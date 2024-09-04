/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:16:15 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/22 15:41:08 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long long		last_eat;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	*right_fork_mtx;
	pthread_mutex_t	*left_fork_mtx;
}				t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	long long		start;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
	t_philo			*philo;
}				t_data;

int			ft_atoi(char *str);
int			create_threads(t_data *data);
int			init_philo(t_data *data);
int			check_eat_count(t_philo *philo);
int			error(char *msg);
int			my_sleep(long time);
void		lock_rightfork_print(t_philo *philo);
void		lock_leftfork_print(t_philo *philo);
void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		monitor_philos(t_philo *philo);
void		*philo_sim(t_philo *philo);
long long	get_time(void);

#endif
