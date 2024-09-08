// philo_routine.c
#include "philo.h"
// void *philosopher_routine(void *arg) {
//     t_philosopher *philo = (t_philosopher *)arg;
//     t_data *data = philo->data;

//     while (!data->dead) {
//         // Thinking
//         print_status(data, philo->id, "is thinking");

//         // Picking up forks
//         pthread_mutex_lock(philo->left_fork);
//         print_status(data, philo->id, "has taken a fork");
//         pthread_mutex_lock(philo->right_fork);
//         print_status(data, philo->id, "has taken a fork");

//         // Eating
//         print_status(data, philo->id, "is eating");
//         philo->last_meal = current_time();
//         philo->times_eaten++;
//         sleep_for(data->time_to_eat);

//         // Putting down forks
//         pthread_mutex_unlock(philo->right_fork);
//         pthread_mutex_unlock(philo->left_fork);

//         // Sleeping
//         print_status(data, philo->id, "is sleeping");
//         sleep_for(data->time_to_sleep);
//     }
//     return NULL;
// }

void	eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (stop(philo->sim_info))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	philo->meals_had += 1;
	pthread_mutex_lock(&philo->sim_info->last_meal_lock);
	philo->last_meal_time = current_time();
	print_status(philo->sim_info, philo->id, "eating");
	pthread_mutex_unlock(&philo->sim_info->last_meal_lock);
	sleep_for(philo->sim_info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void thinking(t_philosopher*philo)
{
	if (stop(philo->sim_info))
	{
		return ;
	}
	print_status(philo->sim_info,philo->id,"thinking");
}

void	sleeping(t_philosopher *philo)
{
	if (stop(philo->sim_info))
		return ;
	print_status(philo->sim_info,philo->id,"sleeping");
	sleep_for(philo->sim_info->time_to_sleep);
}

int	stop(t_data *data)
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

void	*start(void *philosopher)
{
	t_philosopher *philo;

	philo = philosopher;
	if (philo->sim_info->total_philosophers == 1)
	{
		print_status(philo->sim_info, philo->id, "has taken a fork");
		usleep(philo->sim_info->time_to_die * 1000);
        print_status(philo->sim_info, philo->id, "died");
		return (NULL);
	}
	while (!stop(philo->sim_info))
	{
		eating(philo);
		if (philo->last_meal_time == philo->sim_info->meals_required)
		{
			pthread_mutex_lock(&philo->sim_info->meals_eaten);
			philo->sim_info->meals_eaten += 1;
			pthread_mutex_unlock(&philo->sim_info->meals_eaten);
		}
		thinking(philo);
		sleeping(philo);
	}
	return (NULL);
}
// void *philo_routine(){

// }
void	start_simulation(t_data *data, t_philosopher *philo)
{
	pthread_t	*seat;
	// pthread_t	manage;
	int	i;

	seat = (pthread_t *)malloc(sizeof(pthread_t) * data->total_philosophers);
	i = 0; 
	while( i < data->total_philosophers)
	{
		pthread_create(seat + i,NULL, start, &philo[i]);
		i++;
	}
	// pthread_create(&manage, NULL, philo_routine, philo);
	i = 0;
	while (i < philo->sim_info->total_philosophers)
	{
		pthread_join(seat[i], NULL);
		i++;
	}
	// pthread_join(manage, NULL);
	free(seat);
}

// void cleanup(t_data *data) {
//     for (int i = 0; i < data->num_philosophers; i++) {
//         pthread_mutex_destroy(&data->forks[i]);
//     }
//     pthread_mutex_destroy(&data->print_lock);
//     free(data->forks);
//     free(data->philosophers);
// }