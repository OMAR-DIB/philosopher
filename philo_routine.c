// philo_routine.c
#include "philo.h"
void *philosopher_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;

    while (!data->dead) {
        // Thinking
        print_status(data, philo->id, "is thinking");

        // Picking up forks
        pthread_mutex_lock(philo->left_fork);
        print_status(data, philo->id, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_status(data, philo->id, "has taken a fork");

        // Eating
        print_status(data, philo->id, "is eating");
        philo->last_meal = current_time();
        philo->times_eaten++;
        sleep_for(data->time_to_eat);

        // Putting down forks
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Sleeping
        print_status(data, philo->id, "is sleeping");
        sleep_for(data->time_to_sleep);
    }
    return NULL;
}

void *monitor_routine(void *arg) {
    t_data *data = (t_data *)arg;

    while (!data->dead) {
        for (int i = 0; i < data->num_philosophers; i++) {
            if (current_time() - data->philosophers[i].last_meal > data->time_to_die) {
                print_status(data, data->philosophers[i].id, "died");
                data->dead = 1;
                break;
            }
        }
        usleep(1000); // Sleep for 1 ms to reduce CPU usage
    }
    return NULL;
}


void cleanup(t_data *data) {
    for (int i = 0; i < data->num_philosophers; i++) {
        pthread_mutex_destroy(&data->forks[i]);
    }
    pthread_mutex_destroy(&data->print_lock);
    free(data->forks);
    free(data->philosophers);
}