/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivar <ivar@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:11:06 by ivar              #+#    #+#             */
/*   Updated: 2025/02/04 13:11:07 by ivar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static int	g_len_status = 0;

static void	process_message_length(size_t *len, char ch, char **message)
{
	if (ch == '\0')
	{
		g_len_status = 1;
		*message = (char *)malloc(sizeof(char) * (*len));
		if (!*message)
			ft_error("Error: Memory allocation failed for message\n");
	}
	else if (ch >= '0' && ch <= '9')
	{
		*len = (ch - '0') + (*len * 10);
	}
}

static void	append_to_message(char *message, unsigned char ch)
{
	static size_t	index = 0;

	if (!message)
		return ;
	message[index++] = ch;
	if (ch == '\0')
	{
		index = 0;
		g_len_status = 2;
	}
}

static void	output_message_and_cleanup(char **str, size_t *len, siginfo_t *info)
{
	write(1, *str, *len);
	*len = 0;
	free(*str);
	*str = NULL;
	g_len_status = 0;
	kill(info->si_pid, SIGUSR2);
}

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	current_char = 0;
	static unsigned int		bit_position = 0;
	static size_t			message_length = 0;
	static char				*message = NULL;

	(void)ucontext;
	if (sig == SIGUSR1)
		current_char <<= 1;
	else if (sig == SIGUSR2)
		current_char = (current_char << 1) | 1;
	bit_position++;
	if (bit_position == 8)
	{
		if (g_len_status == 0)
			process_message_length(&message_length, current_char, &message);
		else if (g_len_status == 1)
			append_to_message(message, current_char);
		current_char = 0;
		bit_position = 0;
	}
	if (g_len_status == 2)
		output_message_and_cleanup(&message, &message_length, info);
	else
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	char				*pid_str;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Error: Failed to set up signal handlers\n");
	write(1, "> PID: ", sizeof("> PID: "));
	pid_str = ft_stoa(getpid());
	write(1, pid_str, ft_strlen(pid_str));
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
