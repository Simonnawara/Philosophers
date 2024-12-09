#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <libc.h>


typedef struct s_table
{
	pthread_t *philosophers;
	pthread_mutex_t *forks;
	int num_philo;
	int num_fork;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int amount_to_eat;
} t_table;

typedef struct s_philo
{
	int id;
	int	meals_eaten;
	struct timeval last_meal_time;
	t_table *table;
}	t_philo;

// utils.c //
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);

// actions.c //
void eat(int num_philo);
void think(int num_philo);
void sleeping(int num_philo);
void die(int num_philo);
int check_death(t_philo *philo);
void *monitor_routine(void *arg);

#endif