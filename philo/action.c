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

int	ft_take_forks2(t_thread_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (print_act(philo, " has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	if (ft_check_if_dead(philo->rules))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	if (print_act(philo, " has taken a fork"))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	ft_take_forks(t_thread_philo *philo)
{
	if (ft_check_if_dead(philo->rules))
		return (1);
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_act(philo, " has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		if (ft_check_if_dead(philo->rules))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
		if (print_act(philo, " has taken a fork"))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
	}
	else
	{
		if (ft_take_forks2(philo))
			return (1);
	}
	return (0);
}

int	ft_start_eating(t_thread_philo *philo)
{
	if (ft_check_if_dead(philo->rules))
		return (1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
	philo->last_eaten = ft_timestamp_in_ms();
	philo->meals_eaten++;
	if (pthread_mutex_unlock(&philo->mutex) != 0)
		return (1);
	if (print_act(philo, " is eating"))
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
	while (!ft_check_if_dead(philo->rules))
	{
		if (ft_take_forks(philo))
			break ;
		if (ft_start_eating(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (print_act(philo, " is sleeping"))
			break ;
		usleep(philo->rules->time_to_sleep * 1000);
		if (print_act(philo, " is thinking"))
			break ;
	}
	return (NULL);
}
