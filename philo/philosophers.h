/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncortigi <ncortigi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:10:59 by ncortigi          #+#    #+#             */
/*   Updated: 2023/05/12 12:40:46 by ncortigi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_phi
{
	struct s_data	*data;
	pthread_mutex_t	lock;
	int				eat_times;
	int				last_meal;
	int				whitch;
	int				eating;
	int				status;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_phi;

typedef struct s_data
{
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mu;
	pthread_mutex_t	meal;
	pthread_mutex_t	eat_mu;
	long int		start;
	int				finished;
	int				dead;
	int				n_philo;
	int				tm_to_die;
	int				tm_to_eat;
	int				tm_to_sleep;
	int				n_meals;
	t_phi			*philos;
	pthread_t		thr1;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
}	t_data;

long int	get_time(long int start_time);
void		print(char *str, t_phi *philo);
int			ft_write_and_return(char *str, int ret);
int			check_args(int ac, char **av);
int			ft_atoi(const char *nptr);
int			ft_set(int ac, char **av, t_data *data);
void		set_forks_and_phi(t_data *data);
void		*check_death(void *pointer);
int			control_death(t_phi *philo);
void		*living(void *pointer);
void		ft_close(t_data *data);

#endif