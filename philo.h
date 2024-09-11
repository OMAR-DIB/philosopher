/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:47:32 by odib              #+#    #+#             */
/*   Updated: 2024/09/12 11:26:53 by odib             ###   ########.fr       */
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
	t_data			*sim_info;     		// Pointer to the shared simulation information.
}	t_philosopher;

/*		philo_init		*/
pthread_mutex_t	*init_forks(t_data *data);
t_philosopher	*init_philo(t_data *data, pthread_mutex_t **forks);
void			init_data(t_data *data, char **av);

/*		philo_simulation		*/ 
void			*run_philosopher(void *philosopher);
void			start_simulation(t_data *data, t_philosopher *philo);
int				check_simulation_stop(t_data *data);

/*		philo_monitor		*/ 
void			*monitor_philosophers(void *arg);

/*		philo_print		*/ 
int				print_sim_info(t_philosopher *philo, char action);

/*		philo_action		*/ 
void			philo_eat(t_philosopher *philo);
void			philo_sleep(t_philosopher *philo);
void			philo_think(t_philosopher *philo);

/*		philo_utils		*/ 
long long 		current_time();
void			sleep_for(int duration);
int				ft_atoi(char *nptr);
int				ft_max(int a, int b);
int				ft_min(int a, int b);

#endif
