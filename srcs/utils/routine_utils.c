/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:39:44 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 05:11:08 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

bool	someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (false);
}

int	check_if_dead(t_philo *philo)
{
	int			should_print;
	long long	last_meal_time;

	should_print = 0;
	last_meal_time = time_since_meal(philo);
	if (last_meal_time >= philo->data->ttd)
	{
		pthread_mutex_lock(&philo->data->dead);
		if (!philo->data->is_dead)
		{
			philo->data->is_dead = 1;
			should_print = 1;
		}
		pthread_mutex_unlock(&philo->data->dead);
		if (should_print)
			safe_print(philo, "Died", true);
		return (1);
	}
	return (0);
}

void	safe_print(t_philo *philo, char *action, bool	dead_philo)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->is_dead && !dead_philo)
	{
		pthread_mutex_unlock(&philo->data->dead);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead);
	timestamp = get_actual_time(philo->data);
	printf("%lld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->print);
}
