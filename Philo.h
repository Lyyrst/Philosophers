#ifndef PHILO_H  
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"
# include "sys/time.h"

typedef	enum
{
	THINK,
	EAT,
	SLEEP,
	DEAD,
} status;

typedef struct s_philo
{
	int						id;
	status					status;
	pthread_mutex_t			*left;
	pthread_mutex_t			*right;
	unsigned long			last_meal;
	int						meals;
	pthread_mutex_t			mutex;
	struct s_data			*d;
}	t_philo;

typedef struct s_data
{
	int				n;
	int				t_die;
	int				to_eat;
	int				t_sleep;
	int				n_meal;
	int				*done;
	unsigned long	start;
	pthread_mutex_t	print_mutex;
}	t_data;


typedef struct s_main
{
	struct s_philo	*p;
	struct s_data	*d;
}	t_main;


void	exit_handler(char *error, int n, t_main *main);
int		check_args(char **argv);

void	init_struct(t_main **main, char **argv);

#endif