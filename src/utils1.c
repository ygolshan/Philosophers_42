/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:50:58 by ygolshan          #+#    #+#             */
/*   Updated: 2023/06/27 09:18:28 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	divisor;
	int	digit;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	divisor = 1;
	while (n / divisor >= 10)
		divisor *= 10;
	while (divisor > 0)
	{
		digit = n / divisor;
		ft_putchar_fd((char)(digit + '0'), fd);
		n %= divisor;
		divisor /= 10;
	}
}

void	ft_put_unbr_fd(unsigned int n, int fd)
{
	char	buffer[20];
	int		index;

	index = 0;
	while (n > 0)
	{
		buffer[index++] = (char)(n % 10 + '0');
		n /= 10;
	}
	while (index > 0)
		ft_putchar_fd(buffer[--index], fd);
}

void	ft_putstr_fd(char const *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	int				res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * res);
}
