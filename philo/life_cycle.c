#include "header/philo.h"

void	ft_thinking(t_philo *p)
{
	print_info(p, "is thinking");
}

void	ft_sleeping(t_philo *p)
{
	print_info(p, "is sleeping");
	my_usleep(p->data->time_to_sleep);
	usleep(100);
}

void	ft_eating(t_philo *p, size_t f1, size_t f2)
{
	pthread_mutex_lock(&p->data->forks[f1]);
	print_info(p, "has taken a fork");
	pthread_mutex_lock(&p->data->forks[f2]);
	print_info(p, "has taken a fork");
	pthread_mutex_lock(&p->eat);
	p->meal_time = my_get_time();
	pthread_mutex_unlock(&p->eat);
	print_info(p, "is eating");
	my_usleep(p->data->time_to_eat);
	pthread_mutex_unlock(&p->data->forks[f1]);
	pthread_mutex_unlock(&p->data->forks[f2]);
	p->count_meal_f++;
	if (p->count_meal_f >= p->data->count_meals
		&& p->data->count_meals)
	{
		pthread_mutex_lock(&p->full);
		p->ate_f = 1;
		pthread_mutex_unlock(&p->full);
	}	
}	

void	*life_cycle(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		pthread_mutex_lock(&p->data->dead);
		pthread_mutex_lock(&p->data->all_philos_ate);
		if (p->data->dead_f || p->data->all_philos_ate_f)
		{
			pthread_mutex_unlock(&p->data->dead);
			pthread_mutex_unlock(&p->data->all_philos_ate);
			break ;
		}
		pthread_mutex_unlock(&p->data->dead);
		pthread_mutex_unlock(&p->data->all_philos_ate);
		ft_thinking(p);
		if (p->id % 2)
			ft_eating(p, p->l_fork, p->r_fork);
		else
			ft_eating(p, p->r_fork, p->l_fork);
		ft_sleeping(p);
	}
	return (0);
}
