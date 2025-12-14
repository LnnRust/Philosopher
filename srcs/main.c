/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:28:50 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/14 07:59:24 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


//gerer les erreurs : cas ou erreur mutex_init -> mutex_destroy
static bool	init_struct(t_data *data, int ac, char **av)
{
	int i;

	if(ac == 6)
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
		return (false);
	data->start_time = get_start_time();
	data->is_dead = 0;
	data->all_ate = 0;
	if(pthread_mutex_init(&data->print, NULL) != 0)
		return (false);
	if(pthread_mutex_init(&data->dead, NULL) != 0)
		return (false);
	i = -1;
	while(++i < data->phil_num)
		pthread_mutex_init(&data->fork[i], NULL);
	return (true);
}

static bool	create_philos(t_data *data)
{
	int i;

	i = 0;
	while(i < data->phil_num)
	{
		if(pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]) != 0)
		{
			printf("Error, failed to create philosopher\n");
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_philo(t_data *data)
{
	int i;

	i = 0;
	while(i < data->phil_num)
	{
		//data->philo[i].thread = pas besoin d init ici car init avec pthread_create
		data->philo[i].id = i + 1;
		data->philo[i].eaten = 0;
		data->philo[i].last_eat = data->start_time;
		data->philo[i].l_fork = &data->fork[i];
		data->philo[i].r_fork = &data->fork[(i + 1) % data->phil_num];
		data->philo[i].data = data;
		if(pthread_mutex_init(&data->philo[i].meal, NULL) != 0)
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

// pthread_create(&philo[i].thread, NULL, routine, &philo[i]);

int	main(int ac, char **av)
{
	t_data		*data;

	if (ac != 6)
		return (EXIT_FAILURE);
	data = malloc(sizeof(data));
	if(!data || !parse_args(ac, av))
		return (EXIT_FAILURE);
	if(!init_struct(data, ac, av))
	{
		return 1;
		// free(); clean up tout et return; //
	}
	if(!init_philo(data))
	{
		return 1;
		// free(); clean up tout et return //
	}
	if(!create_philos(data))
		return (1);
	join_philos(data);
	//clean et exit //
	return (0);
}
