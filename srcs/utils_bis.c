/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:19:14 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/10 16:22:17 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

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

void	print_status(t_philo *p, char *str, int n)
{
	char			*color;
	char			*symbol;

	get_pimp(&color, &symbol, n);
	pthread_mutex_lock(&p->main->d->print_mutex);
	pthread_mutex_lock(&p->main->d->mutex);
	if (n == 4 && p->main->d->dead == 0)
	{
		printf("%ld -> ", get_time(p->main) - p->main->d->start);
		printf("%s philosopher %d %s %s\033[0m\n" \
				, color, p->id + 1, str, symbol);
		p->main->d->dead = 1;
	}
	if (!p->main->d->dead)
	{
		printf("%ld -> ", get_time(p->main) - p->main->d->start);
		printf("%s philosopher %d %s %s\033[0m\n" \
				, color, p->id + 1, str, symbol);
	}
	pthread_mutex_unlock(&p->main->d->print_mutex);
	pthread_mutex_unlock(&p->main->d->mutex);
}
