/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npizzi <npizzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:13:47 by npizzi            #+#    #+#             */
/*   Updated: 2025/02/08 14:16:44 by npizzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_THREADS 200
# define MAX_USLEEP 10000

# define RED "\x1b[31m"
# define REEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

# define BOLD "\x1b[1m"
# define DIM "\x1b[2m"
# define ITALIC "\x1b[3m"
# define UNDERLINE "\x1b[4m"
# define BLINKING "\x1b[5m"
# define REVERSE "\x1b[7m"
# define STRIKETHROUGH "\x1b[9m"

# define PARAM_ERR 0
# define PHIL_ERR 1
# define ZERO_ERR 2
# define USLEEP_ERR 3

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_param_data
{
	bool					is_phil_dead;
	int						how_many_spaghetti;
	int						philosophers_number;
	__useconds_t			die_time;
	__useconds_t			eat_time;
	__useconds_t			sleep_time;
	size_t					starting_milliseconds;
	pthread_mutex_t			display_mutex;
	pthread_mutex_t			update_mutex;
	pthread_mutex_t			bool_mutex;

}							t_param_data;

typedef struct s_philosopher
{
	int						philosopher_num;
	int						spaghetti_eaten;
	size_t					last_meal;
	pthread_t				thread;
	pthread_mutex_t			fork_mutex;
	struct s_param_data		*data;
	struct s_philosopher	*previous;
	struct s_philosopher	*next;

}							t_philosopher;

// CHECKER FUNCTIONS

bool						are_args_valid(int argc, char *argv[]);
bool						are_arguments_in_limits(int argc, char *argv[]);

// STRUCT INITIALIZING FUNCTIONS

t_philosopher				*init_philo(t_param_data *data);
t_param_data				*init_data_struct(int argc, char *argv[]);

// THREADS FUNCTIONS

int							start_the_dinner(t_philosopher *head,
								t_param_data *data, int phil_num);
void						*dinner(void *philosopher_head);

// GENERAL UTILS FUNCTIONS

bool						read_or_update_death(t_param_data *data, char mode);
void						ft_usleep(size_t milliseconds, t_param_data *data);
void						ft_free_all(t_philosopher **head,
								t_param_data **data);
void						locked_printing(size_t begin, int phil_num,
								t_param_data *data, char *action);
int							simple_atoi(char *nptr);
size_t						get_time_in_milliseconds(void);

//ERROR FUNCTION

void						printerr(int errtype);
#endif
