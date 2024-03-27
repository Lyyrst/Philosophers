#include "../Philo.h"

static unsigned long	get_time()
{
	struct timeval	t;
	gettimeofday(&t, 0);
	return (t.tv_sec * 1000 / t.tv_usec / 1000);
}

static void print_status(t_philo *p, char *s)
{
	struct timeval t;
	gettimeofday(&t, 0);
	pthread_mutex_lock(&p->d->print_mutex);
    printf("%ld philosopher %d %s\n", (t.tv_sec * 1000 + t.tv_usec / 1000) - p->d->start, p->id + 1, s);
	pthread_mutex_unlock(&p->d->print_mutex);
}

static void	*philo_day(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (p->status == EAT)
		{
			print_status(p, "is eating");
			p->last_meal = get_time();
			usleep(p->d->to_eat * 1000);
			p->meals++;
			p->status = SLEEP;
 			pthread_mutex_unlock(p->left);
			pthread_mutex_unlock(p->right);
		}
		if (p->status == THINK)
		{
			print_status(p, "is thinking");
			p->status = EAT;
			pthread_mutex_lock(p->left);
			pthread_mutex_lock(p->right);
		}
		if (p->status == SLEEP)
		{
			print_status(p, "is sleeping");
			usleep(p->d->t_sleep * 1000);
			p->status = THINK;
		}
		if (p->d->n_meal > 0 && (p->meals >= p->d->n_meal))
		{
			p->d->done[p->id] = 1;
			break ;
		}
		if (get_time() - p->last_meal >= (unsigned long)p->d->t_die)
		{
			p->status = DEAD;
			print_status(p, "died");
			break ;
		}
	}
	return (0);
}

void	get_thread(t_main *main)
{
	pthread_t	threads[main->d->n];
	int			i;

	i = 0;
	while (i < main->d->n)
	{
		pthread_create(&threads[i], NULL, philo_day, &main->p[i]);
		i++;
	}
	while (main->d->n_meal)
	{
		i = -1;
		while (++i < main->d->n)
		{
			if (main->p[i].status == DEAD)
			{
				main->d->n_meal = 0;
				break ;
			}
		}
		i = -1;
		while (++i < main->d->n)
		{
			if (main->d->done[i] == 0)
			{
				main->d->n_meal = 0;
				break ;
			}
		}
		usleep(1000);
	}
	i = 0;
	while (i < main->d->n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < main->d->n)
	{
		pthread_mutex_destroy(&main->p[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&main->d->print_mutex);
}

int main(int argc, char **argv)
{
	t_main *main;

	if (argc != 5 && argc != 6)
		exit_handler("Wrong numbers of arguments\n", 1, 0);
	if (check_args(argv))
		exit_handler("Wrong arguments, only positive numbers are accepted\n", 1, 0);
	init_struct(&main, argv);
	get_thread(main);
	return (0);
}