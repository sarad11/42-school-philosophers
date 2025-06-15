/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:56:00 by sardomin          #+#    #+#             */
/*   Updated: 2025/05/18 13:56:16 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print_philo_action(t_thread_philo *philo, char *message_to_print)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!philo->rules->someone_died[0])
	{
		timestamp = ft_timestamp_in_ms() - philo-> rules->start_time;
		if (!philo->rules->someone_died[0])
			printf("%lld %i %s\n", timestamp, philo->id, message_to_print);
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return (0);
	}
	else
	{
		if (philo->last_eaten)
			timestamp = ft_timestamp_in_ms() - philo->last_eaten;
		
		else
			timestamp = ft_timestamp_in_ms() - philo->rules->start_time;
		if (!(philo->rules)->death_printed)
		{
			printf("%lld %i %s\n", timestamp, philo->id, message_to_print);
			pthread_mutex_unlock(&philo->rules->print_mutex);		
		}
		else
		{
			pthread_mutex_unlock(&philo->rules->print_mutex);
			return (1);
		}
		philo->rules->death_printed = 1;
		return (1);
	}
	return (0);
}

void	ft_print_error(char *str, int n)
{
	write(2, str, n);
}

void	ft_print_rules(t_rules *rules)
{
	printf("nb_philos: %i\n", rules->nb_philos);
	printf("nb_forks: %i\n", rules->nb_forks);
	printf("time_to_die: %i\n", rules->time_to_die);
	printf("time_to_sleep: %i\n", rules->time_to_sleep);
	printf("time_to_eat: %i\n", rules->time_to_eat);
	printf("start_time: %lld\n", rules->start_time);
	//printf("someone_died: %i\n\n", rules->someone_died);
	if (rules->nb_times_philo_must_eat)
		printf("nb_times_philo_must_eat: %i\n\n", rules->nb_times_philo_must_eat);
}

void	ft_print_philos(t_thread_philo *philos)
{
	int	i;
	int	size;

	i = 0;
	size = philos[0].rules->nb_philos;
	while (i < size)
	{
		printf("Philo id: %i\n", philos[i].id);
		printf("thread: %li\n", philos[i].thread);
		//printf("direccion del mutex: %p\n", (void *)&philos[i].mutex);
		printf("left_fork: %p\n", philos[i].left_fork);
		printf("right_fork: %p\n", philos[i].right_fork);
		printf("meals_eaten: %i\n", philos[i].meals_eaten);
		printf("last_eaten: %lld\n\n", philos[i].last_eaten);
		printf("rule->nb_philo: %i\n\n", philos[i].rules->nb_philos);
		i++;
	}
}
