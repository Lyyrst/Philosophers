#include "../Philo.h"

void	get_thread(t_main	*main)
{
	int				i;
	pthread_t		t;
	pthread_t		threads[main->d->n];

	main->d->start = get_time(main);
	if (main->d->n_meal > 0)
	{
		if (pthread_create(&t, NULL, &check_meals, &main->p[0]))
			exit_handler("A thread has failed\n", 1, main);
	}
	i = -1;
	while (++i < main->d->n)
	{
		if (pthread_create(&threads[i], NULL, &day, &main->p[i]))
			exit_handler("A thread has failed\n", 1, main);
		usleep(1);
	}
	i = 0;
	while (i < main->d->n)
	{
		if (pthread_join(threads[i++], NULL))
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
	while (main->d->dead == 0)
		usleep(0);
}

int main(int argc, char **argv)
{
	t_main *main;

	if (argc != 5 && argc != 6)
		exit_handler("Wrong numbers of arguments\n", 1, 0);
	if (check_args(argv))
		exit_handler("Wrong arguments, only positive numbers are accepted\n", 1, 0);
	init_struct(&main, argv);
	if (main->d->n == 1)
		one_philo(main);
	else
		get_thread(main);
	exit_handler(0, 0, main);
	return (0);
}