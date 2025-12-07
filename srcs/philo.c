/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:28:50 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/07 03:29:29 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_data(t_data *data, int ac, char **av)
{
	data->num_to_eat = ft_atol(av[5]);
	data->phil_num = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
}

void	*routine(t_philo *philo)
{
	int	id;

	id = (int *)philo;
}

int	main(int ac, char **av)
{
	int			i;
	int			t_id;
	t_data		*data;
	pthread_t	*thread;

	t_id = 1;
	data = malloc(sizeof(data));
	if (ac == 6)
	{
		if (check_values(ac, av) == false);
			return (1);
		init_data(data, ac, av);
		i = 0;
		while (i < data->phil_num)
		{
			if (pthread_create(&thread, NULL, routine, &t_id) != 0)
				return (free(data), NULL);

			i++;
		}
	}
	return (0);
}
