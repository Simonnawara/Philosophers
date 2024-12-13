/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:12:26 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/13 11:19:30 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	validate_inputs(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Invalid number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		ft_putendl_fd("Not enough philosophers\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
	{
		ft_putendl_fd("Error: Values cannot be negative", 2);
		exit(EXIT_FAILURE);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		ft_putendl_fd("Error: Number of times to eat must be positive", 2);
		exit(EXIT_FAILURE);
	}
}
