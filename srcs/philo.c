/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:28:50 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/10 08:21:32 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_struct(t_data *data, int ac, char **av)
{
	data->num_to_eat = ft_atol(av[5]);
	data->phil_num = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	data->start_time = get_start_time();
}

void	init_philo(t_data *data)
{
	int i;

	i = 0;
	while(i < data->phil_num)
	{
		t_philo *philo;
		philo = malloc(sizeof(t_philo));
		if(!philo)
			return (free(philo), NULL);
		 // pthread_create(&)
		 i++;
	}
	// pthread_join(&thread, NULL);
}

void	*routine(t_philo *philo)
{

}

long long	get_start_time(void)
{
	long long start_time;
	struct timeval *tv;
	gettimeofday(tv, NULL);
	start_time = (tv->tv_sec * 1000) + (tv->tv_usec / 1000);
	return (start_time);
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*thread;

	data = malloc(sizeof(data));
	if (ac == 6)
	{
		if (parse_args(ac, av) == false);
			return (0);
		init_struct(data, ac, av);
	}
	return (0);
}
