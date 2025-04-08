/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:18:08 by ael-most          #+#    #+#             */
/*   Updated: 2025/04/08 16:26:11 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_synch_bit;

static void	_send_char(int pid, unsigned char c)
{
	int	i;

	i = 128;
	while (i > 0)
	{
		g_synch_bit = 0;
		if (c >= i)
		{
			kill(pid, SIGUSR2);
			c -= i;
		}
		else
			kill(pid, SIGUSR1);
		i /= 2;
		while (g_synch_bit != 1)
			usleep(100);
	}
}

static void	_sendlen(int pid, int len)
{
	char	*_len;
	int		i;

	i = 3;
	_len = (char *)&len;
	while (i >= 0)
	{
		_send_char(pid, _len[i]);
		i--;
	}
}

static void	_handler(int pid, char *msg)
{
	int	i;

	i = ft_strlen(msg);
	if (!i)
		return ;
	_sendlen(pid, i);
	i = 0;
	while (msg[i])
		_send_char(pid, msg[i++]);
	_send_char(pid, '\0');
	ft_printf("\033[1;92mMessage sent successfully.\033[0m\n");
}

void	check_send(int signum)
{
	if (signum == SIGUSR1)
		g_synch_bit = 1;
}

int	main(int argc, char **argv)
{
	int	pid_server;

	if (argc != 3)
	{
		ft_printf("\033[0;95mError\n");
		ft_printf("Usage: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	signal(SIGUSR1, &check_send);
	pid_server = ft_atoi(argv[1]);
	if (pid_server <= 2)
	{
		ft_printf("Invalid PID!\n");
		exit(EXIT_FAILURE);
	}
	_handler(pid_server, argv[2]);
	return (0);
}
