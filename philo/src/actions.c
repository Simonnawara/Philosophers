/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:46:13 by sinawara          #+#    #+#             */
/*   Updated: 2024/12/10 15:08:28 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void philo_eat(int num_philo, int wait_time, t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_mutex);
    printf("%ldms Philo no %d is eating\n", get_timestamp(), num_philo);
    pthread_mutex_unlock(&philo->table->print_mutex);
    usleep(wait_time * 1000);
}

void philo_sleep(int num_philo, int wait_time, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
    printf("%ldms Philo no %d is sleeping\n", get_timestamp(), num_philo);
    pthread_mutex_unlock(&philo->table->print_mutex);
	usleep(wait_time * 1000);
}

void philo_think(int num_philo, t_philo *philo)
{
 	pthread_mutex_lock(&philo->table->print_mutex);
    printf("%ldms Philo no %d is thinking\n", get_timestamp(), num_philo);
    pthread_mutex_unlock(&philo->table->print_mutex);
}

void philo_die(int num_philo, t_philo *philo)
{
    pthread_mutex_lock(&philo->table->print_mutex);
    printf("%ldms Philo no %d has died\n", get_timestamp(), num_philo);
    pthread_mutex_unlock(&philo->table->print_mutex);
}

int check_death(t_philo *philo)
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
}

void *monitor_routine(void *arg)
{
    t_philo *philos;
    int i;
    int all_ate;

    philos = (t_philo *)arg;
    while (1)
    {
        i = 0;
        all_ate = 1;
        while (i < philos->table->num_philo)
        {
            if (check_death(&philos[i]))
                return (NULL);
            if (philos->table->amount_to_eat != -1 &&
                philos[i].meals_eaten < philos->table->amount_to_eat)
                all_ate = 0;
            i++;
        }
        if (philos->table->amount_to_eat != -1 && all_ate)
            return (NULL);
        usleep(1000);
    }
}