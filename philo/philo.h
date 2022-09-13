#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT "is eating 🍴🍱"
# define SLEEP "is sleeping 💤"
# define THINK "is thinking 🤔"
# define DIED "died 💀"
# define FORK "has taken a fork 🍴"
# define FULL "All philosophers are full 🍱"

typedef struct s_args
{
	int				n_philo;
	int				must_eat;
	int				death;
	int				times_ate;
	long			time_tdie;
	long			time_teat;
	long			time_tsleep;
	pthread_mutex_t	times_eat_lock;
	pthread_mutex_t	lock_death;
	useconds_t		o_time;
}					t_args;

typedef struct s_philo
{
	int				philo_id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	lock_last_ate;
	long long		last_ate;
	struct t_args	*info;
}					t_philo;

int					philos(t_args *phil, t_philo *philo);
void				philosophers(t_philo *mutexes, t_args *args);
void				*living_philo(t_philo *philo, t_args *data);
int					thread_initalization(t_args *args);

long long			get_time(void);
int					u_sleep(useconds_t usec);
int					ft_atoi(char *str);
void				parse_errors(t_args *args, int argc);

#endif