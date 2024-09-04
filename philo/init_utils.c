/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:23:01 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/20 10:15:42 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat_count(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_lock(&philo->data->eat_mutex);
		if (philo[i].nb_eat != 0)
		{
			pthread_mutex_unlock(&philo->data->eat_mutex);
			return (1);
		}
		i++;
		pthread_mutex_unlock(&philo->data->eat_mutex);
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, (void *)philo_sim,
				&data->philo[i]) && error("pthread_create failed"))
			return (0);
		i++;
	}
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_detach(data->philo[i].thread) != 0
			&& error("pthread_detach failed"))
			return (0);
	return (1);
}

void	init(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->nb_philo = data->nb_philo;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->nb_eat = data->nb_eat;
	philo->left_fork_mtx = &data->forks_mutex[philo->id - 1];
	philo->right_fork_mtx = &data->forks_mutex[(philo->id) % data->nb_philo];
	philo->last_eat = get_time();
	philo->data = data;
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philo = (t_philo *) malloc (sizeof(t_philo) * data->nb_philo);
	if (!data->philo && error("malloc failed"))
	{
		free(data);
		return (0);
	}
	while (++i < data->nb_philo)
		init(&data->philo[i], data, i);
	return (1);
}
