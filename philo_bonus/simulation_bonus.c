/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:09:18 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/22 15:21:53 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_data *data, int i)
{
	sem_wait(data->forks_sem);
	sem_wait(data->print_sem);
	printf("%lld %d has taken a fork\n",
		get_time() - data->start_time, i + 1);
	sem_post(data->print_sem);
	sem_wait(data->forks_sem);
	sem_wait(data->print_sem);
	printf("%lld %d has taken a fork\n",
		get_time() - data->start_time, i + 1);
	printf("%lld %d is eating\n",
		get_time() - data->start_time, i + 1);
	sem_post(data->print_sem);
	if (data->nb_eat != -1)
		data->nb_eat--;
	my_sleep(data->time_to_eat);
	data->last_eat = get_time();
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
}

void	philo_routine(t_data *data, int i)
{
	data->start_time = get_time();
	data->last_eat = data->start_time;
	if (i % 2)
		my_sleep(data->time_to_eat / 2);
	while (data->nb_eat)
	{
		eating(data, i);
		sem_wait(data->print_sem);
		printf("%lld %d is sleeping\n", get_time() - data->start_time, i + 1);
		sem_post(data->print_sem);
		my_sleep(data->time_to_sleep);
		sem_wait(data->print_sem);
		printf("%lld %d is thinking\n", get_time() - data->start_time, i + 1);
		sem_post(data->print_sem);
	}
}

void	monitor(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < data->nb_philo)
				kill(data->pid[i], SIGKILL);
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			continue ;
	}
}

void	*monitor_philo(t_data *data)
{
	my_sleep(data->time_to_die);
	while (1)
	{
		if (get_time() - data->last_eat >= data->time_to_die)
		{
			sem_wait(data->print_sem);
			printf("%lld %d died\n",
				get_time() - data->start_time, data->nb_philo);
			exit(1);
		}
		usleep(100);
	}
}

void	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			error("Error: Fork failed\n");
		if (data->pid[i] == 0)
		{
			if (pthread_create(&data->monitor, NULL,
					(void *)monitor_philo, data))
				error("Error: pthread_create failed\n");
			if (pthread_detach(data->monitor))
				error("Error: pthread_detach failed\n");
			philo_routine(data, i);
			exit(0);
		}
	}
	monitor(data);
}
