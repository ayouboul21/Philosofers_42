/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:22:17 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/22 14:30:56 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	error(char *str)
{
	printf("Error: %s\n", str);
	exit(1);
}

void	my_sleep(long time)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

long long	get_time(void)
{
	long long		time;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time = now.tv_sec * 1000;
	time += now.tv_usec / 1000;
	return (time);
}

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

void	free_data(t_data *data)
{
	if (data->eat_sem != SEM_FAILED)
	{
		sem_close(data->eat_sem);
		sem_unlink("eat_sem");
	}
	if (data->forks_sem != SEM_FAILED)
	{
		sem_close(data->forks_sem);
		sem_unlink("forks_sem");
	}
	if (data->print_sem != SEM_FAILED)
	{
		sem_close(data->print_sem);
		sem_unlink("print_sem");
	}
	if (data->pid)
		free(data->pid);
	free(data);
}
