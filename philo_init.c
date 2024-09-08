/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:30:48 by odib              #+#    #+#             */
/*   Updated: 2024/09/09 11:37:25 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, char **av)
{
	data->total_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals_required = ft_atoi(av[5]);
	else
		data->meals_required = -1;
	data->meals_eaten = 0;
	data->simulation_start = current_time();
	data->stop_simulation = false;
	pthread_mutex_init(&data->last_meal_lock, NULL);
	pthread_mutex_init(&data->meals_lock, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->simulation_lock, NULL);
}

t_philosopher	*init_philo(t_data *data, pthread_mutex_t **forks)
{
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher) * data->total_philosophers);
	i = 0;
	while (i < data->total_philosophers)
	{
		philo[i].id = i + 1;
		philo[i].meals_had = 0;
		philo[i].last_meal_time = data->simulation_start;
		philo[i].left_fork = &(*forks)[i];
		philo[i].right_fork = &(*forks)[(i + 1) % data->total_philosophers];
		philo[i].sim_info = data;
		i++;
	}
	return (philo);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;					

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->total_philosophers);
	if (!forks)
		return (NULL);
	while (i < data->total_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}