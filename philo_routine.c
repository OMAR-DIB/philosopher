
#include "philo.h"

void	print_data(t_data *data, int philosopher_id, const char *action)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%lld %d %s\n", current_time() - data->simulation_start,
		philosopher_id, action);
	pthread_mutex_unlock(&data->print_lock);
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
	while (!finish_meals_required(philo))
	{
        i = 0;
        while (i < data->total_philosophers)
        {
            if (died_with_no_food(philo))
            {
               pthread_mutex_lock(&data->simulation_lock);
	            data->stop_simulation = true;
	            pthread_mutex_unlock(&data->simulation_lock);
                return (NULL);
            }
            i++;
        }
		usleep(3000);
	}
	return (NULL);
}

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
	philo->last_meal_time = print_status(philo, 'E');
	pthread_mutex_unlock(&philo->sim_info->last_meal_lock);
	sleep_for(philo->sim_info->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philosopher *philo)
{
	if (stop(philo->sim_info))
		return ;
	print_status(philo, 'S');
	sleep_for(philo->sim_info->time_to_sleep);
}

void	thinking(t_philosopher *philo)
{
	if (stop(philo->sim_info))
		return ;
	print_status(philo, 'T');
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
	t_philosopher	*philo;

	philo = philosopher;
	if (philo->sim_info->total_philosophers == 1)
	{
		print_status(philo, 'F');
		usleep(philo->sim_info->time_to_die * 1000);
		// print_data(philo->sim_info, philo->id, "died");
		return (NULL);
	}
	while (!stop(philo->sim_info))
	{
		eating(philo);
		if (philo->meals_had == philo->sim_info->meals_required)
		{
			pthread_mutex_lock(&philo->sim_info->meals_lock);
			philo->sim_info->meals_eaten += 1;
			pthread_mutex_unlock(&philo->sim_info->meals_lock);
            return (NULL);
		}
		sleeping(philo);
		thinking(philo);
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
		pthread_create(seat + i, NULL, start, &philo[i]);
	pthread_create(&manage, NULL, philo_routine, philo);
	i = -1;
	while (++i < data->total_philosophers)
		pthread_join(seat[i], NULL);
	pthread_join(manage, NULL);
	free(seat);
}
