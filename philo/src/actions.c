/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:46:13 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/11 14:13:18 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void print_status(t_philo *philo, char *status)
{
    if (check_simulation_status(philo->table))
    {
        pthread_mutex_lock(&philo->table->print_mutex);
        printf("%ldms %d %s\n", get_timestamp(), philo->id, status);
        pthread_mutex_unlock(&philo->table->print_mutex);
    }
}

void *monitor_routine(void *arg)
{
    t_philo *philos;
    int i;
    struct timeval current_time;
    long time_since_last_meal;
    int all_ate_enough;

    philos = (t_philo *)arg;
    while (check_simulation_status(philos[0].table))
    {
        i = 0;
        all_ate_enough = 1;
        while (i < philos[0].table->num_philo)
        {
            pthread_mutex_lock(&philos[i].meal_mutex);
            gettimeofday(&current_time, NULL);
            time_since_last_meal = get_time_diff(&current_time, &philos[i].last_meal_time);
            
            if (time_since_last_meal > philos[0].table->time_to_die)
            {
                print_status(&philos[i], "died");
                stop_simulation(philos[0].table);
                pthread_mutex_unlock(&philos[i].meal_mutex);
                return (NULL);
            }
            
            if (philos[0].table->amount_to_eat != -1 && 
                philos[i].meals_eaten < philos[0].table->amount_to_eat)
                all_ate_enough = 0;
                
            pthread_mutex_unlock(&philos[i].meal_mutex);
            i++;
        }
        
        if (philos[0].table->amount_to_eat != -1 && all_ate_enough)
        {
            stop_simulation(philos[0].table);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}

void cleanup_resources(t_table *table, t_philo *philo)
{
    int i;

    i = 0;
    while (i < table->num_philo)
    {
        pthread_mutex_destroy(&table->forks[i]);
        pthread_mutex_destroy(&philo[i].meal_mutex);
        i++;
    }
    
    pthread_mutex_destroy(&table->print_mutex);
    pthread_mutex_destroy(&table->simulation_mutex);
    
    free(philo);
    free(table->philosophers);
    free(table->forks);
    free(table);
}




void philo_eat(int num_philo, int wait_time, t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_mutex);
    printf("%ldms %d is eating\n", get_timestamp(), num_philo);
    pthread_mutex_unlock(&philo->table->print_mutex);
    usleep(wait_time * 1000);
}

void philo_sleep(int num_philo, int wait_time, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
    printf("%ldms %d is sleeping\n", get_timestamp(), num_philo);
    pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(wait_time * 1000);
}

void philo_think(int num_philo, t_philo *philo)
{
 	pthread_mutex_lock(&philo->table->print_mutex);
    printf("%ldms %d is thinking\n", get_timestamp(), num_philo);
    pthread_mutex_unlock(&philo->table->print_mutex);
}

void philo_die(int num_philo, t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_mutex);
    printf("%ldms %d has died\n", get_timestamp(), num_philo);
    pthread_mutex_unlock(&philo->table->print_mutex);
}

/* int check_death(t_philo *philo)
{
    struct timeval current_time;
    long time_diff;

    gettimeofday(&current_time, NULL);
    time_diff = (current_time.tv_sec - philo->last_meal_time.tv_sec) * 1000 +
                (current_time.tv_usec - philo->last_meal_time.tv_usec) / 1000;
    
    if (time_diff > philo->table->time_to_die)
    {
        philo_die(philo->id, philo);
        return (1);
    }
    return (0);
} */