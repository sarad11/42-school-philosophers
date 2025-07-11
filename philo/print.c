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

int	ft_print_action2(t_thread_philo *philo, char *sms)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (philo->last_eaten)
		timestamp = ft_timestamp_in_ms() - philo->last_eaten;
	else
		timestamp = ft_timestamp_in_ms() - philo->rules->start_time;
	if (!(philo->rules)->death_printed)
	{
		printf("%lld %i %s\n", timestamp, philo->id, sms);
		philo->rules->death_printed = 1;
		pthread_mutex_unlock(&philo->rules->print_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return (1);
	}
	return (0);
}

int	print_act(t_thread_philo *philo, char *sms)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->rules->print_mutex);
	if (!ft_check_if_dead(philo->rules))
	{
		pthread_mutex_lock(&(philo)[0].rules->death_mutex);
		timestamp = ft_timestamp_in_ms() - philo-> rules->start_time;
		if (!ft_check_if_dead(philo->rules))
			printf("%lld %i %s\n", timestamp, philo->id, sms);
		pthread_mutex_unlock(&(philo)[0].rules->death_mutex);
		pthread_mutex_unlock(&philo->rules->print_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->rules->print_mutex);
		ft_print_action2(philo, sms);
		return (1);
	}
	return (0);
}

void	ft_print_error(char *str, int n)
{
	write(2, str, n);
}
