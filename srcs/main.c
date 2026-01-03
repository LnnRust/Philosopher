/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:28:50 by aandreo           #+#    #+#             */
/*   Updated: 2026/01/03 12:58:00 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	bool	init_struct(t_data *data, int ac, char **av)
{
	int	i;

	if (ac == 6)
		data->num_to_eat = ft_atol(av[5]);
	else
		data->num_to_eat = -1;
	data->phil_num = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	data->philo = malloc(sizeof(t_philo) * data->phil_num);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->phil_num);
	if (!data->philo || !data->fork)
		return (cleanup(data), false);
	data->start_time = get_start_time();
	data->is_dead = 0;
	data->all_ate = 0;
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (cleanup(data), false);
	if (pthread_mutex_init(&data->dead, NULL) != 0)
		return (cleanup(data), false);
	i = -1;
	while (++i < data->phil_num)
		pthread_mutex_init(&data->fork[i], NULL);
	return (true);
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	monitor_t;

	if (!parse_args(ac, av))
		return (EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	if (!init_struct(data, ac, av))
		return (EXIT_FAILURE);
	if (!init_philo(data))
		return (EXIT_FAILURE);
	if (data->phil_num == 1)
		return (one_philo_case(data->philo), destroy_mutexes(data),
			cleanup(data), EXIT_SUCCESS);
	if (!create_philos(data))
		return (EXIT_FAILURE);
	if (pthread_create(&monitor_t, NULL, monitor, data) != 0)
		return (EXIT_FAILURE);
	pthread_join(monitor_t, NULL);
	join_philos(data);
	destroy_mutexes(data);
	free(data->fork);
	free(data->philo);
	return (free(data), EXIT_SUCCESS);
}
