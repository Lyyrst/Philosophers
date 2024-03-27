#include "../Philo.h"

static void	free_philo(t_philo *p, int n)
{
	int	i;

	i = -1;
	if (!p)
		return ;
	while (++i < n)
	{
		pthread_mutex_destroy(p[i].left);
		pthread_mutex_destroy(p[i].right);
	}
	free(p);
}

void	free_struct(t_main *main)
{
	if (!main)
		return ;
	free_philo(main->p, main->d->n);
	if (main->d)
		free(main->d);
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

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while(argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) || (j == 0 && argv[i][j] == '+'))
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}
