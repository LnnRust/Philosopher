/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:30:33 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 10:00:14 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	all_done_actions(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->dead);
}

static	bool	check_phils(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->phil_num)
	{
		if (check_if_dead(&data->philo[i]))
			return (true);
	}
	return (false);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;
	int		all_done;

	data = (t_data *)arg;
	while (1)
	{
		all_done = 1;
		if (check_phils(data) == true)
			return (NULL);
		if (data->num_to_eat != -1)
		{
			i = -1;
			while (++i < data->phil_num)
			{
				pthread_mutex_lock(&data->philo[i].meal);
				if (data->philo[i].eaten < data->num_to_eat)
					all_done = 0;
				pthread_mutex_unlock(&data->philo[i].meal);
			}
			if (all_done)
				return (all_done_actions(data), NULL);
		}
		usleep(1000);
	}
}
