#include "header/philo_bonus.h"

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
		data->full = ft_atoi(argv[5]);
		if (!data->full)
			return (0);
	}
	else
		data->full = -1;
	data->start = my_get_time();
	return (1);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->dead_f = 0;
	data->philos = malloc(sizeof(t_philo) * data->count_philo);
	if (!data->philos)
		return (0);
	while (++i < data->count_philo)
	{
		data->philos[i].count_meals = 0;
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
	}
	return (1);
}

int	init_sem(t_data *data)
{
	sem_unlink("check");
	sem_unlink("forks");
	sem_unlink("print");
	data->check = sem_open("check", O_CREAT, 0666, 1);
	data->forks = sem_open("forks", O_CREAT, 0666, data->count_philo);
	data->print = sem_open("print", O_CREAT, 0666, 1);
	if (data->check == SEM_FAILED || data->forks == SEM_FAILED \
		|| data->print == SEM_FAILED)
		return (0);
	return (1);
}
