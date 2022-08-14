#include "header/philo_bonus.h"

void	thinking(t_philo *p)
{
	sem_wait(p->data->print);
	printf("%zu %zu %s", (my_get_time() - p->data->start), \
		p->id, "is thinking\n");
	sem_post(p->data->print);
}

void	sleeping(t_philo *p)
{
	sem_wait(p->data->print);
	printf("%zu %zu %s", (my_get_time() - p->data->start), \
		p->id, "is sleeping\n");
	sem_post(p->data->print);
	my_usleep(p->data->time_to_sleep);
	usleep(100);
}

void	eating(t_philo *p)
{
	sem_wait(p->data->print);
	printf("%zu %zu %s", (my_get_time() - p->data->start), \
		p->id, "is eating\n");
	sem_post(p->data->print);
	my_usleep(p->data->time_to_eat);
	sem_wait(p->data->check);
	p->time_to_die = my_get_time();
	p->count_meals++;
	sem_post(p->data->check);
	sem_post(p->data->forks);
	sem_post(p->data->forks);
}

void	take_forks(t_philo *p)
{
	sem_wait(p->data->forks);
	sem_wait(p->data->print);
	printf("%zu %zu %s", (my_get_time() - p->data->start), \
		p->id, "has taken a fork\n");
	sem_post(p->data->print);
	sem_wait(p->data->forks);
	sem_wait(p->data->print);
	printf("%zu %zu %s", (my_get_time() - p->data->start), \
		p->id, "has taken a fork\n");
	sem_post(p->data->print);
}

void	*life_cycle(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	pthread_create(&p->dead, NULL, check_dead, (void *)p);
	if (p->id % 2 == 0)
		my_usleep(p->data->time_to_eat / 10);
	while (!(p->data->dead_f))
	{
		take_forks(p);
		eating(p);
		sleeping(p);
		if (p->count_meals >= p->data->full)
			break ;
		thinking(p);
	}
	pthread_join(p->dead, NULL);
	exit(0);
	return (args);
}
