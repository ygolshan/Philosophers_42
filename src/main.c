/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:50:34 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/27 09:18:16 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	join_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < (int)table->nbr_created)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
}

void	check_philos(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->print_mt);
	while (table->is_running)
	{
		pthread_mutex_unlock(&table->print_mt);
		my_usleep(1);
		pthread_mutex_lock(&table->philos[i].monitor_mt);
		if (time_ms() - table->philos[i].last_eat > table->philos[i].time_die)
		{
			pthread_mutex_lock(&table->print_mt);
			print_state(&table->philos[i], DIED, true);
			table->is_running = false;
			pthread_mutex_unlock(&table->print_mt);
		}
		pthread_mutex_unlock(&table->philos[i].monitor_mt);
		i++;
		if (i == (int)table->nbr_philos)
			i = 0;
		pthread_mutex_lock(&table->print_mt);
	}
	pthread_mutex_unlock(&table->print_mt);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_table	table;

	if (parse(ac, av, &args) != 0 || prepare_meal(args, &table) != 0)
	{
		printf("Error\n");
		return (1);
	}
	check_philos(&table);
	join_philos(&table);
	free_table(&table);
	return (0);
}
