/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:18:08 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/11 15:40:00 by sinawara         ###   ########.fr       */
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

t_table	*init_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
		
	table->philosophers = malloc(sizeof(pthread_t) * ft_atoi(argv[1])); // ft_atoi(argv[1]) = num_philo
	if (!table->philosophers)
	{
		free(table);
		return (NULL);
	}
	
	table->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!table->forks)
	{
		free(table->philosophers);
		free(table);
		return (NULL);
	}

	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->simulation_mutex, NULL);
	table->simulation_running = 1;
	table->num_philo = ft_atoi(argv[1]);
	table->num_fork = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->amount_to_eat = ft_atoi(argv[5]);
	else
		table->amount_to_eat = -1;
		
	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}

	gettimeofday(&table->simulation_start_time, NULL);
	return (table);
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

void *philo_routine(void *arg)
{
    t_philo *philo;
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

    philo = (t_philo *)arg;
    while (check_simulation_status(philo->table))
    {
		print_status(philo, "is thinking");
		usleep(1000);

		if (!check_simulation_status(philo->table))
			break ;
        
        if (philo->id % 2 == 0)
        {
			first_fork = &philo->table->forks[philo->id - 1];
 			second_fork = &philo->table->forks[philo->id % philo->table->num_philo];
		}
        else
        {
			first_fork = &philo->table->forks[philo->id % philo->table->num_philo];
    		second_fork = &philo->table->forks[philo->id - 1];
        }
       
		// lock forks
		pthread_mutex_lock(first_fork);
		print_status(philo, "Has taken a fork");
		pthread_mutex_lock(second_fork);
		print_status(philo, "Has taken a fork");

		// Eat
		pthread_mutex_lock(&philo->meal_mutex);
		gettimeofday(&philo->last_meal_time, NULL);
		pthread_mutex_unlock(&philo->meal_mutex);

		print_status(philo, "is eating");
		smart_sleep(philo->table->time_to_eat);
        philo->meals_eaten++;
		
		// Realease forks
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);

		// Sleep
		print_status(philo, "is sleeping");
		smart_sleep(philo->table->time_to_sleep);
    }
	return(NULL);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	t_philo *philo;
	pthread_t monitor;
	int	i;
	
	validate_inputs(argc, argv);   // checks if all inputs are correct before proceeding
	table = init_table(argc, argv); // initiates table structre
	if (!table)
		exit(EXIT_FAILURE);
	philo = init_philo(table); // initiate philosophers structure
	if (!philo)
	{
		free(table->philosophers);
		free(table->forks);
		free(table);
		exit(EXIT_FAILURE);
	}
	if (table->num_philo == 1)
	{
		usleep(philo->table->time_to_die);
		//smart_sleep(philo->table->time_to_die);
		print_status(philo, "Has died");
		exit(1);
	}
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philosophers[i], NULL, philo_routine, &philo[i]) != 0) //creates a thread per philosophers
		{
			stop_simulation(table);
			while(--i >= 0)
				pthread_join(table->philosophers[i], NULL);
			cleanup_resources(table, philo);
			exit(EXIT_FAILURE);
		}
		usleep(1000); // prevents deadlocks by staggering philosophers's start time
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philo) != 0)
	{
		stop_simulation(table);
		i = 0;
		while(i < table->num_philo)
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
