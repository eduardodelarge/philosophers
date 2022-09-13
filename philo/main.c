/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caeduard <caeduard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:53:30 by caeduard          #+#    #+#             */
/*   Updated: 2022/09/13 01:15:04 by caeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int initialize_philos(t_args *args, int ac, char **av)
{
	args->n_philo = ft_atoi(av[1]);
	args->time_tdie = ft_atoi(av[2]);
	args->time_teat = ft_atoi(av[3]);
	args->time_tsleep = ft_atoi(av[4]);
	args->death = 0;
	args->must_eat = -1;
	args->times_ate = 0;
	args->o_time = get_time();
	pthread_mutex_init(&args->lock_death, NULL);
	pthread_mutex_init(&args->times_eat_lock, NULL);
	if (ac == 6)
	{
		args->must_eat = ft_atoi(av[5]);
		parse_errors(args, ac);
	}
	parse_errors(args, ac);
	return(0);
}

int main(int ac, char **av)
{
	// init main
}
