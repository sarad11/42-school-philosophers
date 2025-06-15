/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:50:08 by sardomin          #+#    #+#             */
/*   Updated: 2025/06/15 18:50:17 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_death_chk(void *arg)
{
	t_thread_philo	*philo;
	int				stop;

	philo = (t_thread_philo *)arg;
	stop = 0;
	while (!stop)
	{
		if (ft_is_any_philo_death(&philo))
			stop = 1;
		usleep(100);
	}
	return (NULL);
}

void	*ft_fed_checker(void *arg)
{
	t_thread_philo	*philo;
	t_rules			*rules;
	int				all_fed;
	int				i;

	philo = (t_thread_philo *)arg;
	rules = philo[0].rules;
	if (!philo || !rules || rules->nb_philos <= 0)
		return (NULL);
	if (rules->nb_times_philo_must_eat > 0)
	{
		while (!(philo)[0].rules->someone_died[0])
		{
			all_fed = 1;
			i = 0;
			while (i < rules->nb_philos && !(philo)[0].rules->someone_died[0])
			{
				pthread_mutex_lock(&philo[i].mutex);
				if (philo[i].meals_eaten < rules->nb_times_philo_must_eat)
				{
					all_fed = 0;
					pthread_mutex_unlock(&philo[i].mutex);
					break ;
				}
				pthread_mutex_unlock(&philo[i].mutex);
				i++;
				if (!all_fed)
					break ;
			}
			if (all_fed && !(philo)[0].rules->someone_died[0])
			{
				pthread_mutex_lock(&rules->death_mutex);
				pthread_mutex_lock(&rules->print_mutex);
				if (!rules->someone_died[0])
				{
					rules->someone_died[0] = 1;
					if (!rules->death_printed)
						rules->death_printed = 1;
				}
				pthread_mutex_unlock(&rules->print_mutex);
				pthread_mutex_unlock(&rules->death_mutex);
				break ;
			}
		}
	}
	return (NULL);
}
