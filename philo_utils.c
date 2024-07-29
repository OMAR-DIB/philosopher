// philo_utils.c
#include "philo.h"

long long current_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void sleep_for(int duration) {
    usleep(duration * 1000);
}


void print_status(t_data *data, int id, const char *status) {
    pthread_mutex_lock(&data->print_lock);
    if (!data->dead) {
        printf("%lld %d %s\n", current_time() - data->start_time, id, status);
    }
    pthread_mutex_unlock(&data->print_lock);
}
