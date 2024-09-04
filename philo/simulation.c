/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:48:54 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/22 15:17:19 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *msg)
{
	printf("Error: %s\n", msg);
	return (1);
}

void	lock_leftfork_print(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork_mtx);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d has taken a fork\n",
		get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	lock_rightfork_print(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork_mtx);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d has taken a fork\n",
		get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	*philo_sim(t_philo *philo)
{
	(!(philo->id % 2)) && (my_sleep(philo->time_to_eat / 2));
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&philo->data->eat_mutex);
		if (philo->nb_eat == 0)
		{
			pthread_mutex_unlock(&philo->data->eat_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->eat_mutex);
	}
	return (NULL);
}

void	monitor_philos(t_philo *philo)
{
	int		i;

	while (1)
	{
		i = -1;
		while (++i < philo->nb_philo)
		{
			pthread_mutex_lock(&philo->data->eat_mutex);
			if (get_time() - philo[i].last_eat >= philo[i].time_to_die)
			{
				if (philo[i].nb_eat)
				{
					pthread_mutex_lock(&philo->data->print_mutex);
					printf("%lld %d died\n",
						get_time() - philo[i].data->start, philo[i].id);
					return ;
				}
			}
			pthread_mutex_unlock(&philo->data->eat_mutex);
		}
		if (!check_eat_count(philo))
			break ;
	}
}
