/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:19:04 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/12 12:47:39 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	control_death(t_phi *philo)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&philo->data->dead_mu);
	if (philo->data->dead >= 1)
		ret = 0;
	pthread_mutex_unlock(&philo->data->dead_mu);
	return (ret);
}

static int	ft_finished(t_data *data)
{
	pthread_mutex_lock(&data->dead_mu);
	data->finished = data->n_philo;
	data->dead++;
	pthread_mutex_unlock(&data->dead_mu);
	pthread_mutex_unlock(&data->meal);
	return (1);
}

static int	ft_eat_times(t_data *data)
{
	int	finished;
	int	i;

	i = 0;
	finished = 0;
	if (data->n_meals != -1)
	{
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&data->eat_mu);
			if (data->philos[i].eat_times >= data->n_meals)
				finished++;
			pthread_mutex_unlock(&data->eat_mu);
			i++;
		}
		if (finished == data->n_philo)
			return (ft_finished(data));
	}
	return (0);
}

static void	ft_death(t_data *data, int i)
{
	long int	time;

	time = get_time(data->start);
	pthread_mutex_unlock(&data->meal);
	pthread_mutex_lock(&data->dead_mu);
	data->dead++;
	pthread_mutex_unlock(&data->dead_mu);
	pthread_mutex_lock(&data->print);
	printf("%ld    %d died\n", time, data->philos[i].whitch);
	pthread_mutex_unlock(&data->print);
}

void	*check_death(void *pointer)
{
	t_data	*data;
	int		i;

	data = (t_data *)pointer;
	while (1)
	{
		i = -1;
		usleep(10);
		while (++i < data->n_philo)
		{
			pthread_mutex_lock(&data->meal);
			if (data->tm_to_die < get_time(data->start) - \
				data->philos[i].last_meal && data->philos[i].eating == 0)
			{
				ft_death(data, i);
				return (0);
			}
			else if (ft_eat_times(data))
				return (0);
			pthread_mutex_unlock(&data->meal);
		}
	}
	return (0);
}
