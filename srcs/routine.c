/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:46:09 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/11 11:28:08 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//bool	fork_handle(t_data *data)
//{

//}

void	safe_print(t_philo *philo, char *action)
{
	long long timestamp;

	if(&philo->data->dead)
	{
		pthread_mutex_lock(&philo->data->dead);
		printf("%lld %d %s\n", timestamp, philo->id, "is dead");
		pthread_mutex_unlock(&philo->data->dead);
		philo->data->is_dead = 1;
		return ;
	}
	timestamp = get_actual_time(philo->data);
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->print);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	int			i;

	i = 0;
	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->dead);
			break;
		}
		pthread_mutex_unlock(&philo->data->dead);
		pthread_mutex_lock(philo->l_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		safe_print(philo, "has taken a fork");
		safe_print(philo, "is eating");
		pthread_mutex_lock(&philo->meal);
		philo->last_eat = get_start_time();
		philo->eaten++;
		pthread_mutex_unlock(&philo->meal);
		usleep(philo->data->tte * 1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		safe_print(philo, "is sleeping");
		usleep(philo->data->tts * 1000);
		safe_print(philo, "is thinking");
	}
	return (NULL);
}

//void	monitoring(t_data *data)
//{

//}
