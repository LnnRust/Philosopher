/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:30:33 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/02 16:30:52 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		all_done;

	all_done = 1;
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (++i < data->phil_num)
		{
			if (isDead(&data->philo[i]))
			return (NULL);
			i++;
		}
		if (data->num_to_eat != -1)
		{
			i = 0;
			while (i < data->phil_num)
			{
				pthread_mutex_lock(&data->philo[i].meal);
				if (data->philo[i].eaten < data->num_to_eat)
					all_done = 0;
				pthread_mutex_unlock(&data->philo[i].meal);
				i++;
			}
			if (all_done)
			{
				pthread_mutex_lock(&data->dead);
				data->is_dead = 1;
				pthread_mutex_unlock(&data->dead);
				return (NULL);
			}
		}
		usleep(1000); // check tt les 1ms
	}
	return (NULL);
}
