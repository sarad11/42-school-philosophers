/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sardomin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:09:57 by sardomin          #+#    #+#             */
/*   Updated: 2025/06/20 17:10:24 by sardomin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arguments(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				ft_print_error("Error: args must be numbers > 0.\n", 33);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_functions(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_check_arguments(argv) != 0)
			return (1);
		if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) == 1)
		{
			ft_arg_error(argc, argv);
			return (1);
		}
		if (argc == 6 && ft_atoi(argv[5]) == 0)
			return (1);
		return (0);
	}
	if (argc < 5 || argc > 6)
	{
		ft_arg_error(argc, argv);
		return (1);
	}
	return (0);
}
