#include "header/philo_bonus.h"

int	put_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void	*check_dead(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	while (!p->data->dead_f && p->count_meals \
	< p->data->full)
	{
		sem_wait(p->data->check);
		if (my_get_time() - p->time_to_die > p->data->time_to_die)
		{
			p->data->dead_f = 1;
			sem_wait(p->data->print);
			printf("%zu %zu %s", (my_get_time() - p->data->start), \
				p->id, "is dead\n");
			exit(1);
		}
		sem_post(p->data->check);
	}
	return (NULL);
}

int	semulation(t_data *data)
{
	int	i;

	i = -1;
	data->start = my_get_time();
	while (++i < data->count_philo)
	{
		data->philos[i].time_to_die = data->start;
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			exit(EXIT_FAILURE);
		if (data->philos[i].pid == 0)
			life_cycle((void *)&data->philos[i]);
	}
	return (1);
}

void	end_semulation(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->count_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < data->count_philo)
				kill(data->philos[i].pid, SIGTERM);
			break ;
		}
	}
	sem_close(data->print);
	sem_close(data->check);
	sem_close(data->forks);
	sem_unlink("print");
	sem_unlink("check");
	sem_unlink("forks");
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (put_error("Error count arguments"));
	if (!init_data(&data, argc, argv))
		return (put_error("Error data init"));
	if (!init_philos(&data))
		return (put_error("Error philos init"));
	if (!init_sem(&data))
		return (put_error("Error sem init"));
	semulation(&data);
	end_semulation(&data);
	return (0);
}
