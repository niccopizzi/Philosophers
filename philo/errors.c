/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:29:41 by npizzi            #+#    #+#             */
/*   Updated: 2025/02/08 13:45:20 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printerr(int errtype)
{
	if (errtype == PARAM_ERR)
	{
		printf(RED BOLD "DISASTER! INCORRECT NUMBER OF ARGS\n"
			"This is the parameters I can accept\n"
			"1) <number_of_philosophers>\n"
			"2) <time_to_die>\n"
			"3) <time_to_eat>\n"
			"4) <time_to_sleep>\n"
			"5) <number_of_times_each_philosopher_must_eat> (optional)\n"
			RESET);
	}
	else if (errtype == PHIL_ERR)
		printf(YELLOW BOLD "Sorry but we don't have that many philosophers\n"
			"Please insert a lower number!\n" RESET);
	else if (errtype == ZERO_ERR)
		printf(YELLOW BOLD
			"Mmmmh .. We don't like 0 in here, try something else\n" RESET);
	else if (errtype == USLEEP_ERR)
		printf(YELLOW BOLD "Woah, that's a big number!"
			" Usleep doesn't like it :(\n" RESET);
}
