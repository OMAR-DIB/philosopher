/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:21:56 by odib              #+#    #+#             */
/*   Updated: 2024/09/11 23:24:54 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_sim_info(t_philosopher *philo, char action)
{
	size_t	current;
	size_t	time_spent;

	current = current_time();
	time_spent = current - philo->sim_info->simulation_start;
	pthread_mutex_lock(&philo->sim_info->print_lock);
	if (action == 'F') // 'F' for TAKING_FORK
		printf(FORK_LOG, time_spent, philo->id);
	else if (action == 'E') // 'E' for EATING
		printf(FORK_LOG FORK_LOG EAT_LOG, time_spent, \
					philo->id, time_spent, philo->id, \
					time_spent, philo->id);
	else if (action == 'S') // 'S' for SLEEPING
		printf(SLEEP_LOG, time_spent, philo->id);
	else if (action == 'D') // 'D' for DEAD
		printf(DEATH_LOG, time_spent, philo->id);
	else if (action == 'T') // 'T' for THINKING
		printf(THINK_LOG, time_spent, philo->id);
	pthread_mutex_unlock(&philo->sim_info->print_lock);
	return (current);
}

int	finish_meals_required(t_data *data)
{
	int	done;

	done = 0;
	pthread_mutex_lock(&data->meals_lock);
	if (data->meals_eaten == data->total_philosophers)
	{
		done = 1;
	}
	pthread_mutex_unlock(&data->meals_lock);
	return (done);
}

int	died_with_no_food(t_philosopher *philo)
{
	int	tik_tak;

	pthread_mutex_lock(&philo->sim_info->last_meal_lock);
	tik_tak = current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->sim_info->last_meal_lock);
	if (tik_tak > philo->sim_info->time_to_die)
	{
        return 1;
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
    t_data          *data;
    int              i;

	philo = (t_philosopher *)arg;
    data = philo[0].sim_info;
	while (!finish_meals_required(data))
	{
        i = 0;
        while (i < data->total_philosophers)
        {
            if (died_with_no_food(&philo[i]))
            {
               pthread_mutex_lock(&data->simulation_lock);
	            data->stop_simulation = true;
	            pthread_mutex_unlock(&data->simulation_lock);
				print_sim_info(&philo[i], 'D');
                return (NULL);
            }
            i++;
        }
		usleep(3000);
	}
	return (NULL);
}
