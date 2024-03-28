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

static t_philo	*init_philo(int	n, t_data *d, t_main *main, t_forks *f)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * n);
	if (!philo)
		return (0);
	i = 0;
	philo[0].left = &f[0];
	philo[0].right = &f[d->n - 1];
	while (i < n)
	{
		if (i > 0)
		{
			philo[i].left = &f[i];
			philo[i].right = &f[i - 1];
		}
		philo[i].id = i;
		philo[i].to_die = d->t_die;
		philo[i].d = d;
		philo[i].main = main;
		philo[i].meals = 0;
		philo[i].is_eating = 0;
		philo[i].dead = 0;
		pthread_mutex_init(&philo[i].mutex, NULL);
		i++;
	}
	return (philo);
}

static void	init_basic_data(char **argv, t_data **d)
{
	(*d)->n = ft_atoi(argv[1]);
	(*d)->t_die = ft_atoi(argv[2]);
	(*d)->to_eat = ft_atoi(argv[3]);
	(*d)->t_sleep = ft_atoi(argv[4]);
	(*d)->all_eat = 0;
	(*d)->dead = 0;
	if (argv[5])
		(*d)->n_meal = ft_atoi(argv[5]);
	else
		(*d)->n_meal = -1;
}

static t_data	*init_data(char **argv)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	if (!d)
		return (0);
	init_basic_data(argv, &d);
	pthread_mutex_init(&d->print_mutex, NULL);
	pthread_mutex_init(&d->mutex, NULL);
	return (d);
}

static t_forks	*init_forks(t_data *d)
{
	t_forks	*f;
	int		i;

	f = malloc(sizeof(t_forks) * d->n);
	if (!f)
		return (0);
	i = -1;
	while (++i < d->n)
	{
		pthread_mutex_init(&f->fork, NULL);
		f->is_taken = 0;
	}
	return (f);
}

void	init_struct(t_main **main, char **argv)
{
	*main = malloc(sizeof(t_main));
	if (!main)
		exit_handler("A memory allocution has failed\n", 1, 0);
	(*main)->d = init_data(argv);
	if (!(*main)->d)
		exit_handler("A memory allocution has failed\n", 1, *main);
	if ((*main)->d->n <= 0 || (*main)->d->t_die < 0 || (*main)->d->t_sleep < 0 || (*main)->d->to_eat < 0)
		exit_handler("Wrong arguments\n", 1, *main);
	(*main)->f = init_forks((*main)->d);
	if (!(*main)->f)
		exit_handler("A memory allocution has failed\n", 1, *main);
	(*main)->p = init_philo((*main)->d->n, (*main)->d,*main, (*main)->f);
	if (!(*main)->p)
		exit_handler("A memory allocution has failed\n", 1, *main);
}