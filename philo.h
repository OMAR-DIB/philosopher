/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:47:32 by odib              #+#    #+#             */
/*   Updated: 2024/09/12 10:55:49 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_LOG "%-5ld %2d has taken a fork\n"
# define EAT_LOG "%-5ld %2d is eating\n"
# define SLEEP_LOG "%-5ld %2d is sleeping\n"
# define THINK_LOG "%-5ld %2d is thinking\n"
# define DEATH_LOG "%-5ld %2d died\n"

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_philosophers;
	int				meals_required;
	int				meals_eaten;
	long long		simulation_start;
	bool			stop_simulation;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	simulation_lock;
	pthread_mutex_t	last_meal_lock;
}					t_data;

typedef struct s_philosopher
{
	int				id;
	int				meals_had;
	int				last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*sim_info;
}					t_philosopher;

/*		philo_init		*/
pthread_mutex_t		*init_forks(t_data *data);
t_philosopher		*init_philo(t_data *data, pthread_mutex_t **forks);
void				init_data(t_data *data, char **av);

/*		philo_simulation		*/
void				*run_philosopher(void *philosopher);
void				start_simulation(t_data *data, t_philosopher *philo);
int					check_simulation_stop(t_data *data);

/*		philo_monitor		*/
void				*monitor_philosophers(void *arg);

/*		philo_print		*/
int					print_sim_info(t_philosopher *philo, char action);

/*		philo_action		*/
void				philo_eat(t_philosopher *philo);
void				philo_sleep(t_philosopher *philo);
void				philo_think(t_philosopher *philo);

/*		philo_utils		*/
long long			current_time(void);
void				sleep_for(int duration);
int					ft_atoi(char *nptr);
int					ft_max(int a, int b);
int					ft_min(int a, int b);

#endif
