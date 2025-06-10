/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:03:25 by sardomin          #+#    #+#             */
/*   Updated: 2025/05/31 12:03:45 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_thread_philo **philo)
{
	t_rules	*rules;
	
	if (!philo || !*philo)
		return ;
	rules = (*philo)[0].rules;
	if (rules)
	{
		if (rules->forks)
			free(rules->forks);
		if (rules->someone_died)
			free(rules->someone_died);
		if (rules->forks_mutex_destroyed)
			free(rules->forks_mutex_destroyed);
		free(rules);
	}
	free(*philo);
	*philo = NULL;
}

