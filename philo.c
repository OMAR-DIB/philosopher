


#include "philo.h"

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }
	t_philosopher *philospher;
	t_data *data;
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
    free_data(philospher, forks);
    return 0;
}
