/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:44:01 by sardomin          #+#    #+#             */
/*   Updated: 2025/05/31 17:44:23 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_forks(t_rules **rules)
{
	int	i;

	i = 0;
	while (i < (*rules)->nb_philos)
	{
		if (pthread_mutex_init(&((*rules)->forks[i]), NULL) != 0)
		{
			ft_print_error("Error. Mutex init failed\n", 24);
			return (1);
		}
		((*rules)->forks_mutex_destroyed)[i] = 0;
		i++;
	}
	return (0);
}

int	ft_init_print_mutex(t_rules **rules)
{
	if (pthread_mutex_init(&(*rules)->print_mutex, NULL) != 0)
	{
		ft_print_error("Error. Print mutex init failed\n", 32);
		//TODO funcion free para liberar todos los mutex en caso de error
		return (1);
	}
	(*rules)->print_mutex_destroyed = 0;
	return (0);
}

int	ft_init_death_mutex(t_rules **rules)
{
	if (pthread_mutex_init(&(*rules)->death_mutex, NULL) != 0)
	{
		ft_print_error("Error. Death mutex init failed\n", 32);
		return (1);
	}
	(*rules)->death_mutex_destroyed = 0;
	return (0);
}

int	ft_init_rules_mutexes(t_rules **rules)
{
	if (ft_init_forks(rules) != 0)
		return (1);
	if (ft_init_print_mutex(rules) != 0)
		return (1);
	if (ft_init_death_mutex(rules) != 0)
		return (1);
	return (0);
}
