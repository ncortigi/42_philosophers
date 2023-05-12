/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:39:24 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/12 14:55:13 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	drop_forks(t_phi *philo)
{
	if (philo->whitch == philo->data->n_philo)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

static void	take_forks(t_phi *philo)
{
	if (philo->whitch == philo->data->n_philo)
	{
		pthread_mutex_lock(philo->r_fork);
		print("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print("has taken a fork", philo);
		pthread_mutex_lock(philo->r_fork);
		print("has taken a fork", philo);
	}
}

static void	ft_eating(t_phi *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	pthread_mutex_lock(&philo->data->meal);
	philo->last_meal = get_time(philo->data->start);
	pthread_mutex_unlock(&philo->data->meal);
	print("is eating", philo);
	usleep(philo->data->tm_to_eat * 1000);
	pthread_mutex_lock(&philo->data->eat_mu);
	philo->eat_times++;
	pthread_mutex_unlock(&philo->data->eat_mu);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
	if (!control_death(philo))
		return ;
	print("is sleeping", philo);
	usleep(philo->data->tm_to_sleep * 1001);
}

static void	ft_eating_one(t_phi *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print("has taken a fork", philo);
	pthread_mutex_unlock(philo->r_fork);
}

void	*living(void *pointer)
{
	t_phi	*philo;

	philo = (t_phi *)pointer;
	if (philo->data->n_philo == 1)
	{
		print("is thinking", philo);
		ft_eating_one(philo);
		return (0);
	}
	if (philo->whitch % 2 == 0)
		usleep(30);
	while (control_death(philo))
	{
		print("is thinking", philo);
		if (!control_death(philo))
			return (0);
		ft_eating(philo);
	}
	return (0);
}
