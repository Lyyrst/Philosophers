/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbutor-b <kbutor-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:39 by kbutor-b          #+#    #+#             */
/*   Updated: 2024/04/08 09:33:39 by kbutor-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	get_thread(t_main	*main)
{
	int				i;
	pthread_t		*threads;

	threads = main->d->threads;
	main->d->start = get_time(main);
	i = -1;
	while (++i < main->d->n_philo)
	{
		if (pthread_create(&threads[i], NULL, &day, &main->p[i]))
			exit_handler("A thread has failed\n", 1, main);
		usleep(512);
	}
	i = -1;
	while (++i < main->d->n_philo)
	{
		if (pthread_join(threads[i], NULL))
			exit_handler("A threads join has failed\n", 1, main);
	}
}

void	one_philo(t_main *main)
{
	pthread_t	threads;

	main->d->start = get_time(main);
	if (pthread_create(&threads, NULL, &day, &main->p[0]))
		exit_handler("A thread failed to start\n", 1, main);
	pthread_join(threads, NULL);
}

int	main(int argc, char **argv)
{
	t_main	*main;

	if (argc != 5 && argc != 6)
		exit_handler("Wrong numbers of arguments\n", 1, 0);
	if (check_args(argv))
		exit_handler("Wrong arguments, only positive numbers are accepted\n" \
					, 1, 0);
	init_struct(&main, argv);
	if (main->d->n_philo == 1)
		one_philo(main);
	else
		get_thread(main);
	exit_handler(0, 0, main);
	return (0);
}
