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

int	ft_death_threads(t_thread_philo *philos, pthread_t *death_th)
{
	if (pthread_create(death_th, NULL, &ft_death_chk, (void *)philos) != 0)
	{
		write(2, "Error creating death checker thread\n", 36);
		return (1);
	}
	return (0);
}

int	ft_start_fed_threads(t_thread_philo *philos, pthread_t *fed_thread)
{
	if (pthread_create(fed_thread, NULL, &ft_fed_checker, (void *)philos) != 0)
	{
		write(2, "Error creating fed checker thread\n", 35);
		return (1);
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
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			write(2, "Error creating thread for philosophers %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}
