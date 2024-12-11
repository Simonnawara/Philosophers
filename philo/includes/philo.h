#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <libc.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_table
{
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	simulation_mutex;
	struct timeval	simulation_start_time;
	int				simulation_running;
	int				num_philo;
	int				num_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				amount_to_eat;
}					t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	struct timeval	last_meal_time;
	t_table			*table;
}					t_philo;

// main.c //
void				validate_inputs(int argc, char **argv);
t_table				*init_table(int argc, char **argv);
t_philo				*init_philo(t_table *table);
void				*philo_routine(void *arg);

// actions.c //
void				print_status(t_philo *philo, char *status);
void				*monitor_routine(void *arg);
void				cleanup_resources(t_table *table, t_philo *philo);
int					check_simulation_status(t_table *table);
void				stop_simulation(t_table *table);

// time.c //
long				get_timestamp(void);
void				smart_sleep(long duration);
long				get_time_diff(struct timeval *t1, struct timeval *t2);

// utils.c //
int					ft_atoi(const char *str);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);

#endif