/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:44:19 by marhuber          #+#    #+#             */
/*   Updated: 2025/10/31 22:56:00 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "main.h"

void	execbatterytest(char **argv);

void	testshow(char *filename, int lines)
{
	int		fd;
	int		n;
	char	*str;

	fd = open(filename, O_RDONLY);
	n = lines;
	fd = open("testtxt.txt", O_RDONLY);
	ft_putnbr_fd(fd, 1);
	ft_putstr_fd("\n", 1);
	while (n)
	{
		ft_putnbr_fd(lines - n + 1, 1);
		ft_putstr_fd("\n", 1);
		str = get_next_line(fd);
		if (str)
			ft_putstr_fd(str, 1);
		else
			ft_putstr_fd(">> NULL pointer <<\n", 1);
		ft_putstr_fd("------------------\n", 1);
		n--;
		free(str);
	}
	close(fd);
}

void	testfilecmp(char *infile)
{
	int		fdin;
	int		fdout;
	char	*line;
	char	*it;

	fdin = open(infile, O_RDONLY);
	fdout = open("out.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	line = get_next_line(fdin);
	while (line)
	{
		it = line;
		while (*it)
			write(fdout, it++, 1);
		free(line);
		line = get_next_line(fdin);
	}
	free(line);
	close(fdin);
	close(fdout);
	line = ft_strjoin(infile, " out.txt");
	it = ft_strjoin("diff ", line);
	if (!system(it))
		ft_putendl_fd("\tok", 1);
	free(line);
	free(it);
}

void	teststdin(void)
{
	char	*line;

	ft_putstr_fd("Type a line, please\n", 1);
	line = get_next_line(0);
	ft_putstr_fd("You typed:\n", 1);
	ft_putstr_fd(line, 1);
	free(line);
}

void	setbatterytest(char **argv)
{
	int		i;
	int		j;
	int		fdin;
	int		fdout;
	char	*line;

	i = 0;
	fdin = open("test150lines.txt", O_RDONLY);
	while (i < 5)
	{
		fdout = open(argv[1 + i], O_WRONLY | O_CREAT | O_TRUNC, 0664);
		j = 0;
		while (j < 26 + 2 * i)
		{
			line = get_next_line(fdin);
			ft_putstr_fd(line, fdout);
			free (line);
			j++;
		}
		close(fdout);
		i++;
	}
	close(fdin);
}

int	main(int argc, char **argv)
{
	ft_putnbr_fd(BUFFER_SIZE, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(FOPEN_MAX, 1);
	ft_putstr_fd("\n", 1);
	if (argc == 1)
		teststdin();
	else if (argc == 2)
		testfilecmp(argv[1]);
	else if (argc == 11)
		setbatterytest(argv);
	else if (argc == 21)
		execbatterytest(argv);
	else if (argc == 3)
		testshow(argv[1], ft_atoi(argv[2]));
	else
		testshow("testtxt.txt", 110);
}
