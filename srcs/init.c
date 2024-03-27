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

static t_philo	*init_philo(int	n, t_data *d)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * n);
	if (!philo)
		return (0);
	i = 0;
	while (i < n)
	{
		philo[i].left = malloc(sizeof(pthread_mutex_t));
		philo[i].right = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].left || !philo[i].right)
			return (0);
		pthread_mutex_init(philo[i].left, 0);
		pthread_mutex_init(philo[i].right, 0);
		if (i == d->n - 1)
		{
			philo[i].left = philo[0].right;
			philo[i].right = philo[i].left;
		}
		else
		{
			philo[i].left = philo[i].right;
			philo[i].right = philo[i + 1].left;
		}
		philo[i].id = i;
		philo[i].status = THINK;
		philo[i].last_meal = 0;
		philo[i].d = d;
		philo[i].meals = 0;
		pthread_mutex_init(&philo[i].mutex, NULL);
		i++;
	}
	return (philo);
}

static unsigned long	get_start()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

static t_data	*init_data(char **argv)
{
	t_data	*d;
	int		i;

	d = malloc(sizeof(t_data));
	if (!d)
		return (0);
	d->n = ft_atoi(argv[1]);
	d->t_die = ft_atoi(argv[2]);
	d->to_eat = ft_atoi(argv[3]);
	d->t_sleep = ft_atoi(argv[4]);
	d->start = get_start();
	d->done = malloc(sizeof(int) * d->n);
	if (!d->done)
		return (0);
	i = -1;
	while (++i < d->n)
		d->done = 0;
	if (argv[5])
		d->n_meal = ft_atoi(argv[5]);
	else
		d->n_meal = 0;
	pthread_mutex_init(&d->print_mutex, NULL);
	return (d);
}

void	init_struct(t_main **main, char **argv)
{
	*main = malloc(sizeof(t_main));
	if (!main)
		exit_handler("A memory allocution has failed\n", 1, 0);
	(*main)->d = init_data(argv);
	if (!(*main)->d)
		exit_handler("A memory allocution has failed\n", 1, *main);
	(*main)->p = init_philo((*main)->d->n, (*main)->d);
	if (!(*main)->p)
		exit_handler("A memory allocution has failed\n", 1, *main);
}