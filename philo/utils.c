/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:39:56 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/05 14:45:19 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	get_time(long int start_time)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - start_time);
}

int	ft_converter(const char *str)
{
	int	sum;
	int	i;

	i = 0;
	sum = 0;
	while ((str[i] > 47 && str[i] < 58) && str[i])
	{
		sum = sum * 10 + (str[i] - 48);
		i++;
	}
	return (sum);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	meno;

	i = 0;
	meno = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 45)
	{
		meno *= -1;
		i++;
	}
	else if (nptr[i] == 43)
		i++;
	return (ft_converter(&nptr[i]) * meno);
}
