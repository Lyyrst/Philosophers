/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:34:32 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/08 09:34:32 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int						meals;
	unsigned long			to_die;
	pthread_mutex_t			mutex;
	struct s_main			*main;
}	t_philo;

typedef struct s_data
{
	int				dead;
	int				n_philo;
	int				t_die;
	int				to_eat;
	int				t_sleep;
	int				n_meal;
	int				*forks;
	unsigned long	start;
	pthread_t		*threads;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	mutex_forks;
	struct s_main	*main;
}	t_data;

typedef struct s_main
{
	struct s_philo	*p;
	struct s_data	*d;
}	t_main;

int				any_death(t_philo *p);
unsigned long	get_time(t_main *main);
void			fixed_sleep(unsigned long n, t_main *main);
int				check_args(char **argv);

void			print_status(t_philo *p, char *s, int n);

void			init_struct(t_main **main, char **argv);

void			eat_sleep(t_philo *p);

void			*day(void *ptr);

void			exit_handler(char *error, int n, t_main	*main);

void			down_forks(t_philo *p);
int				take_forks(t_philo *p);

#endif