#include "../Philo.h"

static void	free_f(t_forks *f, t_data *d)
{
	int	i;

	i = 0;
	while (i < d->n)
	{
		pthread_mutex_destroy(&f[i].fork);
		free(&f[i]);
		i++;
	}
}

static void	free_d(t_data *d)
{
	pthread_mutex_destroy(&d->print_mutex);
	pthread_mutex_destroy(&d->mutex);
	free(d);
}

static void	free_p(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->d->n)
		pthread_mutex_destroy(&p[i].mutex);
	free(p);
}

static void	free_struct(t_main *main)
{
	if (!main)
		return ;
	if (main->p)
		free_p(main->p);
	if (main->f)
		free_f(main->f, main->d);
	if (main->d)
		free_d(main->d);
	free(main);
}

void	exit_handler(char *error, int n, t_main	*main)
{
	int	i;

	i = 0;
	if (error)
	{
		while (error[i])
			write(2, &error[i++], 1);
	}
	free_struct(main);
	if (n == 0)
		exit(EXIT_SUCCESS);
	exit(EXIT_FAILURE);
}