/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:32:18 by sardomin          #+#    #+#             */
/*   Updated: 2025/05/23 20:32:35 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_destroy_death_mutex(t_thread_philo **philos)
{
	if (philos[0]->rules->fed_mutex_destroyed == 0)
	{
		if (pthread_mutex_destroy(&philos[0]->rules->death_mutex) != 0)
		{
			ft_print_error("Error. Destroy death_mutex failed\n", 34);
			return (1);
		}
	}
	philos[0]->rules->death_mutex_destroyed = 1;
	return (0);
}

int	ft_destroy_print_mutex(t_thread_philo **philos)
{
	if (philos[0]->rules->print_mutex_destroyed == 0)
	{
		if (pthread_mutex_destroy(&philos[0]->rules->print_mutex) != 0)
		{
			ft_print_error("Error. Destroy print_mutex failed\n", 34);
			return (1);
		}
	}
	philos[0]->rules->print_mutex_destroyed = 1;
	return (0);
}

int	ft_destroy_forks(t_thread_philo **philos, int i)
{
	if (philos[0]->rules->forks_mutex_destroyed[i] == 0)
	{
		if (pthread_mutex_destroy(&philos[0]->rules->forks[i]) != 0)
		{
			ft_print_error("Error. Destroy forks mutex failed\n", 34);
			return (1);
		}
	}
	philos[0]->rules->forks_mutex_destroyed[i] = 1;
	return (0);
}

int	ft_destroy_philo_mutex(t_thread_philo **philos, int i)
{
	if ((*philos)[i].mutex_destroyed == 0)
	{
		if (pthread_mutex_destroy(&(*philos)[i].mutex) != 0)
		{
			ft_print_error("Error. Destroy philo mutex failed.\n", 33);
			return (1);
		}
		(*philos)[i].mutex_destroyed = 1;
	}
	return (0);
}

int	ft_destroy_mutex(t_thread_philo **philos)
{
	int	i;

	i = 0;
	while (i < (philos[0]->rules->nb_philos))
	{
		if (ft_destroy_philo_mutex(philos, i) != 0)
			return (1);
		if (ft_destroy_forks(philos, i) != 0)
			return (1);
		i++;
	}
	if (ft_destroy_print_mutex(philos) != 0)
		return (1);
	if (ft_destroy_death_mutex(philos) != 0)
		return (1);
	if (ft_destroy_s_died_mutex(philos) != 0)
		return (1);
	if (ft_destroy_fed_mutex(philos) != 0)
		return (1);
	return (0);
}
