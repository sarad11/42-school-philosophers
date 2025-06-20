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

int	ft_check_functions(int argc, char **argv)
{
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (0);
	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) == 0 || ft_atoi(argv[1]) == 1)
	{
		ft_arg_error(argc, argv);
		return (1);
	}
	return (0);
}
