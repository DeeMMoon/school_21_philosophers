#include "header/philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->count_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (!data->count_philo || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep)
		return (0);
	if (argc == 6)
	{
		data->count_meals = ft_atoi(argv[5]);
		if (!data->count_meals)
			return (0);
	}
	else
		data->count_meals = -1;
	data->start = my_get_time();
	return (1);
}

int	init_mutex(t_data *data)
{
	size_t	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->count_philo);
	if (!data->forks)
		return (0);
	while (i < data->count_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->dead, NULL))
		return (0);
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->all_philos_ate, NULL))
		return (0);
	return (1);
}

int	init_philos(t_data *data, t_philo **philos)
{
	size_t	i;

	i = 0;
	*philos = malloc(sizeof(t_philo) * data->count_philo);
	if (!*philos)
		return (0);
	memset (*philos, 0, sizeof(t_philo) * data->count_philo);
	while (i < data->count_philo)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].data = data;
		(*philos)[i].l_fork = i;
		(*philos)[i].meal_time = data->start;
		if (i != data->count_philo - 1)
			(*philos)[i].r_fork = i + 1;
		if (pthread_mutex_init(&(*philos)[i].eat, NULL))
			return (0);
		if (pthread_mutex_init(&(*philos)[i].full, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	init_threads(t_data *data, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < data->count_philo)
	{
		if (pthread_create(&(philos[i].thread_id), NULL,
				life_cycle, philos + i))
		{
			ft_free(data, &philos);
			return (0);
		}
		i++;
	}
	return (1);
}
