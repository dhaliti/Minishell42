/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperras <jperras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:34:45 by jperras           #+#    #+#             */
/*   Updated: 2022/05/24 18:31:49 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static void	ft_builtin_redirect2(t_minishell *shell, char *tmp)
{
	if (ft_strcmp(shell->input[1], ">"))
	{
		shell->fd_out = open(shell->input2[2], \
			O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if (shell->fd_out < 0)
		{
			printf("%s: No such file or directory\n", shell->input2[2]);
			return ;
		}
		ft_putstr_fd(tmp, shell->fd_out);
	}
	if (ft_strcmp(shell->input[1], ">>"))
	{
		shell->fd_out = open(shell->input2[2], \
			O_WRONLY | O_APPEND | O_CREAT, 0664);
		if (shell->fd_out < 0)
		{
			printf("%s: No such file or directory\n", shell->input2[2]);
			return ;
		}
		ft_putstr_fd(tmp, shell->fd_out);
	}
}

void	ft_buildin_pwd(t_minishell *shell)
{
	char	tmp[2048];

	if (shell->input[1] && !(ft_strcmp(shell->input[1], ">"))
		&& !(ft_strcmp(shell->input[1], ">>")))
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	if (getcwd(tmp, sizeof(tmp)) == NULL)
	{
		printf("Pwd error");
		g_st = 1;
		return ;
	}
	if (shell->input2[1])
	{
		if (ft_strcmp(shell->input2[1], ">")
			|| ft_strcmp(shell->input2[1], ">>"))
			ft_builtin_redirect2(shell, tmp);
	}
	else
		printf("%s\n", tmp);
	g_st = 0;
}
