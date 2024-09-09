// philo.c
#include "philo.h"


 void	free_data(t_philosopher *philos, pthread_mutex_t *m_forks)
{
	int	i;

	i = -1;
	while (++i < philos->sim_info->total_philosophers)
		pthread_mutex_destroy(&m_forks[i]);
	pthread_mutex_destroy(&philos->sim_info->simulation_lock);
	pthread_mutex_destroy(&philos->sim_info->last_meal_lock);
	pthread_mutex_destroy(&philos->sim_info->print_lock);
	pthread_mutex_destroy(&philos->sim_info->meals_lock);
	free(m_forks);
	free(philos);
}
int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }
	t_philosopher *philospher;
	t_data  data;
	pthread_mutex_t *forks;
	init_data(&data, argv);
	forks = init_forks(&data);
	philospher = init_philo(&data, &forks);
	start_simulation(&data, philospher);
   free_data(philospher, forks);

    return 0;
}
