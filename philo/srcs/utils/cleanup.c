/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 07:36:27 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 10:00:26 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = data->phil_num;
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead);
	while (i--)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].meal);
	}
}

void	cleanup(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->fork)
		free(data->fork);
	free(data);
}
