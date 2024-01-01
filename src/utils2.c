/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:45:14 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/26 20:52:01 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	status_args(int code)
{
	if (code)
	{
		if (code == 1)
			ft_putstr_fd("nsufficient arguments.\n", 2);
		if (code == 2)
			ft_putstr_fd("Excessive arguments.\n", 2);
		ft_putstr_fd("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
			time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 2);
		return (1);
		write(2, "Error: ", 7);
		if (code > 2)
			ft_putstr_fd("Invalid argument for \"", 2);
		if (code == 3)
			ft_putstr_fd("number_of_philosophers\"\n", 2);
		if (code == 4)
			ft_putstr_fd("time_to_die\"\n", 2);
		if (code == 5)
			ft_putstr_fd(" time_to_eat\"\n", 2);
		if (code == 6)
			ft_putstr_fd("time_to_sleep\"\n", 2);
		if (code == 7)
			ft_putstr_fd("number_of_times_each_philosopher_must_eat\"\n", 2);
		return (1);
	}
	return (0);
}

uint64_t	time_ms(void)
{
	struct timeval	tv;
	uint64_t		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = ((uint64_t)tv.tv_sec
			* 1000 + (uint64_t)tv.tv_usec / 1000);
	return (milliseconds);
}

bool	is_running(t_philos *self)
{
	bool	state;

	pthread_mutex_lock(self->print_mt);
	state = *self->is_running;
	pthread_mutex_unlock(self->print_mt);
	return (state);
}

void	set_philo_times(t_philos *self, t_args args)
{
	self->time_die = args.time_die;
	self->time_eat = args.time_eat;
	self->time_sleep = args.time_sleep;
	self->must_eat = args.must_eat_nbr;
	self->nbr_philos = args.nbr_philos;
}

void	my_usleep(int time)
{
	uint64_t	delay;
	uint64_t	current_time ;

	delay = time_ms() + time;
	while (true)
	{
		current_time = time_ms();
		if (current_time >= delay)
			break ;
		usleep(40);
	}
}
