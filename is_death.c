/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:50:59 by sardomin          #+#    #+#             */
/*   Updated: 2025/06/20 18:51:14 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_any_dead(t_thread_philo **philo, int nb_meals_to_eat)
{
	if ((*philo)[0].rules->nb_times_philo_must_eat \
	&& (*philo)[0].rules->philos_fed \
	&& ((*philo)[0].rules->philos_fed < nb_meals_to_eat))
	{
		print_act(&(*philo)[(*philo)[0].rules->someone_died[1] - 1], " died");
	}
	pthread_mutex_unlock(&(*philo)[0].rules->death_mutex);
}

int	ft_one_is_dead(t_thread_philo **philo)
{
	long long	timestamp;
	int			i;

	i = 0;
	while (i < (*philo)[0].rules->nb_philos)
	{
		pthread_mutex_lock(&(*philo)[i].mutex);
		if ((*philo)[i].last_eaten)
			timestamp = ft_timestamp_in_ms() - (*philo)[i].last_eaten;
		else
			timestamp = ft_timestamp_in_ms() - (*philo)->rules->start_time;
		pthread_mutex_unlock(&(*philo)[i].mutex);
		if (timestamp > (*philo)[0].rules->time_to_die)
		{
			(*philo)[0].rules->someone_died[0] = 1;
			(*philo)[0].rules->someone_died[1] = i + 1;
			print_act(&(*philo)[i], " died");
			pthread_mutex_unlock(&(*philo)[0].rules->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_is_any_philo_death(t_thread_philo **philo)
{
	int			nb_meals_to_eat;

	nb_meals_to_eat = (*philo)[0].rules->nb_times_philo_must_eat;
	pthread_mutex_lock(&(*philo)[0].rules->death_mutex);
	if ((*philo)[0].rules->someone_died[0])
	{
		ft_any_dead(philo, nb_meals_to_eat);
		return (1);
	}
	else
	{
		if (ft_one_is_dead(philo) != 0)
			return (1);
	}
	pthread_mutex_unlock(&(*philo)[0].rules->death_mutex);
	return (0);
}
