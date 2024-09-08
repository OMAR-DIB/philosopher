// philo.c
#include "philo.h"


// void start_simulation(t_data *data) {
//     pthread_t monitor_thread;

//     for (int i = 0; i < data->num_philosophers; i++) {
//         pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]);
//     }

//     pthread_create(&monitor_thread, NULL, monitor_routine, data);

//     for (int i = 0; i < data->num_philosophers; i++) {
//         pthread_join(data->philosophers[i].thread, NULL);
//     }
//     pthread_join(monitor_thread, NULL);
// }

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
   // cleanup(&data);

    return 0;
}
