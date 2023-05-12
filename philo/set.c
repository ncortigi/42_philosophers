/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:03:36 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/12 12:27:27 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	allocate(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->tid)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
		return (0);
	data->philos = malloc(sizeof(t_phi) * data->n_philo);
	if (!data->philos)
		return (0);
	return (1);
}

int	ft_set(int ac, char **av, t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	data->start = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	data->n_philo = ft_atoi(av[1]);
	data->tm_to_die = ft_atoi(av[2]);
	data->tm_to_eat = ft_atoi(av[3]);
	data->tm_to_sleep = ft_atoi(av[4]);
	data->finished = 0;
	data->dead = 0;
	if (ac == 6)
		data->n_meals = ft_atoi(av[5]);
	else
		data->n_meals = -1;
	if (!allocate(data))
		return (0);
	pthread_mutex_init(&data->eat_mu, NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->dead_mu, NULL);
	pthread_mutex_init(&data->meal, NULL);
	pthread_mutex_init(&data->print, NULL);
	return (1);
}

static void	set_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].data = data;
		data->philos[i].whitch = i + 1;
		data->philos[i].last_meal = get_time(data->start);
		data->philos[i].eat_times = 0;
		data->philos[i].eating = 0;
		data->philos[i].status = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
		i++;
	}
}

void	set_forks_and_phi(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos[0].r_fork = &data->forks[0];
	if (data->n_philo != 1)
		data->philos[0].l_fork = &data->forks[data->n_philo - 1];
	i = 1;
	while (i < data->n_philo)
	{
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[i - 1];
		i++;
	}
	set_philos(data);
}
