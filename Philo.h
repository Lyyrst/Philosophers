#ifndef PHILO_H  
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"
# include "sys/time.h"

typedef struct s_philo
{
	int						is_eating;
	int						id;
	int						dead;
	int						meals;
	unsigned long			to_die;
	pthread_t				t;
	struct s_forks			*left;
	struct s_forks			*right;
	pthread_mutex_t			mutex;
	struct s_data			*d;
	struct s_main			*main;
}	t_philo;

typedef struct s_forks
{
	pthread_mutex_t	fork;
	int				is_taken;
}	t_forks ;


typedef struct s_data
{
	int				dead;
	int				n;
	int				t_die;
	int				to_eat;
	int				t_sleep;
	int				n_meal;
	int				all_eat;
	unsigned long	start;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print_mutex;
}	t_data;


typedef struct s_main
{
	struct s_philo	*p;
	struct s_data	*d;
	struct s_forks	*f;
}	t_main;

void	fixed_sleep(unsigned long n, t_main *main);
int		check_args(char **argv);

void	init_struct(t_main **main, char **argv);

void 			print_status(t_philo *p, char *s, int n);
void			eat_sleep(t_philo	*p);
unsigned long	get_time(t_main *main);

void	*check_meals(void *ptr);
void	*day(void *ptr);

void	exit_handler(char *error, int n, t_main	*main);

#endif