/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:57:58 by sardomin          #+#    #+#             */
/*   Updated: 2025/05/18 18:58:11 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init2_ph(int i, t_thread_philo **philos, t_rules *rules)
{
	(*philos)[i].left_fork = &rules->forks[(i + 1) % rules->nb_philos];
	(*philos)[i].right_fork = &rules->forks[i];
}

int	ft_init_ph(char **argv, t_thread_philo **philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].thread = 0;
		(*philos)[i].left_fork = &rules->forks[i];
		(*philos)[i].right_fork = &rules->forks[(i + 1) % rules->nb_philos];
		if (i % 2 != 0)
			ft_init2_ph(i, &(*philos), rules);
		(*philos)[i].mutex_destroyed = -1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_eaten = 0;
		(*philos)[i].rules = rules;
		if (pthread_mutex_init(&((*philos)[i].mutex), NULL) != 0)
		{
			ft_print_error("Error. Philo mutex init failed\n", 31);
			return (1);
		}
		(*philos)[i].mutex_destroyed = 0;
		i++;
	}
	return (0);
}

int	ft_init_rules2(int nb, int argc, char **argv, t_rules **rules)
{
	int	i;

	i = 0;
	(*rules)->forks_mutex_destroyed = (int *)malloc(nb * sizeof(int));
	if (!(*rules)->forks_mutex_destroyed)
		return (1);
	while (i < (*rules)->nb_philos)
	{
		((*rules)->forks_mutex_destroyed)[i] = -1;
		i++;
	}
	(*rules)->print_mutex_destroyed = -1;
	(*rules)->death_mutex_destroyed = -1;
	(*rules)->s_died_mutex_destroyed = -1;
	(*rules)->fed_mutex_destroyed = -1;
	(*rules)->ph_fed_mutex_destroyed = -1;
	(*rules)->nb_times_philo_must_eat = -1;
	if (argc == 6)
		(*rules)->nb_times_philo_must_eat = ft_atoi(argv[5]);
	(*rules)->philos_fed = 0;
	if (ft_init_rules_mutexes(rules) != 0)
		return (1);
	return (0);
}

int	ft_init_rules(int argc, char **argv, t_rules **rules)
{
	int	nb;

	if (!rules || !(*rules) || !argv || !(*argv))
		return (1);
	(*rules)->nb_philos = ft_atoi(argv[1]);
	nb = (*rules)->nb_philos;
	(*rules)->nb_forks = ft_atoi(argv[1]);
	(*rules)->time_to_die = ft_atoi(argv[2]);
	(*rules)->time_to_sleep = ft_atoi(argv[3]);
	(*rules)->time_to_eat = ft_atoi(argv[4]);
	if (!(*rules)->start_time)
		(*rules)->start_time = ft_timestamp_in_ms();
	(*rules)->forks = (pthread_mutex_t *)malloc(nb * sizeof(pthread_mutex_t));
	if (!(*rules)->forks)
		return (1);
	(*rules)->someone_died = (int *)malloc(2 * sizeof(int));
	if (!(*rules)->someone_died)
		return (1);
	(*rules)->someone_died[0] = 0;
	(*rules)->someone_died[1] = 0;
	(*rules)->death_printed = 0;
	if (ft_init_rules2(nb, argc, argv, rules))
		return (1);
	return (0);
}

int	ft_init(char **argv, t_rules **rules, t_thread_philo **philos)
{
	int	nb;

	nb = ft_atoi(argv[1]);
	*rules = (t_rules *)malloc(sizeof(t_rules));
	if (!*rules)
		return (1);
	memset(*rules, 0, sizeof(t_rules));
	*philos = (t_thread_philo *)malloc(nb * sizeof(t_thread_philo));
	if (!*philos)
	{
		free(*rules);
		return (1);
	}
	return (0);
}
