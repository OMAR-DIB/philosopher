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
void print_data(t_data *data, int philosopher_id, const char *action) {
    pthread_mutex_lock(&data->print_lock);
    printf("%lld %d %s\n", current_time() - data->simulation_start, philosopher_id, action);
    pthread_mutex_unlock(&data->print_lock);
}

int finish_meals_required(t_philosopher *philo) {
    int done = 0;

    pthread_mutex_lock(&philo->sim_info->meals_lock);
    if (philo->sim_info->meals_required == philo->id) {
        done = 1;
    }
    pthread_mutex_unlock(&philo->sim_info->meals_lock);
    return done;
}

int died_with_no_food(t_philosopher *philo) {
    int tik_tak;

    pthread_mutex_lock(&philo->sim_info->last_meal_lock);
    tik_tak = current_time() - philo->last_meal_time;
    pthread_mutex_unlock(&philo->sim_info->last_meal_lock);

    if (tik_tak > philo->sim_info->time_to_die) {
        pthread_mutex_lock(&philo->sim_info->simulation_lock);
        if (!philo->sim_info->stop_simulation) {
            philo->sim_info->stop_simulation = true;
            print_data(philo->sim_info, philo->id, "died");
        }
        pthread_mutex_unlock(&philo->sim_info->simulation_lock);
        return 1;
    }
    return 0;
}

void *philo_routine(void *arg) {
    t_philosopher *philo = (t_philosopher *)arg;

    while (!finish_meals_required(philo) && !stop(philo->sim_info)) {
        if (died_with_no_food(philo)) {
            break;
        }
        sleep_for(3000);
    }
    return NULL;
}

void eating(t_philosopher *philo) {
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);

    if (stop(philo->sim_info)) {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return;
    }

    philo->meals_had += 1;
    pthread_mutex_lock(&philo->sim_info->last_meal_lock);
    philo->last_meal_time = current_time();
    print_data(philo->sim_info, philo->id, "eating");
    pthread_mutex_unlock(&philo->sim_info->last_meal_lock);

    sleep_for(philo->sim_info->time_to_eat);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void sleeping(t_philosopher *philo) {
    if (stop(philo->sim_info))
        return;

    print_data(philo->sim_info, philo->id, "sleeping");
    sleep_for(philo->sim_info->time_to_sleep);
}

void thinking(t_philosopher *philo) {
    if (stop(philo->sim_info))
        return;

    print_data(philo->sim_info, philo->id, "thinking");
}

int stop(t_data *data) {
    int result;

    pthread_mutex_lock(&data->simulation_lock);
    result = data->stop_simulation;
    pthread_mutex_unlock(&data->simulation_lock);

    return result;
}

void *start(void *philosopher) {
    t_philosopher *philo = (t_philosopher *)philosopher;

    if (philo->sim_info->total_philosophers == 1) {
        print_data(philo->sim_info, philo->id, "take a fork");
        usleep(philo->sim_info->time_to_die * 1000);
        print_data(philo->sim_info, philo->id, "died");
        return NULL;
    }

    while (!stop(philo->sim_info)) {
        eating(philo);
        if (philo->last_meal_time == philo->sim_info->meals_required) {
            pthread_mutex_lock(&philo->sim_info->meals_lock);
            philo->sim_info->meals_eaten += 1;
            pthread_mutex_unlock(&philo->sim_info->meals_lock);
        }
        thinking(philo);
        sleeping(philo);
    }
    return NULL;
}

void start_simulation(t_data *data, t_philosopher *philo) {
    pthread_t *seat;
    pthread_t manage;
    int i;

    seat = (pthread_t *)malloc(sizeof(pthread_t) * data->total_philosophers);

    for (i = 0; i < data->total_philosophers; i++) {
        pthread_create(&seat[i], NULL, start, &philo[i]);
    }
    pthread_create(&manage, NULL, philo_routine, philo);

    for (i = 0; i < data->total_philosophers; i++) {
        pthread_join(seat[i], NULL);
    }
    pthread_join(manage, NULL);
    free(seat);
}

// void print_status(t_data *data, int id, const char *status) {
//     pthread_mutex_lock(&data->print_lock);
//     if (!data->stop_simulation) {
//         printf("%lld %d %s\n", current_time() - data->simulation_start, id, status);
//     }
//     pthread_mutex_unlock(&data->print_lock);
// }

// size_t	print_status(t_philosopher *philo, char **action)
// {
// 	size_t	current_time;
// 	size_t	time_spent;

// 	current_time = get_current_time();
// 	time_spent = current_time - philo->sim_info->simulation_start;
// 	pthread_mutex_lock(&philo->sim_info->print_lock);
// 	if (action == "taking a fork")
// 		printf("%d , %d, taking a fork", time_spent, philo->id);
// 	else if (action == "eating")
// 	{
// 		printf("%d  %d has taken a fork\n", time_spent, philo->id);
// 		printf("%d  %d has taken a fork\n", time_spent, philo->id);
// 		printf("%d  %d is eating\n", time_spent, philo->id);
// 	}
// 	else if (action == "sleeping")
// 		printf("%d , %d, sleeping", time_spent, philo->id);
// 	else if (action == "died")
// 		printf("%d , %d, died", time_spent, philo->id);
// 	else if (action == "thinking")
// 		printf("%d , %d, thinking", time_spent, philo->id);
// 	pthread_mutex_unlock(&philo->sim_info->print_lock);
// 	return (current_time);
// }
// void cleanup(t_data *data) {
//     for (int i = 0; i < data->num_philosophers; i++) {
//         pthread_mutex_destroy(&data->forks[i]);
//     }
//     pthread_mutex_destroy(&data->print_lock);
//     free(data->forks);
//     free(data->philosophers);
// }