/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:38:02 by npizzi            #+#    #+#             */
/*   Updated: 2025/02/08 13:38:06 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_for_one(void *philos_head)
{
	t_philosopher	*phil;

	phil = (t_philosopher *)philos_head;
	phil->data->starting_milliseconds = get_time_in_milliseconds();
	pthread_mutex_lock(&phil->fork_mutex);
	locked_printing(phil->data->starting_milliseconds, 1, phil->data,
		"has taken a fork");
	ft_usleep(phil->data->die_time, phil->data);
	locked_printing(phil->data->starting_milliseconds, 1, phil->data, "died");
	pthread_mutex_unlock(&phil->fork_mutex);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_param_data	*data;
	t_philosopher	*head;

	if (argc < 5 || argc > 6)
		return (printerr(PARAM_ERR), 1);
	if (are_args_valid(argc, argv) == false || are_arguments_in_limits(argc,
			argv) == false)
		return (2);
	data = init_data_struct(argc, argv);
	if (data == NULL)
		return (4);
	head = init_philo(data);
	if (head == NULL)
		return (5);
	if (data->philosophers_number == 1)
	{
		pthread_create(&head->thread, NULL, dinner_for_one, (void *)head);
		pthread_join(head->thread, NULL);
	}
	else
		start_the_dinner(head, data, data->philosophers_number);
	ft_free_all(&head, &data);
	return (0);
}
