/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:12:14 by sardomin          #+#    #+#             */
/*   Updated: 2025/06/20 18:12:35 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(int ac, char **av, t_rules **rules, t_thread_philo **philo)
{
	if ((ft_init(av, rules, philo) != 0) || (ft_init_rules(ac, av, rules) != 0))
	{
		ft_destroy_mutex(philo);
		ft_free(philo);
		return (1);
	}
	return (0);
}

int	init2(char **argv, t_rules **rules, t_thread_philo **philos)
{
	if (ft_init_ph(argv, philos, *rules) || ft_start_threads(*philos) != 0)
	{
		ft_join_threads(ft_atoi(argv[1]), *philos);
		ft_destroy_mutex(philos);
		ft_free(philos);
		return (1);
	}
	return (0);
}

int	death(char *argv, t_thread_philo **philos, pthread_t *death_thread)
{
	if (ft_death_threads(*philos, death_thread) != 0)
	{
		ft_join_threads(ft_atoi(argv), *philos);
		ft_join_death_philo_thread(*death_thread);
		ft_destroy_mutex(philos);
		ft_free(philos);
		return (1);
	}
	return (0);
}

int	fed(char *argv, t_thread_philo **philos, pthread_t *death_thread)
{
	pthread_t		fed_thread;

	if (ft_start_fed_threads(*philos, &fed_thread) != 0)
	{
		ft_join_threads(ft_atoi(argv), *philos);
		ft_join_death_philo_thread(*death_thread);
		ft_join_fed_philo_thread(fed_thread);
		ft_destroy_mutex(philos);
		ft_free(philos);
		return (1);
	}
	if (ft_join_fed_philo_thread(fed_thread) != 0)
	{
		ft_destroy_mutex(philos);
		ft_free(philos);
		return (1);
	}
	return (0);
}

int	join(char *argv, t_thread_philo **philos, pthread_t *death_thread)
{
	if (ft_join_death_philo_thread(*death_thread) != 0)
	{
		ft_destroy_mutex(philos);
		ft_free(philos);
		return (1);
	}
	if (ft_join_threads(ft_atoi(argv), *philos) != 0)
	{
		ft_destroy_mutex(philos);
		ft_free(philos);
		return (1);
	}
	return (0);
}
