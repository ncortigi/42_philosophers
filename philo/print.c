/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:44:02 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/11 16:58:04 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_write_and_return(char *str, int ret)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (ret);
}

void	print(char *str, t_phi *philo)
{
	pthread_mutex_lock(&philo->data->dead_mu);
	if (philo->data->dead == 0 || \
		philo->data->finished == philo->data->n_philo)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld    %d %s\n", get_time(philo->data->start), \
			philo->whitch, str);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->dead_mu);
}
