/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:47:01 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/26 21:46:11 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static void	init_philos_recursive(t_args args, t_table *table, int i)
{
	if (i >= (int)args.nbr_philos)
		return ;
	memset(&table->philos[i], 0, sizeof(t_philos));
	table->philos[i].id = i + 1;
	set_philo_times(&table->philos[i], args);
	table->philos[i].satiated_mt = &table->satiated_mt;
	table->philos[i].notify_satiation = &table->philos_satiated;
	table->philos[i].is_running = &table->is_running;
	table->philos[i].print_mt = &table->print_mt;
	table->philos[i].time_begin = &table->time_begin;
	pthread_mutex_init(&table->philos[i].monitor_mt, NULL);
	assign_forks(table->forks, table->philos[i].forks,
		args.nbr_philos, table->philos[i].id - 1);
	init_philos_recursive(args, table, i + 1);
}

static int	init_philos(t_args args, t_table *table)
{
	table->philos = (t_philos *)malloc(sizeof(t_philos) * args.nbr_philos);
	if (!table->philos)
	{
		ft_putstr_fd("Error: failed malloc() philos\n", 2);
		free_table(table);
		return (1);
	}
	init_philos_recursive(args, table, 0);
	return (0);
}

static int	launch_philos(t_table *table)
{
	int	i;

	i = -1;
	table->time_begin = time_ms();
	while (++i < (int)table->nbr_philos)
	{
		table->philos[i].last_eat = table->time_begin;
		table->philos[i].time_begin = &table->time_begin;
		if (pthread_create(&table->philos[i].thread, NULL, philoshoper,
				&table->philos[i]))
		{
			pthread_mutex_lock(&table->print_mt);
			table->is_running = false;
			pthread_mutex_unlock(&table->print_mt);
			return (1);
		}
		table->nbr_created = i + 1;
	}
	return (0);
}

int	prepare_meal(t_args args, t_table *table)
{
	if (init_table(table, args.nbr_philos) != 0)
		return (1);
	table->must_eat = args.must_eat_nbr;
	if (init_philos(args, table))
	{
		free_table(table);
		return (1);
	}
	if (launch_philos(table) != 0)
	{
		join_philos(table);
		free_table(table);
		return (1);
	}
	return (0);
}
