/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:43:48 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/22 14:57:37 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <string.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	pid_t			*pid;
	sem_t			*eat_sem;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	long long		start_time;
	long long		last_eat;
	pthread_t		monitor;
}			t_data;

int			ft_atoi(char *str);
void		error(char *str);
void		free_data(t_data *data);
void		my_sleep(long time);
void		philo_routine(t_data *data, int i);
void		ft_bzero(void *s, size_t n);
void		monitor(t_data *data);
void		start_simulation(t_data *data);
void		*monitor_philo(t_data *data);
long long	get_time(void);

#endif
