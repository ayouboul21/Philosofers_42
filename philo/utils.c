/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 09:50:05 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/19 13:09:28 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	find_sign(size_t *i, int *sign, const char *str)
{
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	ft_atoi(char *str)
{
	size_t	i;
	int		res;
	int		pre;
	int		sign;

	(1) && (i = 0, res = 0, pre = 0, sign = 1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	find_sign(&i, &sign, str);
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + (str[i] - '0') * sign;
		if (res / 10 != pre)
			return (-1);
		pre = res;
		i++;
	}
	return (res);
}
