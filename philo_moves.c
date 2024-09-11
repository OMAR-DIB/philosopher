/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odib <odib@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:47:47 by odib              #+#    #+#             */
/*   Updated: 2024/09/11 23:48:35 by odib             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (check_simulation_stop(philo->sim_info))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	philo->meals_had += 1;
	pthread_mutex_lock(&philo->sim_info->last_meal_lock);
	philo->last_meal_time = print_sim_info(philo, 'E');
	pthread_mutex_unlock(&philo->sim_info->last_meal_lock);
	sleep_for(philo->sim_info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philosopher *philo)
{
	if (check_simulation_stop(philo->sim_info))
		return ;
	print_sim_info(philo, 'S');
	sleep_for(philo->sim_info->time_to_sleep);
}

void	thinking(t_philosopher *philo)
{
	if (check_simulation_stop(philo->sim_info))
		return ;
	print_sim_info(philo, 'T');
}
