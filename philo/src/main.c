/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:18:08 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/12 17:33:36 by sinawara         ###   ########.fr       */
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
		ft_putendl_fd("Error: Time values cannot be negative", 2);
		exit(EXIT_FAILURE);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		ft_putendl_fd("Error: Number of times to eat must be positive", 2);
		exit(EXIT_FAILURE);
	}
}

t_philo	*init_philo(t_table *table)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < table->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].table = table;
		gettimeofday(&philo[i].last_meal_time, NULL);
		pthread_mutex_init(&philo[i].meal_mutex, NULL);
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_table		*table;
	t_philo		*philo;
	pthread_t	monitor;
	int			i;

	validate_inputs(argc, argv);
	table = init_table(argc, argv);
	if (!table)
		exit(EXIT_FAILURE);
	philo = init_philo(table);
	if (!philo)
	{
		free(table->philosophers);
		free(table->forks);
		free(table);
		exit(EXIT_FAILURE);
	}
	if (table->num_philo == 1)
	{
		usleep(table->time_to_die * 1000);
		printf("%dms 1 has died\n", table->time_to_die);
		exit(1);
	}
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philosophers[i], NULL, philo_routine,
				&philo[i]) != 0)
		{
			stop_simulation(table);
			while (--i >= 0)
				pthread_join(table->philosophers[i], NULL);
			cleanup_resources(table, philo);
			exit(EXIT_FAILURE);
		}
		usleep(1000);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
	{
		stop_simulation(table);
		i = 0;
		while (i < table->num_philo)
			pthread_join(table->philosophers[i++], NULL);
		cleanup_resources(table, philo);
		return (1);
	}
	pthread_join(monitor, NULL);
	stop_simulation(table);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philosophers[i], NULL);
		i++;
	}
	cleanup_resources(table, philo);
	return (0);
}
