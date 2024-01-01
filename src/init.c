/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:45:43 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/26 21:49:12 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	handle_allocation_error(void)
{
	ft_putstr_fd("Error:\n", 2);
	return (1);
}

void	free_table(t_table *table)
{
	uint64_t	i;

	i = 0;
	if (table == NULL)
		return ;
	if (table->forks != NULL)
	{
		while (i < table->nbr_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
		table->forks = NULL;
	}
	pthread_mutex_destroy(&table->print_mt);
	pthread_mutex_destroy(&table->satiated_mt);
	if (table->philos != NULL)
		free(table->philos);
	table->philos = NULL;
	table->nbr_philos = 0;
}

int	init_table(t_table *table, uint64_t nbr_philos)
{
	uint64_t	i;

	i = 0;
	table->nbr_philos = nbr_philos;
	table->forks = malloc(sizeof(pthread_mutex_t) * nbr_philos);
	if (!table->forks)
		return (handle_allocation_error());
	while (i < nbr_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		++i;
	}
	pthread_mutex_init(&table->print_mt, NULL);
	pthread_mutex_init(&table->satiated_mt, NULL);
	table->is_running = true;
	return (0);
}
