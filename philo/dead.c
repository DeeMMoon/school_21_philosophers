#include "header/philo.h"

int	check_full(t_data *data, t_philo *p, size_t *is_full)
{
	pthread_mutex_lock(&p->full);
	if (p->ate_f == 1)
		*is_full += 1;
	pthread_mutex_unlock(&p->full);
	if (*is_full == data->count_philo)
	{
		pthread_mutex_lock(&data->all_philos_ate);
		data->all_philos_ate_f = 1;
		pthread_mutex_unlock(&data->all_philos_ate);
		return (1);
	}
	return (0);
}

int	check_dead_two(t_data *data, t_philo **p)
{
	size_t	i;
	size_t	is_full;

	i = 0;
	is_full = 0;
	while (i < data->count_philo)
	{
		pthread_mutex_lock(&(*p)[i].eat);
		if ((my_get_time() - (*p)[i].meal_time) > data->time_to_die)
		{
			pthread_mutex_lock(&data->dead);
			data->dead_f = 1;
			pthread_mutex_unlock(&data->dead);
			pthread_mutex_unlock(&(*p)[i].eat);
			printf("%zu %zu is dead\n", my_get_time() - data->start, (*p)[i].id);
			return (1);
		}
		pthread_mutex_unlock(&(*p)[i].eat);
		if (check_full(data, &(*p)[i], &is_full))
			return (1);
		i++;
	}
	return (0);
}

void	check_dead(t_data *data, t_philo **p)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (check_dead_two(data, p))
			break ;
	}
	while (i < data->count_philo)
	{
		if (data->count_philo == 1)
			pthread_detach((*p)[i].thread_id);
		pthread_join((*p)[i].thread_id, NULL);
		i++;
	}
}
