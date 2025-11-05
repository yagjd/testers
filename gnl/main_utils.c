/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:15:30 by marhuber          #+#    #+#             */
/*   Updated: 2025/10/31 22:28:37 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	parallel_reading(int *fd)
{
	int		keep_reading;
	int		i;
	char	*line;

	keep_reading = 1;
	while (keep_reading)
	{
		keep_reading = 0;
		i = 0;
		while (i < 5)
		{
			line = get_next_line(fd[i]);
			if (line)
			{
				ft_putstr_fd(line, fd[10 + i]);
				free (line);
				keep_reading = 1;
			}
			i++;
		}
	}
}

char	*diff_command(char *fn_a, char *fn_b)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("diff ", fn_a);
	tmp2 = ft_strjoin(tmp1, " ");
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, fn_b);
	free(tmp2);
	return (tmp1);
}

void	execbatterytest(char **argv)
{
	int		i;
	int		fd[20];
	char	*cmd;

	i = 0;
	while (i < 5)
	{
		fd[i] = open(argv[1 + i], O_RDONLY);
		fd[10 + i] = open(argv[11 + i], O_WRONLY | O_CREAT | O_TRUNC, 0664);
		i++;
	}
	parallel_reading(fd);
	i = 0;
	while (i < 5)
	{
		close(fd[i]);
		close(fd[10 + i]);
		cmd = diff_command(argv[1 + i], argv[11 + i]);
		if (!system(cmd))
			ft_putendl_fd("ok\n", 1);
		free(cmd);
		i++;
	}
}
