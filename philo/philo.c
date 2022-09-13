/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caeduard <caeduard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:55:32 by caeduard          #+#    #+#             */
/*   Updated: 2022/09/13 01:02:29 by caeduard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos(t_args *phil, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&phil->times_eat_lock);
		if (phil->must_eat * phil->n_philo == phil->times_ate)
		{
			pthread_mutex_lock(&phil->lock_death);
			phil->death = 1;
			pthread_mutex_unlock(&phil->lock_death);
			return (0);
		}
		pthread_mutex_unlock(&phil->times_eat_lock);
		pthread_mutex_lock(&philo->lock_last_ate);
		if (get_time() - philo->last_ate - phil->o_time > phil->time_tdie)
		{
			pthread_mutex_lock(&phil->lock_death);
			phil->death = 1;
			pthread_mutex_unlock(&phil->lock_death);
			printf("[%lld] Philo %d %s\n", get_time() - phil->o_time,
				philo->philo_id, DIED);
			return (0);
		}
		pthread_mutex_unlock(&philo->lock_last_ate);
	}
}

void	philosophers(t_philo *mutexes, t_args *args)
{
	pthread_mutex_lock(&mutexes->fork);
	printf("[%lld] Philo %d %s", get_time() - args->o_time,
		mutexes->philo_id, FORK);
	pthread_mutex_lock(&mutexes->fork);
	printf("[%lld] Philo %d %s", get_time() - args->o_time,
		mutexes->philo_id, FORK);
	pthread_mutex_lock(&mutexes->lock_last_ate);
	mutexes->last_ate = get_time() - args->o_time;
	pthread_mutex_unlock(&mutexes->lock_last_ate);
	printf("[%lld] Philo %d %s", get_time() - args->o_time,
		mutexes->philo_id, EAT);
	u_sleep(args->time_teat);
	printf("[%lld] Philo %d %s", get_time() - args->o_time,
		mutexes->philo_id, SLEEP);
	pthread_mutex_unlock(&mutexes->fork);
	pthread_mutex_unlock(&mutexes->fork);
	u_sleep(args->time_tsleep);
	printf("[%lld] Philo %d %s", get_time() - args->o_time,
		mutexes->philo_id, THINK);
}

void	*living_philo(t_philo *philo, t_args *data)
{
	int	i;

	i = 0;
	u_sleep(!(philo->philo_id % 2) * 2);
	while ((i++ < data->times_ate || data->times_ate == -1) && !data->death)
		philosophers(philo, data);
	return (NULL);
}

int	thread_initalization(t_args *args)
{
	int		i;
	t_philo *phil;

	i = 0;
	phil = NULL;
	while (i < args->n_philo)
	{
		if (pthread_create(&phil->thread, NULL, (void *)living_philo, (void *)&phil[i]))
		{
			printf("Error on threads\n");
			return(1);
		}
		i++;
	}
	philos(args, phil);
	return(0);
}