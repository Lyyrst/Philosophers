#include "../Philo.h"

void	*check_meals(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (p->d->dead == 0)
	{
		pthread_mutex_lock(&p->mutex);
		if (p->d->all_eat >= p->d->n)
			p->d->dead = 1;
		pthread_mutex_unlock(&p->mutex);
	}
	return ((void *)0);
}

static void	*night(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (p->d->dead == 0)
	{
		pthread_mutex_lock(&p->mutex);
		if (get_time(p->main) >= p->to_die && p->is_eating == 0)
			print_status(p, "died", 4);
		if (p->meals == p->d->n_meal)
		{
			pthread_mutex_lock(&p->d->mutex);
			p->d->all_eat++;
			p->meals++;
			pthread_mutex_unlock(&p->d->mutex);
		}
		pthread_mutex_unlock(&p->mutex);
	}
	return ((void *)0);
}

void	*day(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	p->to_die = p->d->t_die + get_time(p->main);
	if (p->id % 2 != 0)
		fixed_sleep(p->d->to_eat, p->main);
	if (pthread_create(&p->t, NULL, &night, (void *)p))
		return ((void *)1);
	while (p->d->dead == 0)
		eat_sleep(p);
	if (pthread_join(p->t, NULL))
		return ((void *)1);
	return ((void *)0);
}
