#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_data	t_data;

typedef struct s_philo	t_philo;

typedef struct s_data
{
	size_t			start;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			full;
	int				count_philo;
	int				dead_f;
	t_philo			*philos;
	sem_t			*print;
	sem_t			*check;
	sem_t			*forks;
}		t_data;

typedef struct s_philo
{
	size_t			id;
	size_t			count_meals;
	t_data			*data;
	size_t			time_to_die;
	pid_t			pid;
	pthread_t		dead;
}				t_philo;

void	my_usleep(size_t time);
size_t	my_get_time(void);
size_t	ft_atoi(const char *str);
void	*check_dead(void *args);
int		semulation(t_data *data);
void	end_semulation(t_data *data);
void	thinking(t_philo *p);
void	sleeping(t_philo *p);
void	eating(t_philo *p);
void	take_forks(t_philo *p);
void	*life_cycle(void *args);
int		init_data(t_data *data, int argc, char **argv);
int		init_philos(t_data *data);
int		init_sem(t_data *data);
int		put_error(char *str);

#endif