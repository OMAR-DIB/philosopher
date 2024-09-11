/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 23:19:15 by odib              #+#    #+#             */
/*   Updated: 2024/09/12 10:55:01 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation_stop(t_data *data)
{
	pthread_mutex_lock(&data->simulation_lock);
	if (data->stop_simulation == true)
	{
		pthread_mutex_unlock(&data->simulation_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->simulation_lock);
	return (0);
}

void	*run_philosopher(void *philosopher)
{
	t_philosopher	*philo;

	philo = philosopher;
	if (philo->sim_info->total_philosophers == 1)
	{
		print_sim_info(philo, 'F');
		usleep(philo->sim_info->time_to_die * 1000);
		// print_data(philo->sim_info, philo->id, "died");
		return (NULL);
	}
	while (!check_simulation_stop(philo->sim_info))
	{
		philo_eat(philo);
		if (philo->meals_had == philo->sim_info->meals_required)
		{
			pthread_mutex_lock(&philo->sim_info->meals_lock);
			philo->sim_info->meals_eaten += 1;
			pthread_mutex_unlock(&philo->sim_info->meals_lock);
            return (NULL);
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	start_simulation(t_data *data, t_philosopher *philo)
{
	pthread_t	*seat;
	pthread_t	manage;
	int			i;

	seat = malloc(sizeof(pthread_t) * data->total_philosophers);
	i = -1;
	while (++i < data->total_philosophers)
		pthread_create(seat + i, NULL, run_philosopher, &philo[i]);
	pthread_create(&manage, NULL, monitor_philosophers, philo);
	i = -1;
	while (++i < data->total_philosophers)
		pthread_join(seat[i], NULL);
	pthread_join(manage, NULL);
	free(seat);
}
