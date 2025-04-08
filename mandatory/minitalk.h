/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:34:52 by rgiraud           #+#    #+#             */
/*   Updated: 2025/04/08 16:27:36 by ael-most         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

# define I_TIME 10

typedef struct s_data
{
	pid_t			sender;
	char			*msg;
	size_t			id;
	unsigned char	c;
	int				c_index;
	size_t			len;
	int				m_index;
}	t_data;
void	ft_reset_val(t_data *data);

#endif
