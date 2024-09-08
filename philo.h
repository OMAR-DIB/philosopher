// philo.h
#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
typedef struct s_data
{
	int				time_to_die;        // Time (in ms) before a philosopher dies if they don't start eating.
	int				time_to_eat;        // Time (in ms) a philosopher spends eating.
	int				time_to_sleep;      // Time (in ms) a philosopher spends sleeping.
	int				total_philosophers; // Total number of philosophers.
	int				meals_required;     // Minimum number of meals each philosopher must eat (optional).
	int				meals_eaten;        // Count of meals eaten by all philosophers.
	long long		simulation_start;   // Start time of the simulation in milliseconds.
	bool			stop_simulation;    // Flag to stop the simulation.
	pthread_mutex_t	print_lock;         // Mutex to lock printing status messages.
	pthread_mutex_t	meals_lock;         // Mutex to lock the meals_eaten variable.
	pthread_mutex_t	simulation_lock;    // Mutex to lock the stop_simulation variable.
	pthread_mutex_t	last_meal_lock;     // Mutex to lock the last meal time of each philosopher.
}	t_data;

typedef struct s_philosopher
{
	int				id;                 // Philosopher's ID.
	int				meals_had;          // Number of meals this philosopher has had.
	int				last_meal_time;     // Timestamp of the last meal in milliseconds.
	pthread_mutex_t	*left_fork;         // Pointer to the mutex for the left fork.
	pthread_mutex_t	*right_fork;        // Pointer to the mutex for the right fork.
	t_data			*sim_info;     // Pointer to the shared simulation information.
}	t_philosopher;

// Function prototypes
void	init_data(t_data *data, char **av);
t_philosopher	*init_philo(t_data *data, pthread_mutex_t **forks);
pthread_mutex_t	*init_forks(t_data *data);
int	ft_atoi(const char *nptr);
long long current_time();
int	stop(t_data *data);

void sleep_for(int duration);


void print_status(t_data *data, int id, const char *status);

void start_simulation(t_data *data, t_philosopher *philo);
// //void init_data(t_data *data, int argc, char **argv);
// void cleanup(t_data *data);

#endif
