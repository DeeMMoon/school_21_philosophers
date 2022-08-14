#include "header/philo_bonus.h"

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
