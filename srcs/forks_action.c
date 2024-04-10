/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:25:29 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/10 16:26:33 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	down_forks(t_philo *p)
{
	pthread_mutex_lock(&p->main->d->mutex_forks);
	if (p->id == p->main->d->n_philo - 1)
	{
		p->main->d->forks[p->id] = 0;
		p->main->d->forks[0] = 0;
		pthread_mutex_unlock(&p->main->d->mutex_forks);
		return ;
	}
	else
	{
		p->main->d->forks[p->id] = 0;
		p->main->d->forks[p->id + 1] = 0;
		pthread_mutex_unlock(&p->main->d->mutex_forks);
		return ;
	}
	pthread_mutex_unlock(&p->main->d->mutex_forks);
}

static int	last_forks(t_philo *p)
{
	pthread_mutex_lock(&p->main->d->mutex_forks);
	if (p->id == p->main->d->n_philo - 1)
	{
		if (p->main->d->forks[p->id] == 0 && p->main->d->forks[0] == 0)
		{
			p->main->d->forks[p->id] = 1;
			p->main->d->forks[0] = 1;
			pthread_mutex_unlock(&p->main->d->mutex_forks);
			print_status(p, "has taken a fork", 5);
			print_status(p, "has taken a fork", 5);
			return (0);
		}
	}
	pthread_mutex_unlock(&p->main->d->mutex_forks);
	return (1);
}

static int	basic_forks(t_philo *p)
{
	pthread_mutex_lock(&p->main->d->mutex_forks);
	if (p->main->d->forks[p->id] == 0 && \
			p->main->d->forks[p->id + 1] == 0 && \
			p->id != p->main->d->n_philo - 1)
	{
		p->main->d->forks[p->id] = 1;
		p->main->d->forks[p->id + 1] = 1;
		pthread_mutex_unlock(&p->main->d->mutex_forks);
		print_status(p, "has taken a fork", 5);
		print_status(p, "has taken a fork", 5);
		return (0);
	}
	pthread_mutex_unlock(&p->main->d->mutex_forks);
	return (1);
}

int	take_forks(t_philo *p)
{
	if (basic_forks(p) == 0)
		return (0);
	if (last_forks(p) == 0)
		return (0);
	return (1);
}
