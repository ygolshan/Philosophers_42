/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:48:56 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/26 21:39:22 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	print_state(t_philos *self, char *str, bool allready_locked)
{
	uint64_t	time;

	if (!allready_locked)
		pthread_mutex_lock(self->print_mt);
	if (*self->is_running)
	{
		ft_putstr_fd("[", 1);
		time = time_ms();
		ft_put_unbr_fd(time - *self->time_begin, 1);
		ft_putstr_fd(" ms] philo ", 1);
		ft_putnbr_fd(self->id, 1);
		ft_putstr_fd(str, 1);
	}
	if (!allready_locked)
		pthread_mutex_unlock(self->print_mt);
}

static void	schedule_philo(t_philos *self)
{
	uint64_t	must_eat;
	uint64_t	has_eaten;
	uint64_t	satiated;

	must_eat = self->must_eat;
	has_eaten = self->has_eaten;
	satiated = 0;
	if (must_eat && has_eaten >= must_eat && !self->satiated)
	{
		pthread_mutex_lock(self->satiated_mt);
		(*self->notify_satiation)++;
		satiated = *self->notify_satiation;
		self->satiated = true;
		pthread_mutex_unlock(self->satiated_mt);
	}
	pthread_mutex_lock(self->print_mt);
	print_state(self, IS_EATING, true);
	if (satiated == self->nbr_philos)
		*self->is_running = false;
	pthread_mutex_unlock(self->print_mt);
}

static void	eat(t_philos *self)
{
	pthread_mutex_lock(self->forks[0]);
	print_state(self, TAKE_FORK, false);
	if (self->forks[1] != self->forks[0])
	{
		pthread_mutex_lock(self->forks[1]);
		print_state(self, TAKE_FORK, false);
	}
	else
	{
		while (is_running(self))
			usleep(40);
	}
	pthread_mutex_lock(&self->monitor_mt);
	self->last_eat = time_ms();
	self->has_eaten++;
	schedule_philo(self);
	pthread_mutex_unlock(&self->monitor_mt);
	print_state(self, IS_EATING, false);
	my_usleep(self->time_eat);
	pthread_mutex_unlock(self->forks[0]);
	if (self->forks[1] != self->forks[0])
		pthread_mutex_unlock(self->forks[1]);
}

void	*philoshoper(void *arg)
{
	t_philos	*self;

	self = (t_philos *)arg;
	while (is_running(self))
	{
		eat(self);
		print_state(self, IS_SLEEPING, false);
		my_usleep(self->time_sleep);
		print_state(self, IS_THINKING, false);
	}
	return (NULL);
}
