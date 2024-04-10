/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:34:08 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/08 09:34:08 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

int	any_death(t_philo *p)
{
	pthread_mutex_lock(&p->main->d->mutex);
	if (p->main->d->dead == 0)
	{
		pthread_mutex_unlock(&p->main->d->mutex);
		return (0);
	}
	pthread_mutex_unlock(&p->main->d->mutex);
	return (1);
}

unsigned long	get_time(t_main *main)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0))
		exit_handler("gettimeofday has failed\n", 1, main);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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
		while (argv[i][j])
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
