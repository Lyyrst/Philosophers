#include "../Philo.h"

unsigned long	get_time(t_main *main)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		exit_handler("gettimeofday has failed\n", 1, main);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

static void	get_pimp(char **color, char **symbol, int n)
{
	if (n == 1)
	{
		*color = "\033[1;32m";
		*symbol = "\U0001F37D";
	}
	else if (n == 2)
	{
		*color = "\033[1;35m";
		*symbol = "\U0001F634";
	}
	else if (n == 3)
	{
		*color = "\033[1;33m";
		*symbol = "\U0001F914";
	}	
	else if (n == 4)
	{
		*color = "\033[1;31m";
		*symbol = "\U0001F480";
	}
	else if (n == 5)
	{
		*color = "\033[1;36m";
		*symbol = "\U0001F374";
    }
}

void print_status(t_philo *p, char *str, int n)
{
	char			*color;
	char			*symbol;

	pthread_mutex_lock(&p->d->print_mutex);
	get_pimp(&color, &symbol, n);
	if (n == 4 && p->d->dead == 0)
	{
		printf("%ld -> ", get_time(p->main) - p->d->start);
		printf("%s philosopher %d %s %s\033[0m\n", color, p->id + 1, str, symbol);
		p->d->dead = 1;
	}
	if (!p->d->dead)
	{
		printf("%ld -> ", get_time(p->main) - p->d->start);
		printf("%s philosopher %d %s %s\033[0m\n", color, p->id + 1, str, symbol);
	}
	pthread_mutex_unlock(&p->d->print_mutex);
}

int	take_forks(t_philo *p)
{
	if (p->d->dead != 0 || (p->left == p->right))
		return (1);
	if (p->right->is_taken == 0)
		pthread_mutex_lock(&p->right->fork);
	else
		return (1);
	if (p->left->is_taken == 0)
	{
		print_status(p, "has taken a fork", 5);
		p->right->is_taken = 1;
 		pthread_mutex_lock(&p->left->fork);
		print_status(p, "has taken a fork", 5);
		p->left->is_taken = 1;
	}
	else
	{
		pthread_mutex_unlock(&p->right->fork);
		return (1);
	}
	return (0);
}

void	eat_sleep(t_philo *p)
{
	if (take_forks(p) != 0)
		return ;
	pthread_mutex_lock(&p->mutex);
	p->is_eating = 1;
	p->to_die = get_time(p->main) + p->d->t_die;
	print_status(p, "is eating", 1);
	p->meals++;
	fixed_sleep(p->d->to_eat, p->main);
	p->is_eating = 0;
	pthread_mutex_unlock(&p->mutex);
	p->left->is_taken = 0;
	pthread_mutex_unlock(&p->left->fork);
	p->right->is_taken = 0;
	pthread_mutex_unlock(&p->right->fork);
	print_status(p, "is sleeping", 2);
	fixed_sleep(p->d->t_sleep, p->main);
	print_status(p, "is thinking", 3);
}
