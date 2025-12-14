/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandreo <aandreo@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:03:37 by aandreo           #+#    #+#             */
/*   Updated: 2025/12/14 07:59:46 by aandreo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static bool	check_values(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if(ft_atol(av[i]) < 0 || ft_atol(av[i]) > INT_MAX)
			return (printf("invalid arg value"), false);
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == false)
				return (printf("arg has invalid character"), false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	parse_args(int ac,char **av)
{
	if(ac != 5 && ac != 6)
		return (printf("wrong number of args\n"), false);
	if(ac == 5 || ac == 6)
		if(!check_values(av))
		return (false);
	return (true);
}
