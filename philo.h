// philo.h
#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher {
    int id;
    int times_eaten;
    long long last_meal;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data *data;
} t_philosopher;

typedef struct s_data {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_to_eat;
    int dead;
    long long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    t_philosopher *philosophers;
} t_data;

// Function prototypes
void    init_data(t_data *data, int ac, char **av);
void    init_philo(t_data *data);
long long current_time();
void sleep_for(int duration);
void *monitor_routine(void *arg);
void print_status(t_data *data, int id, const char *status);
void *philosopher_routine(void *arg);
void start_simulation(t_data *data);
//void init_data(t_data *data, int argc, char **argv);
void cleanup(t_data *data);

#endif
