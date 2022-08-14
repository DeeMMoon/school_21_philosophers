#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_data
{
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			count_meals;
	size_t			start;
	size_t			count_philo;
	int				dead_f;
	int				all_philos_ate_f;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	all_philos_ate;
}		t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	size_t			id;
	size_t			r_fork;
	size_t			l_fork;
	size_t			meal_time;
	size_t			count_meal_f;
	int				ate_f;
	pthread_mutex_t	eat;
	pthread_mutex_t	full;
	t_data			*data;
}					t_philo;

int		check_full(t_data *data, t_philo *p, size_t *is_full);
int		check_dead_two(t_data *data, t_philo **p);
void	check_dead(t_data *data, t_philo **p);
int		init_data(t_data *data, int argc, char **argv);
int		init_mutex(t_data *data);
int		init_philos(t_data *data, t_philo **philos);
int		init_threads(t_data *data, t_philo *philos);
void	ft_thinking(t_philo *p);
void	ft_sleeping(t_philo *p);
void	ft_eating(t_philo *p, size_t f1, size_t f2);
void	*life_cycle(void *philo);
void	ft_free(t_data *data, t_philo **p);
int		main(int argc, char **argv);
size_t	ft_atoi(const char *str);
int		put_error(char *str);
size_t	my_get_time(void);
void	my_usleep(size_t time);
void	print_info(t_philo *philo, char *str);
#endif