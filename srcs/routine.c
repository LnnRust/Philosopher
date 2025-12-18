/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:46:09 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/18 20:14:36 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long time_since_meal(t_philo *philo)
{
	long long current_time;
	long long time_since;

	pthread_mutex_lock(&philo->meal);
	current_time = get_actual_time(philo->data);
	time_since = current_time - philo->last_eat;
	pthread_mutex_unlock(&philo->meal);
	return (time_since);
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

int	isDead(t_philo *philo)
{
	long long last_meal_time;

	last_meal_time = time_since_meal(philo);
	if (last_meal_time >= philo->data->ttd)
	{
		pthread_mutex_lock(&philo->data->dead);
		if (!philo->data->is_dead)
			philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	return (0);
}

void	safe_print(t_philo *philo, char *action, bool	dead_philo)
{
	long long timestamp;

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

void	one_philo_case(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, "has taken a fork", false);
	usleep(philo->data->ttd * 1000);
	safe_print(philo, "is dead", true);
	pthread_mutex_unlock(philo->l_fork);
}

void	even_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, "has taken a fork", false);
	pthread_mutex_lock(philo->r_fork);
	safe_print(philo, "has taken a fork", false);
	safe_print(philo, "is eating", false);
	pthread_mutex_lock(&philo->meal);
	philo->last_eat = get_actual_time(philo->data);
	philo->eaten++;
	pthread_mutex_unlock(&philo->meal);
	usleep(philo->data->tte * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	safe_print(philo, "is sleeping", false);
	usleep(philo->data->tts * 1000);
	safe_print(philo, "is thinking", false);
}

void	odd_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	safe_print(philo, "has taken a fork", false);
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, "has taken a fork", false);
	safe_print(philo, "is eating", false);
	pthread_mutex_lock(&philo->meal);
	philo->last_eat = get_actual_time(philo->data);
	philo->eaten++;
	pthread_mutex_unlock(&philo->meal);
	usleep(philo->data->tte * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	safe_print(philo, "is sleeping", false);
	usleep(philo->data->tts * 1000);
	safe_print(philo, "is thinking", false);
}

//si philo pair, prendre a gauche en premier, si impair prendre a droite
void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (!someone_died(philo))
	{
		if (philo->id % 2 == 0)
			even_philo(philo);
		else
			odd_philo(philo);
		pthread_mutex_lock(&philo->meal);
		if (philo->data->num_to_eat != -1 &&
			philo->eaten >= philo->data->num_to_eat)
		{
			pthread_mutex_unlock(&philo->meal);
			break;
		}
		pthread_mutex_unlock(&philo->meal);
	}
	return (NULL);
}
