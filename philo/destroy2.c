/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:40:01 by sardomin          #+#    #+#             */
/*   Updated: 2025/06/15 17:40:16 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_destroy_fed_mutex(t_thread_philo **philos)
{
	if (philos[0]->rules->fed_mutex_destroyed == 0)
	{
		if (pthread_mutex_destroy(&philos[0]->rules->fed_mutex) != 0)
		{
			ft_print_error("Error. Destroy fed_mutex failed\n", 34);
			return (1);
		}
	}
	philos[0]->rules->fed_mutex_destroyed = 1;
	return (0);
}

int	ft_destroy_s_died_mutex(t_thread_philo **philos)
{
	if (philos[0]->rules->s_died_mutex_destroyed == 0)
	{
		if (pthread_mutex_destroy(&philos[0]->rules->s_died_mutex) != 0)
		{
			ft_print_error("Error. Destroy s_died_mutex failed\n", 34);
			return (1);
		}
	}
	philos[0]->rules->s_died_mutex_destroyed = 1;
	return (0);
}
