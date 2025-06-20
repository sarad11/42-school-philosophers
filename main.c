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
	t_rules			*rules;

	if (ft_check_functions(argc, argv))
		return (1);
	rules = NULL;
	if (init(argc, argv, &rules, &philos) != 0)
		return (1);
	if (init2(argv, &rules, &philos) != 0)
		return (1);
	if (death(argv[1], &philos, &death_thread) != 0)
		return (1);
	if (argc == 6 && fed(argv[1], &philos, &death_thread) != 0)
		return (1);
	if (join(argv[1], &philos, &death_thread) != 0)
		return (1);
	if (ft_destroy_mutex(&philos) != 0)
	{
		ft_free(&philos);
		return (1);
	}
	ft_free(&philos);
	return (0);
}
