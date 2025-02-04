/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivar <ivar@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:11:02 by ivar              #+#    #+#             */
/*   Updated: 2025/02/04 13:11:03 by ivar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static volatile int	g_signal_received = 0;

static void	send_bit(int pid, char bit)
{
	int	shift;

	shift = 8;
	while (shift--)
	{
		if ((bit >> shift) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error("Error: Failed to send SIGUSR2 signal\n");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error("Error: Failed to send SIGUSR1 signal\n");
		}
		while (!g_signal_received)
			;
		g_signal_received = 0;
	}
}

static void	handle_signal(int sig)
{
	if (sig == SIGUSR2)
		write(1, "Transmission successfully received.\n", 37);
	g_signal_received = 1;
}

static void	send_message_length(int pid, const char *message)
{
	char	*length_str;
	size_t	i;

	length_str = ft_stoa(ft_strlen(message) + 2);
	if (!length_str)
		ft_error("Error: Memory allocation failed for length string\n");
	i = 0;
	while (length_str[i])
		send_bit(pid, length_str[i++]);
	send_bit(pid, '\0');
	free(length_str);
}

static void	send_full_message(int pid, const char *message)
{
	while (*message)
		send_bit(pid, *message++);
	send_bit(pid, '\n');
	send_bit(pid, '\0');
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	size_t				pid;

	if (argc != 3)
		ft_error("Error: Incorrect number of arguments. Usage: "
			"./client <PID> <Message>\n");
	pid = ft_atos(argv[1]);
	if (pid == 0)
		ft_error("Error: Invalid PID");
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_signal;
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_error("Error: Failed to set up SIGUSR1 handler\n");
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Error: Failed to set up SIGUSR2 handler\n");
	send_message_length(pid, argv[2]);
	send_full_message(pid, argv[2]);
	return (0);
}
