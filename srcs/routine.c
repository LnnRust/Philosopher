/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:46:09 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 10:36:16 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	pthread_mutex_lock(&philo->meal);
	philo->last_eat = get_actual_time(philo->data);
	philo->eaten++;
	pthread_mutex_unlock(&philo->meal);
	safe_print(philo, "is eating", false);
	usleep(philo->data->tte * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	safe_print(philo, "is sleeping", false);
	usleep(philo->data->tts * 1000);
	safe_print(philo, "is thinking", false);
	if (philo->data->phil_num % 2 == 1)
		usleep((philo->data->tte * 2 - philo->data->tts) * 1000);
}

void	odd_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	safe_print(philo, "has taken a fork", false);
	pthread_mutex_lock(philo->l_fork);
	safe_print(philo, "has taken a fork", false);
	pthread_mutex_lock(&philo->meal);
	philo->last_eat = get_actual_time(philo->data);
	philo->eaten++;
	pthread_mutex_unlock(&philo->meal);
	safe_print(philo, "is eating", false);
	usleep(philo->data->tte * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	safe_print(philo, "is sleeping", false);
	usleep(philo->data->tts * 1000);
	safe_print(philo, "is thinking", false);
	if (philo->data->phil_num % 2 == 1)
		usleep((philo->data->tte * 2 - philo->data->tts) * 1000);
}

//si philo pair, prendre a gauche en premier, si impair prendre a droite
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->tte / 2 * 1000);
	while (!someone_died(philo))
	{
		if (philo->id % 2 == 0)
			even_philo(philo);
		else
			odd_philo(philo);
		pthread_mutex_lock(&philo->meal);
		if (philo->data->num_to_eat != -1
			&& philo->eaten >= philo->data->num_to_eat)
		{
			pthread_mutex_unlock(&philo->meal);
			break ;
		}
		pthread_mutex_unlock(&philo->meal);
		usleep(100);
	}
	return (NULL);
}
