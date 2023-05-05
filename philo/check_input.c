/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:30:13 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/04 14:22:44 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	control_numbers(int ac, char **av)
{
	int	i;

	if (ac == 6)
	{
		if (ft_atoi(av[5]) <= 0)
			return (0);
	}
	if (ft_atoi(av[1]) < 1)
		return (0);
	i = 2;
	while (i < 5)
	{
		if (ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;
	
	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	if (!control_numbers(ac, av))
		return (0);
	return (1);
}
