/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:57 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/08 09:33:57 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	ret;
	int	par;

	i = 0;
	ret = 0;
	par = 0;
	if (str[0] == 0)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13)
		|| str[i] == 32)
		i++;
	if (str[i] == '-')
		par = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9')
		&& str[i])
	{
		ret *= 10;
		ret += str[i++] - 48;
	}
	if (par == 1)
		return (ret * -1);
	return (ret);
}

static t_philo	*init_philo(t_main *main, t_data *d)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * d->n_philo);
	if (!philo)
		return (0);
	i = 0;
	while (i < d->n_philo)
	{
		philo[i].id = i;
		philo[i].to_die = d->t_die;
		philo[i].main = main;
		philo[i].meals = 0;
		philo[i].is_eating = 0;
		pthread_mutex_init(&philo[i].mutex, NULL);
		i++;
	}
	return (philo);
}

static void	init_basic_data(char **argv, t_data **d)
{
	(*d)->n_philo = ft_atoi(argv[1]);
	(*d)->t_die = ft_atoi(argv[2]);
	(*d)->to_eat = ft_atoi(argv[3]);
	(*d)->t_sleep = ft_atoi(argv[4]);
	(*d)->dead = 0;
	if (argv[5])
		(*d)->n_meal = ft_atoi(argv[5]);
	else
		(*d)->n_meal = -1;
}

static t_data	*init_data(char **argv, t_main *main)
{
	t_data	*d;
	int		i;

	d = malloc(sizeof(t_data));
	if (!d)
		return (0);
	i = 0;
	init_basic_data(argv, &d);
	d->forks = malloc(sizeof(int) * d->n_philo);
	if (!d->forks)
		return (0);
	while (i < d->n_philo)
		d->forks[i++] = 0;
	d->threads = malloc(sizeof(pthread_t) * d->n_philo);
	if (!d->threads)
		return (0);
	pthread_mutex_init(&d->print_mutex, NULL);
	pthread_mutex_init(&d->mutex, NULL);
	pthread_mutex_init(&d->mutex_forks, NULL);
	d->main = main;
	return (d);
}

void	init_struct(t_main **main, char **argv)
{
	*main = malloc(sizeof(t_main));
	if (!main)
		exit_handler("A memory allocution has failed\n", 1, 0);
	(*main)->d = init_data(argv, *main);
	if (!(*main)->d)
		exit_handler("A memory allocution has failed\n", 1, *main);
	if ((*main)->d->n_philo <= 0 || (*main)->d->t_die < 0 || \
		(*main)->d->t_sleep < 0 || (*main)->d->to_eat < 0)
		exit_handler("Wrong arguments\n", 1, *main);
	(*main)->p = init_philo(*main, (*main)->d);
	if (!(*main)->p)
		exit_handler("A memory allocution has failed\n", 1, *main);
}
