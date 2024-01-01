/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:52:58 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/27 09:06:26 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

bool	positive_number(const char *str)
{
	if (str == NULL || *str == '\0')
		return (false);
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

bool	check_for_int_max(const char *str)
{
	size_t		str_length;
	const char	*int_max_str;

	int_max_str = "2147483647";
	str_length = 0;
	while (str[str_length] != '\0')
		str_length++;
	if (str_length < 10 || (str_length == 10 && strcmp(str, int_max_str) <= 0))
		return (false);
	else
		return (true);
}

int	argument_value(uint64_t *nbr, const char *arg, uint64_t min_val)
{
	uint64_t	value;
	char		*endptr;

	if (!positive_number(arg))
		return (1);
	if (check_for_int_max(arg))
		return (1);
	value = strtoull(arg, &endptr, 10);
	if (*endptr != '\0')
		return (1);
	if (value < min_val)
		return (1);
	*nbr = value;
	return (0);
}

int	parse(int ac, char **av, t_args *args)
{
	memset(args, 0, sizeof(t_args));
	if (ac < 5 || ac > 6)
	{
		printf("Error!\nWrong number of input values.\n");
		return (1);
	}
	if (argument_value(&args->nbr_philos, av[1], MIN_NBR_PHILO))
		return (3);
	if (argument_value(&args->time_die, av[2], MIN_TIME_DIE))
		return (4);
	if (argument_value(&args->time_eat, av[3], MIN_TIME_EAT))
		return (5);
	if (argument_value(&args->time_sleep, av[4], MIN_TIME_SLEEP))
		return (6);
	if (ac == 6)
	{
		args->must_eat = true;
		if (argument_value(&args->must_eat_nbr, av[5], MIN_EAT_NBR))
			return (7);
	}
	return (0);
}
