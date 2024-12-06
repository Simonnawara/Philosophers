/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:18:08 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/06 16:09:08 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
argv[0] = program name
argv[1] = number_of_philosophers
argv[2] = time_to_die
argv[3] = time_to_eat
argv[4] = time_to_sleep
argv[5] = [number_of_times_each_philosopher_must_eat]
*/

/*
typedef struct s_table
{
	int	num_philo;
	int	num_fork;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	amount_to_eat;
}		t_table;
*/

// https://m4nnb3ll.medium.com/the-dining-philoshophers-an-introduction-to-multitasking-a-42-the-network-project-34e4141dbc49

void	validate_inputs(int argc, char **argv)
{
	if (argc < 4)
	{
		perror("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		perror("Not enough philosophers\n");
		exit(EXIT_FAILURE);
	}
}

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;

	table->num_philo = ft_atoi(argv[1]);
	table->num_fork = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 4)
		table->amount_to_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	validate_inputs(argc, argv);
	table = init_table(argc, argv);
	// I think I'd need to create a loop for every philosophers
	// that would create a thread for each one.
	printf("Makefile Works!\n");
	return (0);
}
