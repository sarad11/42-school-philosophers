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
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	fed_mutex;
	long long		start_time;
	int				*someone_died;
	int				*forks_mutex_destroyed;
	int				nb_philos;
	int				nb_forks;
	int				nb_times_philo_must_eat;
	int				philos_fed;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				death_printed;
	int				print_mutex_destroyed;
	int				death_mutex_destroyed;
	int				fed_mutex_destroyed;
}	t_rules;

typedef struct s_thread_philo
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_rules			*rules;
	long long		last_eaten;
	int				id;
	int				mutex_destroyed;
	int				meals_eaten;
}	t_thread_philo;

//main
long long	ft_timestamp_in_ms(void);
//params_checkers.c
int			ft_check_functions(int argc, char **argv);
//init_philo_process.c
int			init(int ac, char **av, t_rules **rules, t_thread_philo **philo);
int			init2(char **argv, t_rules **rules, t_thread_philo **philos);
int			death(char *argv, t_thread_philo **philos, pthread_t *death_thread);
int			fed(char *argv, t_thread_philo **philos, pthread_t *death_thread);
int			join(char *argv, t_thread_philo **philos, pthread_t *death_thread);
//init.c
int			ft_init(char **argv, t_rules **rules, t_thread_philo **philos);
int			ft_init_rules(int argc, char **argv, t_rules **rules);
int			ft_init_rules2(int nb, int argc, char **argv, t_rules **rules);
int			ft_init_ph(char **argv, t_thread_philo **philos, t_rules *rules);
//init_mutexes.c
int			ft_init_rules_mutexes(t_rules **rules);
int			ft_init_forks(t_rules **rules);
int			ft_init_print_mutex(t_rules **rules);
int			ft_init_death_mutex(t_rules **rules);
int			ft_init_fed_mutex(t_rules **rules);
//thread.c
int			ft_start_threads(t_thread_philo *philos);
int			ft_death_threads(t_thread_philo *philos, pthread_t *death_thread);
int			ft_start_fed_threads(t_thread_philo *philos, pthread_t *fed_thread);
//join.c
int			ft_join_threads(int nb_philos, t_thread_philo *philos);
int			ft_join_death_philo_thread(pthread_t death_thread);
int			ft_join_fed_philo_thread(pthread_t fed_thread);
//action.c
void		*routine(void *arg);
int			ft_take_forks(t_thread_philo *philo);
int			ft_start_eating(t_thread_philo *philo);
//checkers.c
void		*ft_death_chk(void *arg);
void		*ft_fed_checker(void *arg);
//is_death.c
int			ft_is_any_philo_death(t_thread_philo **philo);
void		ft_any_dead(t_thread_philo **philo, int nb_meals_to_eat);
int			ft_one_is_dead(t_thread_philo **philo);
//utils.c
int			ft_atoi(const char *nptr);
//print.c
int			print_act(t_thread_philo *philo, char *sms);
int			ft_print_action2(t_thread_philo *philo, char *sms);
void		ft_print_error(char *str, int n);
//error.c
void		ft_arg_error(int argc, char **argv);
//destroy.c
int			ft_destroy_mutex(t_thread_philo **philos);
int			ft_destroy_philo_mutex(t_thread_philo **philos, int i);
int			ft_destroy_forks(t_thread_philo **philos, int i);
int			ft_destroy_print_mutex(t_thread_philo **philos);
int			ft_destroy_death_mutex(t_thread_philo **philos);
int			ft_destroy_fed_mutex(t_thread_philo **philos);
//free.c
void		ft_free(t_thread_philo **philo);
#endif
