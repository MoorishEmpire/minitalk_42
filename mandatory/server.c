/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-most <ael-most@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:18:13 by ael-most          #+#    #+#             */
/*   Updated: 2025/04/08 16:26:23 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

void	ft_reset_val(t_data *data)
{
	free(data->msg);
	data->sender = 0;
	data->msg = NULL;
	data->id = 0;
	data->c = 0;
	data->c_index = 0;
	data->len = 0;
	data->m_index = 0;
}

void	alloc_handler(int nbr)
{
	if (nbr <= 0)
		ft_reset_val(&g_data);
	g_data.msg = ft_calloc((g_data.len) + 1, 1);
	if (!g_data.msg)
		ft_reset_val(&g_data);
}

static void	process_msg_data(int signum)
{
	if (g_data.c_index < 8)
	{
		if (signum == SIGUSR1)
			g_data.c = (g_data.c << 1);
		else
			g_data.c = (g_data.c << 1) | 1;
		g_data.c_index++;
	}
	if (g_data.c_index == 8)
	{
		g_data.msg[g_data.m_index++] = g_data.c;
		g_data.c = 0;
		g_data.c_index = 0;
	}
}

void	sig_handler(int signum, siginfo_t *info, void *con)
{
	(void) con;
	if (g_data.sender != 0 && (g_data.sender != info->si_pid))
		ft_reset_val(&g_data);
	else if (g_data.sender == 0)
		g_data.sender = info->si_pid;
	if (g_data.id == 32)
		alloc_handler(g_data.len);
	if (g_data.id < 32 && (signum == SIGUSR1 || signum == SIGUSR2))
	{
		if (signum == SIGUSR1)
			g_data.len = (g_data.len << 1);
		else
			g_data.len = (g_data.len << 1) | 1;
	}
	else if (g_data.id >= 32 && (signum == SIGUSR1 || signum == SIGUSR2))
		process_msg_data(signum);
	g_data.id++;
	if (g_data.id == ((g_data.len * 8) + 32))
	{
		ft_printf("\033[1;92m%s\033[0m\n", g_data.msg);
		ft_reset_val(&g_data);
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("\033[1;92mServer started!\033[0m\n");
	ft_printf("\033[1;94m--> Server PID: \033[1;93m%d\033[0m\n", getpid());
	ft_printf("\033[1;90mWaiting for messages...\033[0m\n");
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
