/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:46:09 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/14 09:49:14 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	time_since_meal(t_philo *philo)
{
	long long	current_time;
	long long	time_since_last_meal;

	current_time = get_start_time();
	pthread_mutex_lock(&philo->meal);
	time_since_last_meal = current_time - philo->last_eat;
	pthread_mutex_unlock(&philo->meal);
	return (time_since_last_meal);
}

int	isDead(t_philo *philo)
{
	long long last_meal_time;

	last_meal_time = time_since_meal(philo);
	if (last_meal_time > philo->data->ttd)
	{
		pthread_mutex_lock(&philo->data->dead);
		if (!philo->data->is_dead)
		{
			philo->data->is_dead = 1;
			pthread_mutex_lock(&philo->data->print);
			printf("%lld %d died\n", get_actual_time(philo->data), philo->id);
			pthread_mutex_unlock(&philo->data->print);
		}
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	return (0);
}

bool	someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if(philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (false);
}

void	safe_print(t_philo *philo, char *action, bool	dead_philo)
{
	long long timestamp;

	if(someone_died(philo) && !dead_philo)
		return ;
	timestamp = get_actual_time(philo->data);
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&philo->data->print);
}

void	one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, "has taken a fork", false);
	usleep(philo->data->ttd * 1000);
	pthread_mutex_unlock(philo->l_fork);
}

void	handle_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, "has taken a fork", false);
	pthread_mutex_lock(philo->r_fork);
	safe_print(philo, "has taken a fork", false);
	safe_print(philo, "is eating", false);
	pthread_mutex_lock(&philo->meal);
	philo->last_eat = get_start_time();
	philo->eaten++;
	pthread_mutex_unlock(&philo->meal);
	usleep(philo->data->tte * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	safe_print(philo, "is sleeping", false);
	usleep(philo->data->tts * 1000);
	safe_print(philo, "is thinking", false);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	if (philo->data->phil_num == 1)
		return (one_philo_case(philo), NULL);
	if (philo->id % 2 == 0) // evite deadlock //
		usleep(100);
	while (1)
	{
		i = 0;
		while (i < philo->data->phil_num)
		{
			if (isDead(&philo->data->philo[i]))
				return (NULL);
			i++;
		}
		handle_forks(philo);
	}
	return (NULL);
}
