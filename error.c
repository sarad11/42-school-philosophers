/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:39:03 by sardomin          #+#    #+#             */
/*   Updated: 2025/05/18 18:40:46 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_arg_error(int argc, char **argv)
{
	long long	start_time;
	
	start_time = 0;
	if (argc < 5 || argc > 6)
		ft_print_error("Error: Must be five or six arguments.\n", 38);
	else if (ft_atoi(argv[1]) == 0)
		ft_print_error("Error: There must be one philosopher.\n", 37);
	else if (ft_atoi(argv[1]) == 1)
	{
		start_time = ft_timestamp_in_ms();
		printf("%lld 1 has taken a fork\n", (ft_timestamp_in_ms() - start_time));
		usleep(ft_atoi(argv[2]));
		printf("%lld 1 died\n", (ft_timestamp_in_ms() - start_time));
	}
}
