/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:57:51 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/05 17:41:50 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//void	ft_case_one(t_data *data)
//{
//}

// void	*control_eat(void *pointer)
// {
// 	t_phi	*philo;

// 	philo = (t_phi *)pointer;
// 	while (philo->data->dead == 0)
// 	{
// 		pthread_mutex_lock(&philo->data->dead_mu);
// 		if (philo->data->finished >= philo->data->n_philo)
// 			philo->data->dead = 1;
// 		pthread_mutex_unlock(&philo->data->dead_mu);
// 	}
// 	return (0);
// }

void	ft_threads(t_data *data)
{
	int			i;
	pthread_t	t_check;
	//pthread_t	thr;

	i = -1;
	// if (data->n_meals > 0)
	// {
	// 	pthread_create(&thr, NULL, &control_eat, &(data->philos[0]));
	// }
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
		return(ft_write_and_return("Error in imput\n", 0));
	if (!ft_set(ac, av, &data))
		return(ft_write_and_return("Error in memory allocation\n", 0));
	set_forks_and_phi(&data);
	//if (data->n_philo == 1)
	//	ft_case_one(&data);
	//else
	ft_threads(&data);
	ft_close(&data);
}