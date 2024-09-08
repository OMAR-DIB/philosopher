// philo_utils.c
#include "philo.h"
int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

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
    if (!data->stop_simulation) {
        printf("%lld %d %s\n", current_time() - data->simulation_start, id, status);
    }
    pthread_mutex_unlock(&data->print_lock);
}
