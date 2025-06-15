/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saradominguez <saradominguez@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:43:04 by saradomingu       #+#    #+#             */
/*   Updated: 2025/05/17 21:49:11 by saradomingu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_thread_philo	*philos;
	pthread_t		death_thread;
	pthread_t		fed_thread;
	t_rules			*rules;

	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (0);
	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) == 1)
	{
		ft_arg_error(argc, argv);
		return (1);
	}
	if ((ft_init(argv, &rules, &philos) != 0) || (ft_init_rules(argc, argv, &rules) != 0))
	{
		ft_destroy_mutex(&philos);
		ft_free(&philos);
		return (1);
	}
	if (ft_init_ph(argv, &philos, rules) || ft_start_threads(philos) != 0)
	{
		ft_join_threads(ft_atoi(argv[1]), philos);
		ft_destroy_mutex(&philos);
		ft_free(&philos);
		return (1);
	}
	if (ft_death_threads(philos, &death_thread) != 0)
	{
		ft_join_threads(ft_atoi(argv[1]), philos);
		ft_join_death_philo_thread(death_thread);
		ft_destroy_mutex(&philos);
		ft_free(&philos);
		return (1);
	}
	if (argc == 6)
	{
		if (ft_start_fed_threads(philos, &fed_thread) != 0)
		{
			ft_join_threads(ft_atoi(argv[1]), philos);
			ft_join_death_philo_thread(death_thread);
			ft_join_fed_philo_thread(fed_thread);
			ft_destroy_mutex(&philos);
			ft_free(&philos);
			return (1);
		}
		if (ft_join_fed_philo_thread(fed_thread) != 0)
		{
			ft_destroy_mutex(&philos);
			ft_free(&philos);
			return (1);
		}
	}
	if (ft_join_death_philo_thread(death_thread) != 0 || ft_join_threads(ft_atoi(argv[1]), philos))
	{
		ft_destroy_mutex(&philos);
		ft_free(&philos);
		return (1);
	}
	if (ft_destroy_mutex(&philos) != 0)
	{
		ft_free(&philos);
		return (1);
	}
	ft_free(&philos);
	return (0);
}
