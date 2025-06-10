/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:59:28 by sardomin          #+#    #+#             */
/*   Updated: 2025/05/18 18:59:42 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_join_death_philo_thread(pthread_t death_thread)
{
	if (pthread_join(death_thread, NULL) != 0)
	{
		write(2, "Error joining death thread\n", 26);
		return (1);
	}
	return (0);
}

int	ft_start_death_philo_threads(t_thread_philo *philos, pthread_t *death_thread)
{
	if (pthread_create(death_thread, NULL, &ft_death_checker, (void *)philos) != 0)
	{
		write(2, "Error creating death checker thread\n", 36);
		return (1);
	}
	return (0);
}

int	ft_join_threads(int nb_philos, t_thread_philo *philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			write(2, "Error joining thread %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_start_threads(t_thread_philo *philos)
{
	int	i;
	int	nb_philos;

	i = 0;
	nb_philos = philos[i].rules->nb_philos;
	while (i < nb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &ft_routine, &philos[i]) != 0)
		{
			write(2, "Error creating thread for philosophers %d\n", i + 1);
			return (1);
		}
		i++;
	}
	//if (ft_join_threads(nb_philos, philos) != 0)
		//return (1);
	return (0);
}
