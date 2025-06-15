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
	int	i;
	
	i = 0;
	pthread_mutex_lock(&(*philo)[0].rules->death_mutex);
	if ((*philo)[0].rules->someone_died[0])
	{
	//	printf("print3");
		if ((*philo)[0].rules->nb_times_philo_must_eat && (*philo)[0].rules->philos_fed && ((*philo)[0].rules->philos_fed < (*philo)[0].rules->nb_times_philo_must_eat))
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
		//	printf("\nlock philo %i mutex\n", (*philo)[i].id);
			if ((*philo)[i].last_eaten)
				timestamp = ft_timestamp_in_ms() - (*philo)[i].last_eaten;
			else
				timestamp = ft_timestamp_in_ms() - (*philo)->rules->start_time;
				
		//	printf("\nunlock philo %i mutex\n", (*philo)[i].id);
			pthread_mutex_unlock(&(*philo)[i].mutex);
			if (timestamp > (*philo)[0].rules->time_to_die)
			{
				
				(*philo)[0].rules->someone_died[0] = 1;
				(*philo)[0].rules->someone_died[1] = i + 1;
		//		printf("print4\n");
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

void	*ft_death_checker(void *arg)
{
	t_thread_philo *philo;
	int	stop;
	
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
	t_thread_philo *philo;
	t_rules *rules;
	int	all_fed;
	int	i;
	
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
					break;		
				}
				pthread_mutex_unlock(&philo[i].mutex);
				i++;
				if (!all_fed)
					break;
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
				break;
			}
		}
	}
	return (NULL);
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
	/*pthread_mutex_lock(&philo->mutex);
	philo->last_eaten = ft_timestamp_in_ms();
	pthread_mutex_unlock(&philo->mutex);
//	printf("print5\n");
	if (ft_print_philo_action(philo, " is eating"))
		return (1);
	usleep(philo->rules->time_to_eat * 1000);
	return (0);*/
	
	if (philo->rules->someone_died[0])
		return (1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
//	printf("\neating lock philo %i mutex\n", philo->id);
	philo->last_eaten = ft_timestamp_in_ms();
	philo->meals_eaten++;
	if (pthread_mutex_unlock(&philo->mutex) != 0)
		return (1);
//	printf("\neating unlock philo %i mutex\n", philo->id);
	if (ft_print_philo_action(philo, " is eating"))
		return (1);
	usleep(philo->rules->time_to_eat * 1000);
	return (0);
	
}

void	*ft_routine(void *arg)
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
			break;
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
//		printf("print6\n");
		if (ft_print_philo_action(philo, " is sleeping"))
			break ;
		usleep(philo->rules->time_to_sleep * 1000);
//		printf("print7\n");
		if (ft_print_philo_action(philo, " is thinking"))
			break ;
	}
	return (NULL);
}
