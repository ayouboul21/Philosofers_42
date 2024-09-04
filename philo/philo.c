/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:27:21 by aoulahra          #+#    #+#             */
/*   Updated: 2024/09/04 10:57:56 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks_mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t)
			* data->nb_philo);
	if (!data->forks_mutex && error("Error: Malloc failed\n"))
		return (0);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	return (1);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	free(data->forks_mutex);
	free(data->philo);
	free(data);
}

int	check_arguments(int ac, char **av, t_data **data)
{
	int	i;

	i = 0;
	*data = (t_data *) malloc (sizeof(t_data));
	if (!(*data) && error("Error: Malloc failed\n"))
		return (0);
	while (++i < ac)
	{
		if ((i > 1 && ft_atoi(av[i]) < 60 && i != 5) || ft_atoi(av[i]) <= 0)
		{
			free(*data);
			printf("Error: Invalid argument\n");
			return (0);
		}
	}
	i = 1;
	(*data)->nb_philo = ft_atoi(av[i++]);
	(*data)->time_to_die = ft_atoi(av[i++]);
	(*data)->time_to_eat = ft_atoi(av[i++]);
	(*data)->time_to_sleep = ft_atoi(av[i++]);
	(ac == 6) && ((*data)->nb_eat = ft_atoi(av[i]));
	(ac != 6) && ((*data)->nb_eat = -1);
	(*data)->start = get_time();
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 6 && ac != 5 && error("Invalid number of arguments"))
		return (1);
	if (!check_arguments(ac, av, &data))
		return (1);
	if (!init_mutex(data))
		return (1);
	if (!init_philo(data))
		return (1);
	if (!create_threads(data))
		return (1);
	monitor_philos(data->philo);
	usleep(100000);
	free_data(data);
}
