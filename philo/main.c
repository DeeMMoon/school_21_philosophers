#include "header/philo.h"

void	ft_free(t_data *data, t_philo **p)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->all_philos_ate);
	while (i < data->count_philo)
	{
		pthread_mutex_destroy(&(*p)[i].eat);
		pthread_mutex_destroy(&(*p)[i].full);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (*p)
		free(*p);
	if (data -> forks)
		free(data->forks);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	data;

	if (argc != 5 && argc != 6)
		return (put_error("Error count arguments"));
	memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, argc, argv))
		return (put_error("Error data init"));
	if (!init_mutex(&data))
	{
		ft_free(&data, &philos);
		return (put_error("Error mutex init"));
	}
	if (!init_philos(&data, &philos))
	{
		ft_free(&data, &philos);
		return (put_error("Error philos init"));
	}
	if (!init_threads(&data, philos))
		return (put_error("Error thread init"));
	check_dead(&data, &philos);
	ft_free(&data, &philos);
	return (0);
}
