// philo_init.c
#include "philo.h"

void    init_data(t_data *data, int ac, char **av)
{
    data->num_philosophers = atoi(av[1]);
    data->time_to_die = atoi(av[2]);
    data->time_to_eat = atoi(av[3]);
    data->time_to_sleep = atoi(av[4]);
    data->num_times_to_eat = (ac == 6) ? atoi(av[5]) : -1;
    data->start_time = current_time();
    data->dead = 0;
    pthread_mutex_init(&data->print_lock, NULL);
    init_philo(data);
}
void init_philo(t_data *data)
{
    data->philosophers = malloc (sizeof(t_philosopher) * data->num_philosophers);
    data->forks = malloc (sizeof(pthread_mutex_t) * data->num_philosophers);
    int i;

    i = 0;
    while (i < data->num_philosophers)
    {
        pthread_mutex_init(&data->forks[i],NULL);
        data->philosophers[i].id = i + 1;
        data->philosophers[i].last_meal = data -> start_time;
        data->philosophers[i].times_eaten = 0;
        data->philosophers[i].left_fork = &data->forks[i];
        data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
        data->philosophers[i].data = data;
        i++;
    }
}


// void init_data(t_data *data, int argc, char **argv) {
//     data->num_philosophers = atoi(argv[1]);
//     data->time_to_die = atoi(argv[2]);
//     data->time_to_eat = atoi(argv[3]);
//     data->time_to_sleep = atoi(argv[4]);
//     data->num_times_to_eat = (argc == 6) ? atoi(argv[5]) : -1;
//     data->dead = 0;
//     data->start_time = current_time();

//     data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
//     data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
//     pthread_mutex_init(&data->print_lock, NULL);

//     for (int i = 0; i < data->num_philosophers; i++) {
//         pthread_mutex_init(&data->forks[i], NULL);
//         data->philosophers[i].id = i + 1;
//         data->philosophers[i].times_eaten = 0;
//         data->philosophers[i].last_meal = data->start_time;
//         data->philosophers[i].left_fork = &data->forks[i];
//         data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
//         data->philosophers[i].data = data;
//     }
// }
