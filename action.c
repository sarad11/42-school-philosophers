/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:19:18 by sardomin          #+#    #+#             */
/*   Updated: 2025/05/23 18:19:46 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_any_philo_death(t_thread_philo **philo)
{
	long long	timestamp;
	int			nb_meals_to_eat;
	int			i;

	i = 0;
	nb_meals_to_eat = (*philo)[0].rules->nb_times_philo_must_eat;
	pthread_mutex_lock(&(*philo)[0].rules->death_mutex);
	if ((*philo)[0].rules->someone_died[0])
	{
		if ((*philo)[0].rules->nb_times_philo_must_eat \
		&& (*philo)[0].rules->philos_fed \
		&& ((*philo)[0].rules->philos_fed < nb_meals_to_eat))
		{
			ft_print_philo_action(&(*philo)[(*philo)[0].rules->someone_died[1] - 1], " died");
		}
		pthread_mutex_unlock(&(*philo)[0].rules->death_mutex);
		return (1);
	}
	else
	{
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
				ft_print_philo_action(&(*philo)[i], " died");
				pthread_mutex_unlock(&(*philo)[0].rules->death_mutex);
				return (1);
			}
			i++;
		}
	}
	pthread_mutex_unlock(&(*philo)[0].rules->death_mutex);
	return (0);
}

int	ft_take_forks(t_thread_philo *philo)
{
	if (philo->rules->someone_died[0])
		return (1);
	pthread_mutex_lock(philo->left_fork);
	if (ft_print_philo_action(philo, " has taken a fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (philo->rules->someone_died[0])
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	if (ft_print_philo_action(philo, " has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	ft_start_eating(t_thread_philo *philo)
{
	if (philo->rules->someone_died[0])
		return (1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
	philo->last_eaten = ft_timestamp_in_ms();
	philo->meals_eaten++;
	if (pthread_mutex_unlock(&philo->mutex) != 0)
		return (1);
	if (ft_print_philo_action(philo, " is eating"))
		return (1);
	usleep(philo->rules->time_to_eat * 1000);
	return (0);
}

void	*routine(void *arg)
{
	t_thread_philo	*philo;

	philo = (t_thread_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!(philo->rules->someone_died[0]))
	{
		if (ft_take_forks(philo))
			break ;
		if (ft_start_eating(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (ft_print_philo_action(philo, " is sleeping"))
			break ;
		usleep(philo->rules->time_to_sleep * 1000);
		if (ft_print_philo_action(philo, " is thinking"))
			break ;
	}
	return (NULL);
}
