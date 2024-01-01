/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:48:39 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/27 08:55:34 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define MIN_NBR_PHILO 1
# define MIN_TIME_DIE 1
# define MIN_TIME_EAT 1
# define MIN_TIME_SLEEP 1
# define MIN_EAT_NBR 1
# define TAKE_FORK " has taken a fork\n"
# define IS_EATING " is eating\n"
# define IS_SLEEPING " is sleeping\n"
# define IS_THINKING " is thinking\n"
# define DIED " died\n"

typedef struct s_args
{
	uint64_t	nbr_philos;
	uint64_t	time_die;
	uint64_t	time_eat;
	uint64_t	time_sleep;
	bool		must_eat;
	uint64_t	must_eat_nbr;
}				t_args;

typedef struct s_philo
{
	uint64_t		id;
	uint64_t		nbr_philos;
	uint64_t		*time_begin;
	uint64_t		time_die;
	uint64_t		time_eat;
	uint64_t		time_sleep;
	uint64_t		must_eat;
	uint64_t		last_eat;
	uint64_t		has_eaten;
	pthread_mutex_t	monitor_mt;
	pthread_mutex_t	*satiated_mt;
	bool			*is_running;
	pthread_mutex_t	*print_mt;
	pthread_mutex_t	*forks[2];
	pthread_t		thread;
	bool			satiated;
	uint64_t		*notify_satiation;
}				t_philos;

typedef struct s_table
{
	uint64_t		nbr_philos;
	uint64_t		nbr_created;
	uint64_t		time_begin;
	uint64_t		must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mt;
	pthread_mutex_t	satiated_mt;
	uint64_t		philos_satiated;
	bool			is_running;
	t_philos		*philos;
}				t_table;

void		free_table(t_table *table);
int			init_table(t_table *table, uint64_t nbr_philos);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		join_philos(t_table *table);
void		check_philos(t_table *table);
int			main(int ac, char **av);
bool		positive_number(const char *str);
bool		check_for_int_max(const char *str);
int			argument_value(uint64_t *nbr, const char *arg, uint64_t min_val);
int			parse(int ac, char **av, t_args *args);
void		print_state(t_philos *self, char *str, bool allready_locked);
void		*philoshoper(void *arg);
void		assign_forks(pthread_mutex_t *table_forks,
				pthread_mutex_t *philo_forks[2], int nbr_philos, int id);
int			prepare_meal(t_args args, t_table *table);
void		ft_putnbr_fd(int n, int fd);
void		ft_put_unbr_fd(unsigned int n, int fd);
void		ft_putstr_fd(char const *s, int fd);
int			status_args(int code);
uint64_t	time_ms(void);
bool		is_running(t_philos *self);
void		set_philo_times(t_philos *self, t_args args);
void		my_usleep(int time);

#endif
