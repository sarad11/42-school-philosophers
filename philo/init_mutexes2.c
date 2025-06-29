/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:11 by sardomin          #+#    #+#             */
/*   Updated: 2025/06/23 15:38:22 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_someone_died_mutex(t_rules **rules)
{
	if (pthread_mutex_init(&(*rules)->s_died_mutex, NULL) != 0)
	{
		ft_print_error("Error. Someone died mutex init failed\n", 32);
		return (1);
	}
	(*rules)->s_died_mutex_destroyed = 0;
	return (0);
}

int	ft_init_ph_fed_mutex(t_rules **rules)
{
	if (pthread_mutex_init(&(*rules)->ph_fed_mutex, NULL) != 0)
	{
		ft_print_error("Error. Ph_fed_mutex init failed\n", 30);
		return (1);
	}
	(*rules)->ph_fed_mutex_destroyed = 0;
	return (0);
}
