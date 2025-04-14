/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:20:23 by npizzi            #+#    #+#             */
/*   Updated: 2025/02/08 13:10:16 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*get_last_meal(t_philosopher *phil_head)
{
	t_philosopher	*ptr;
	t_philosopher	*phil;
	int				i;

	ptr = phil_head;
	phil = ptr;
	i = phil->data->philosophers_number;
	while (i-- > 0)
	{
		if (ptr->last_meal < phil->last_meal)
			phil = ptr;
		ptr = ptr->next;
	}
	return (phil);
}

void	*death_check_routine(void *phil_head)
{
	t_philosopher	*ptr;
	t_philosopher	*phil;
	size_t			die_time;
	size_t			current_time;

	ptr = (t_philosopher *)phil_head;
	die_time = ptr->data->die_time;
	while (true)
	{
		pthread_mutex_lock(&ptr->data->update_mutex);
		phil = get_last_meal(ptr);
		if (phil->spaghetti_eaten == phil->data->how_many_spaghetti)
			return (pthread_mutex_unlock(&ptr->data->update_mutex), NULL);
		current_time = get_time_in_milliseconds();
		if (current_time - phil->last_meal >= die_time)
		{
			locked_printing(phil->data->starting_milliseconds,
				phil->philosopher_num, phil->data, "died");
			return (pthread_mutex_unlock(&ptr->data->update_mutex), NULL);
		}
		pthread_mutex_unlock(&ptr->data->update_mutex);
		usleep(200);
	}
	return (NULL);
}

int	finish_the_dinner(t_philosopher *head, int phil_num, pthread_t death_t)
{
	while (phil_num-- > 0)
	{
		if (pthread_join(head->thread, NULL) != 0)
			return (printf("Error in joining the philo thread\n"), 2);
		head = head->next;
	}
	if (pthread_join(death_t, NULL) != 0)
		return (printf("Error in joining the death thread\n"), 3);
	return (0);
}

int	start_the_dinner(t_philosopher *head, t_param_data *data, int phil_num)
{
	t_philosopher	*ptr;
	pthread_t		death_checking_thread;

	ptr = head;
	if (data->philosophers_number % 2 == 0)
		ptr = head->next;
	data->starting_milliseconds = get_time_in_milliseconds();
	while (phil_num-- > 0)
	{
		ptr->last_meal = get_time_in_milliseconds();
		if (pthread_create(&ptr->thread, NULL, dinner, (void *)ptr) != 0)
			return (printf("Error in creating thread\n"), 1);
		ptr = ptr->next;
	}
	if (pthread_create(&death_checking_thread, NULL, death_check_routine,
			(void *)head) != 0)
		printf("Error in creating the death thread\n");
	return (finish_the_dinner(head, data->philosophers_number,
			death_checking_thread));
}
