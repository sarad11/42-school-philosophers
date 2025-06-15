/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:36:37 by sardomin          #+#    #+#             */
/*   Updated: 2025/06/15 17:36:50 by sardomin         ###   ########.fr       */
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

int	ft_join_fed_philo_thread(pthread_t fed_thread)
{
	if (pthread_join(fed_thread, NULL) != 0)
	{
		write(2, "Error joining fed thread\n", 26);
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
