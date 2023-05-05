/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:39:24 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/05 17:45:16 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_eating(t_phi *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal = get_time(philo->data->start);
	print("is eating", philo);
	philo->eat_times++;
	pthread_mutex_unlock(&philo->data->meal);
	usleep(philo->data->tm_to_eat * 1000);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (philo->data->dead > 0)
		return ;
	print("is sleeping", philo);
	usleep(philo->data->tm_to_sleep * 1000);
}

static void	ft_thinking(t_phi *philo)
{
	print("is thinking", philo);
}

void	*living(void *pointer)
{
	t_phi	*philo;

	philo = (t_phi *)pointer;
	if (philo->whitch % 2 == 0)
		usleep(10);
	while (philo->data->dead == 0)
	{
		ft_thinking(philo);
		if (philo->data->dead > 0)
			return (0);
		ft_eating(philo);
	}
	return (0);
}
