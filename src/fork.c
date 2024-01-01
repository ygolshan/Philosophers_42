/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 21:40:44 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/26 21:50:12 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	get_fork_id(int fork_nbr, int nbr_philos)
{
	if (fork_nbr >= nbr_philos)
		return (nbr_philos - fork_nbr);
	return (fork_nbr);
}

void	assign_forks(pthread_mutex_t *table_forks,
	pthread_mutex_t *philo_forks[2], int nbr_philos, int id)
{
	int	fork1_id;
	int	fork2_id;

	fork1_id = get_fork_id(id, nbr_philos);
	fork2_id = get_fork_id(id + 1, nbr_philos);
	if (id % 2 == 0)
	{
		philo_forks[0] = &table_forks[fork1_id];
		philo_forks[1] = &table_forks[fork2_id];
	}
	else
	{
		philo_forks[0] = &table_forks[fork2_id];
		philo_forks[1] = &table_forks[fork1_id];
	}
}
