/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:46:09 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/10 16:22:42 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

bool	fork_handle(t_data *data)
{

}

void	*routine(void *arg)
{
	int i;
	t_philo *	philo;

	i = 0;
	philo = (t_philo *)arg;
	while(i < philo->data->phil_num && philo->data->all_ate != 1 && philo->data->is_dead != 1)

}

void	monitoring(t_data *data)
{

}
