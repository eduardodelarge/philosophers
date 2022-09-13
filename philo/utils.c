/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caeduard <caeduard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:55:52 by caeduard          #+#    #+#             */
/*   Updated: 2022/09/13 01:02:21 by caeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
	@brief: u_sleep sleeps for a given amount of time in microseconds
	@param: time time to sleep in microseconds
*/
int	u_sleep(useconds_t usec)
{
	useconds_t	before;
	useconds_t	after;

	before = get_time();
	after = before;
	while (after - before < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = get_time();
	}
	return (0);
}

/*
	@brief: ft_atoi converts a string to an integer
	@param: str string to convert
	@return: integer
*/
int	ft_atoi(char *str)
{
	int		i;
	long	r;
	int		k;

	i = 0;
	r = 0;
	k = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r * k);
}

void parse_errors(t_args *args, int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments.\n");
		exit (1);
	}
	if (args->n_philo < 1)
	{
		printf("Error: Number of philosophers must be more than 1\n");
		exit(1);
	}
	if (args->time_tdie < 0 || args->time_teat < 0 || args->time_tsleep < 0)
	{
		printf("Error: Time to die, eat and sleep must be more than 0.\n");
		exit(1);
	}
	if (args->must_eat < -1)
	{
		printf("Error: Number of times each philosopher must eat must be at least -1.\n");
		exit(1);
	}
}