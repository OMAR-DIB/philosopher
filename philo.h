/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:47:32 by odib              #+#    #+#             */
/*   Updated: 2024/09/11 10:29:02 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

# define FORK_LOG "%-5ld %2d has taken a fork\n"
# define EAT_LOG "%-5ld %2d is eating\n"
# define SLEEP_LOG "%-5ld %2d is sleeping\n"
# define THINK_LOG "%-5ld %2d is thinking\n"
# define DEATH_LOG "%-5ld %2d died\n"

typedef struct s_data
{
	int				time_to_die;        // time_of_death;   Time (in ms) before a philosopher dies if they don't start eating.
	int				time_to_eat;        // time_of_eating;   Time (in ms) a philosopher spends eating.
	int				time_to_sleep;      // time_of_sleeping;   Time (in ms) a philosopher spends sleeping.
	int				total_philosophers; // total_philo;    Total number of philosophers.
	int				meals_required;     // meals_to_eat;   Minimum number of meals each philosopher must eat (optional).
	int				meals_eaten;        // meals_repeated;   Count of meals eaten by all philosophers.
	long long		simulation_start;   // start_time;  Start time of the simulation in milliseconds.
	bool			stop_simulation;    // stop_dinner;     Flag to stop the simulation.
	pthread_mutex_t	print_lock;         // 	m_print_status;   Mutex to lock printing status messages.
	pthread_mutex_t	meals_lock;         // m_meals_repeated;   Mutex to lock the meals_eaten variable.
	pthread_mutex_t	simulation_lock;    // 	m_stop_dinner;   Mutex to lock the stop_simulation variable.
	pthread_mutex_t	last_meal_lock;     // m_last_meal;   Mutex to lock the last meal time of each philosopher.
}	t_data;

typedef struct s_philosopher
{
	int				id;                 // philo_name;   Philosopher's ID.
	int				meals_had;          // eat_again;   Number of meals this philosopher has had.
	int				last_meal_time;     // last_meal;   Timestamp of the last meal in milliseconds.
	pthread_mutex_t	*left_fork;         // *m_left_fork;   Pointer to the mutex for the left fork.
	pthread_mutex_t	*right_fork;        // *m_right_fork;   Pointer to the mutex for the right fork.
	t_data			*sim_info;     // *status;   Pointer to the shared simulation information.
}	t_philosopher;

// Function prototypes
void	init_data(t_data *data, char **av);
t_philosopher	*init_philo(t_data *data, pthread_mutex_t **forks);
pthread_mutex_t	*init_forks(t_data *data);
int	ft_atoi(const char *nptr);
long long current_time();
int	stop(t_data *data);

void sleep_for(int duration);


size_t	print_sim_info(t_philosopher *philo, char action);
void *philo_routine(void *arg);
void start_simulation(t_data *data, t_philosopher *philo);
// //void init_data(t_data *data, int argc, char **argv);
// void cleanup(t_data *data);

#endif
