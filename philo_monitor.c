/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:21:56 by odib              #+#    #+#             */
/*   Updated: 2024/09/12 11:12:14 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal_completion(t_data *data)
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

int	detect_starvation(t_philosopher *philo)
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

void	*monitor_philosophers(void *arg)
{
	t_philosopher	*philo;
    t_data          *data;
    int              i;

	philo = (t_philosopher *)arg;
    data = philo[0].sim_info;
	while (!check_meal_completion(data))
	{
        i = 0;
        while (i < data->total_philosophers)
        {
            if (detect_starvation(&philo[i]))
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
