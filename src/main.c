/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 01:01:07 by banthony          #+#    #+#             */
/*   Updated: 2018/04/08 11:52:16 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>
#include <fcntl.h>

static size_t line_is_valid(char *line)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	while(line[i])
	{
		if (ft_isdigit((int)line[i]))
			len++;
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	return (len);
}

static size_t	tab_is_valid(char **tab)
{
	size_t i;
	size_t len;
	size_t tmp;

	if ((len = ft_tablen(tab)) > MAP_MAX)
	{
		ft_putendl(ERR_MAP);
		return (0);
	}
	i = 0;
	while (i < len)
	{
		tmp = line_is_valid(tab[i]);
		if (!tmp || tmp != len)
		{
			ft_putendl(ERR_MAP);
			return (0);
		}
		i++;
	}
	return (len);
}

static void usage(char *bin)
{
	ft_putstr("Error: Usage ");
	ft_putstr(bin);
	ft_putendl(" [file.txt]");
}

int main(int ac, char **av)
{
	char *line;
	int fd, ret;
	t_wolf wolf;

	line = NULL;
	wolf.map = NULL;
	if (ac != 2)
		usage(av[0]);
	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		wolf.map = ft_tabadd(wolf.map, line);
		ft_strdel(&line);
	}

	if (!tab_is_valid(wolf.map))
		return (0);
	else
		ft_putstr("Map OK!");
	init(&wolf);
	mlx_key_hook(wolf.win, keyhook, &wolf);
	mlx_loop(wolf.mlx);
	ft_freetab(wolf.map);
	return (0);
}
