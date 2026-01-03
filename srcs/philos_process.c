/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:32:02 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 05:06:41 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phil_num)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				&data->philo[i]) != 0)
		{
			printf("Error, failed to create philosopher\n");
			return (false);
		}
		i++;
	}
	return (true);
}

//data->philo[i].thread = pas besoin d init ici car init avec pthread_create
bool	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phil_num)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eaten = 0;
		data->philo[i].last_eat = data->start_time;
		data->philo[i].l_fork = &data->fork[i];
		data->philo[i].r_fork = &data->fork[(i + 1) % data->phil_num];
		data->philo[i].data = data;
		if (pthread_mutex_init(&data->philo[i].meal, NULL) != 0)
			return (false);
		i++;
	}
	return (true);
}

void	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->phil_num)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}
