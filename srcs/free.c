/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:52 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/08 09:33:52 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

static void	free_d(t_data *d)
{
	if (d->threads)
		free(d->threads);
	pthread_mutex_destroy(&d->print_mutex);
	pthread_mutex_destroy(&d->mutex);
	pthread_mutex_destroy(&d->mutex_forks);
	free(d->forks);
	free(d);
}

static void	free_p(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->main->d->n_philo)
		pthread_mutex_destroy(&p[i].mutex);
	free(p);
}

static void	free_struct(t_main *main)
{
	if (!main)
		return ;
	if (main->p)
		free_p(main->p);
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
