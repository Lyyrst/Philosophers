/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:47 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/08 09:33:47 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static void	p_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->main->d->mutex);
	if (p->main->d->dead == 0)
	{
		pthread_mutex_unlock(&p->main->d->mutex);
		print_status(p, "is sleeping", 2);
		fixed_sleep(p->main->d->t_sleep, p->main);
		return ;
	}
	pthread_mutex_unlock(&p->main->d->mutex);
}

static void	p_think(t_philo *p)
{
	pthread_mutex_lock(&p->main->d->mutex);
	if (p->main->d->dead == 0)
	{
		pthread_mutex_unlock(&p->main->d->mutex);
		print_status(p, "is thinking", 3);
		return ;
	}
	pthread_mutex_unlock(&p->main->d->mutex);
}

void	eat_sleep(t_philo *p)
{
	if (p->main->d->n_philo == 1)
		return ;
	if (take_forks(p))
		return ;
	pthread_mutex_lock(&p->mutex);
	p->to_die = get_time(p->main) + p->main->d->t_die;
	p->meals++;
	pthread_mutex_unlock(&p->mutex);
	print_status(p, "is eating", 1);
	fixed_sleep(p->main->d->to_eat, p->main);
	down_forks(p);
	if (p->meals == p->main->d->n_meal)
		return ;
	p_sleep(p);
	p_think(p);
}
