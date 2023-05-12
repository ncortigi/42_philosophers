/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:51 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/12 15:06:30 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_threads(t_data *data)
{
	int			i;
	pthread_t	t_check;

	i = -1;
	pthread_create(&t_check, NULL, &check_death, data);
	while (++i < data->n_philo)
		pthread_create(&(data->tid[i]), NULL, &living, &(data->philos[i]));
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->tid[i], NULL);
	pthread_join(t_check, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!check_args(ac, av))
		return (ft_write_and_return("Error in input\n", 0));
	if (!ft_set(ac, av, &data))
		return (ft_write_and_return("Error in memory allocation\n", 0));
	set_forks_and_phi(&data);
	ft_threads(&data);
	ft_close(&data);
}
