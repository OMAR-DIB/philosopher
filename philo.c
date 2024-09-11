/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:25:53 by odib              #+#    #+#             */
/*   Updated: 2024/09/11 22:46:33 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "philo.h"

void free_data(t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->total_philosophers)
	{	
		pthread_mutex_destroy(&forks[i]);
		++i;
	}
    // Destroy all the mutexes
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->meals_lock);
    pthread_mutex_destroy(&data->simulation_lock);
    pthread_mutex_destroy(&data->last_meal_lock);
	
    // Free the memory allocated for t_data
	free(forks);
    free(data);
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }
	t_philosopher *philospher;
	t_data data;
	pthread_mutex_t *forks;
	init_data(&data, argv);
	forks = init_forks(&data);
	philospher = init_philo(&data, &forks);
	if (!philospher)
	{
		free(forks);
		return (EXIT_FAILURE);
	}
	start_simulation(&data, philospher);
    free_data(&data, forks);
    return 0;
}