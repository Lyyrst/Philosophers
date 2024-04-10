/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:34:04 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/08 09:34:04 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static void	start_day(t_philo *p)
{
	pthread_mutex_lock(&p->mutex);
	print_status(p, "is thinking", 3);
	p->to_die = get_time(p->main) + p->main->d->t_die;
	pthread_mutex_unlock(&p->mutex);
}

static int	is_dead(t_philo *p)
{
	if (get_time(p->main) >= p->to_die)
	{
		print_status(p, "died", 4);
		return (1);
	}
	return (0);
}

static int	is_full(t_philo *p)
{
	if (p->meals == p->main->d->n_meal)
		return (1);
	return (0);
}

void	*day(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	start_day(p);
	while (1)
	{
		if (is_dead(p))
			break ;
		if (is_full(p))
			break ;
		if (any_death(p))
			break ;
		eat_sleep(p);
	}
	return ((void *)0);
}
