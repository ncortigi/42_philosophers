/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:19:04 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/05 17:41:11 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_eat_times(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	data->finished++;
	pthread_mutex_unlock(&data->lock);
}

static void	ft_death(t_data *data, int i)
{
	long int	time;

	time = get_time(data->start);
	pthread_mutex_unlock(&data->meal);
	data->dead++;
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
			if (data->philos[i].eat_times == data->n_meals)
				ft_eat_times(data);
			if (data->finished == data->n_philo)
				return (0);
			pthread_mutex_unlock(&data->meal);
		}
	}
	return (0);
}
