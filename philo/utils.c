#include "header/philo.h"

size_t	ft_atoi(const char *str)
{
	long long	t;
	size_t		res;
	int			i;

	i = 0;
	t = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		t = t * 10 + str[i] - 48;
		i++;
	}
	if (t > 2147483647 || t < -2147483648)
		return (0);
	res = (size_t) t;
	return (res);
}

int	put_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

size_t	my_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((size_t)time.tv_sec * 1000 + (size_t)time.tv_usec / 1000);
}

void	my_usleep(size_t time)
{
	size_t	t;

	t = my_get_time() + time;
	while (my_get_time() < t)
		usleep(50);
}

void	print_info(t_philo *philo, char *str)
{
	size_t	time;

	time = 0;
	pthread_mutex_lock(&philo->data->dead);
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->dead_f)
	{
		pthread_mutex_unlock(&philo->data->dead);
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	pthread_mutex_unlock(&philo->data->dead);
	time = my_get_time() - philo->data->start;
	printf("%zu %zu %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}
