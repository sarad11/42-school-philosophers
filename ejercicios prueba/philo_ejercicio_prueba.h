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

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

/* para el ejercicio 5

typedef struct s_thread_data
{
    int id;
    pthread_mutex_t *mutex;
} t_thread_data;*/

/* para el ejercicio 6*/

typedef struct s_thread_data
{
    int id;
    int
    long long *counter;
    pthread_mutex_t *mutex;
} t_thread_data;

#endif