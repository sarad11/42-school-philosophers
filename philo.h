/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saradominguez <saradominguez@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:37:50 by saradomingu       #+#    #+#             */
/*   Updated: 2025/05/17 21:41:06 by saradomingu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int	nb_philos;
	int	nb_forks;
	int	nb_times_philo_must_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	long long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	int	*someone_died;
	int	death_printed;
	int	*forks_mutex_destroyed;
	int	print_mutex_destroyed;
	int	death_mutex_destroyed;
}	t_rules;

typedef struct s_thread_philo
{
	int	id;
	pthread_t	thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int	mutex_destroyed;
	int	meals_eaten;
	long long	last_eaten;
	t_rules		*rules;
}	t_thread_philo;

//main
//init.c
int		ft_init(char **argv, t_rules **rules, t_thread_philo **philos);
int		ft_init_rules(int argc, char **argv, t_rules **rules);
int		ft_init_philos(char **argv, t_thread_philo **philos, t_rules *rules);
//init_mutexes.c
int		ft_init_rules_mutexes(t_rules **rules);
int		ft_init_forks(t_rules **rules);
int		ft_init_print_mutex(t_rules **rules);
int		ft_init_death_mutex(t_rules **rules);
//thread.c
int		ft_start_threads(t_thread_philo *philos);
int		ft_join_threads(int nb_philos, t_thread_philo *philos);
int		ft_start_death_philo_threads(t_thread_philo *philos, pthread_t *death_thread);
int		ft_join_death_philo_thread(pthread_t death_thread);
//action.c
void	*ft_routine(void *arg);
int	ft_take_forks(t_thread_philo *philo);
int	ft_start_eating(t_thread_philo *philo);
void	*ft_death_checker(void *arg);
int	ft_is_any_philo_death(t_thread_philo **philo);
//utils.c
int		ft_atoi(const char *nptr);
long long	ft_timestamp_in_ms(void);
//print.c
void	ft_print_rules(t_rules *rules);
void	ft_print_philos(t_thread_philo *philos);
int	ft_print_philo_action(t_thread_philo *philo, char *message_to_print);
void	ft_print_error(char *str, int n);
//error.c
void	ft_arg_error(int argc, char **argv);
//destroy.c
int		ft_destroy_mutex(t_thread_philo **philos);
int		ft_destroy_philo_mutex(t_thread_philo **philos, int i);
int		ft_destroy_forks(t_thread_philo **philos, int i);
int		ft_destroy_print_mutex(t_thread_philo **philos);
int		ft_destroy_death_mutex(t_thread_philo **philos);
//free.c
void	ft_free(t_thread_philo **philo);
#endif
