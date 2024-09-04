/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:57:03 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/19 13:10:14 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	now;
	long long		time;

	gettimeofday(&now, NULL);
	time = now.tv_sec * 1000;
	time += now.tv_usec / 1000;
	return (time);
}

int	my_sleep(long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (0);
}

void	eating(t_philo *philo)
{
	lock_leftfork_print(philo);
	lock_rightfork_print(philo);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->data->eat_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is eating\n", get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->eat_mutex);
	(philo->nb_eat > 0) && (philo->nb_eat--);
	pthread_mutex_unlock(&philo->data->eat_mutex);
	my_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork_mtx);
	pthread_mutex_unlock(philo->left_fork_mtx);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is sleeping\n", get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	my_sleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d is thinking\n", get_time() - philo->data->start, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
