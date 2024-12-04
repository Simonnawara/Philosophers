/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:18:08 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/04 15:39:56 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

/*
argv[0] = program name
argv[1] = number_of_philosophers
argv[2] = time_to_die
argv[3] = time_to_eat
argv[4] = time_to_sleep
argv[5] = [number_of_times_each_philosopher_must_eat]
*/

void validate_input(int argc, char **argv)
{
	if (argc < 4)
	{
		perror("Invalid number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if (atoi(argv[1]) < 1)
	{
		perror("Not enough philosophers\n");
		exit(EXIT_FAILURE);
	}
}

int main(void)
{
	printf("Makefile Works!\n");
	return (0);
}