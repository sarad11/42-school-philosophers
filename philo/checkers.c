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

int	ft_check_if_dead(t_rules *rules)
{
	int	dead;

	pthread_mutex_lock(&rules->s_died_mutex);
	dead = rules->someone_died[0];
	pthread_mutex_unlock(&rules->s_died_mutex);
	return (dead);
}

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

void	ft_all_fed_no_death(t_rules *rules)
{
	pthread_mutex_lock(&rules->print_mutex);
	pthread_mutex_lock(&rules->death_mutex);
	if (!ft_check_if_dead(rules))
	{
		pthread_mutex_lock(&rules-> s_died_mutex);
		rules->someone_died[0] = 1;
		pthread_mutex_unlock(&rules-> s_died_mutex);
		if (!rules->death_printed)
			rules->death_printed = 1;
	}
	pthread_mutex_unlock(&rules->death_mutex);
	pthread_mutex_unlock(&rules->print_mutex);
}

void	ft_meals_chk(t_thread_philo *philo, t_rules *rules, int i, int fed)
{
	while (!ft_check_if_dead(rules))
	{
		fed = 1;
		i = 0;
		while (i < rules->nb_philos)
		{
			pthread_mutex_lock(&philo[i].mutex);
			if (philo[i].meals_eaten < rules->nb_times_philo_must_eat)
				fed = 0;
			pthread_mutex_unlock(&philo[i].mutex);
			if (!fed)
				break ;
			i++;
		}
		if (fed)
		{
			ft_all_fed_no_death(rules);
			break ;
		}
		usleep (1000);
	}
}

void	*ft_fed_checker(void *arg)
{
	t_thread_philo	*philo;
	t_rules			*rules;
	int				i;
	int				all_fed;

	i = 0;
	all_fed = 1;
	philo = (t_thread_philo *)arg;
	rules = philo[0].rules;
	if (!philo || !rules || rules->nb_philos <= 0)
		return (NULL);
	if (rules->nb_times_philo_must_eat > 0)
	{
		ft_meals_chk(philo, rules, i, all_fed);
	}
	return (NULL);
}
