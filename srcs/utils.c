#include "../Philo.h"

void	fixed_sleep(unsigned long n, t_main *main)
{
	unsigned long	start;
	
	start = get_time(main);
	while ((get_time(main) - start) < n)
		usleep(n / 10);
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
