/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:38:58 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/22 14:57:17 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nb_philo);
	if (!data->pid)
		error("Error: Malloc failed\n");
	sem_unlink("eat_sem");
	data->eat_sem = sem_open("eat_sem", O_CREAT, 0644, data->nb_philo / 2);
	sem_unlink("forks_sem");
	data->forks_sem = sem_open("forks_sem", O_CREAT, 0644, data->nb_philo);
	sem_unlink("print_sem");
	data->print_sem = sem_open("print_sem", O_CREAT, 0644, 1);
	sem_unlink("wait_sem");
	if (data->eat_sem == SEM_FAILED || data->forks_sem == SEM_FAILED
		|| data->print_sem == SEM_FAILED)
	{
		free_data(data);
		printf("Error: Semaphore failed\n");
		return (0);
	}
	return (1);
}

int	check_arguments(int ac, char **av, t_data **data)
{
	int	i;

	i = 0;
	*data = (t_data *) malloc (sizeof(t_data));
	if (!(*data))
		error("Error: Malloc failed\n");
	ft_bzero(*data, sizeof(t_data));
	while (++i < ac)
	{
		if ((i > 1 && ft_atoi(av[i]) < 60 && i != 5) || ft_atoi(av[i]) <= 0)
		{
			free(*data);
			printf("Error: Invalid argument\n");
			return (0);
		}
	}
	(*data)->nb_philo = ft_atoi(av[1]);
	(*data)->time_to_die = ft_atoi(av[2]);
	(*data)->time_to_eat = ft_atoi(av[3]);
	(*data)->time_to_sleep = ft_atoi(av[4]);
	(ac == 6) && ((*data)->nb_eat = ft_atoi(av[5]));
	(ac != 6) && ((*data)->nb_eat = -1);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 6 && ac != 5)
		error("Invalid number of arguments");
	if (!check_arguments(ac, av, &data))
		return (1);
	if (!init_philo(data))
		return (1);
	start_simulation(data);
	free_data(data);
	return (0);
}
