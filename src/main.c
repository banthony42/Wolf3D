/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 01:01:07 by banthony          #+#    #+#             */
/*   Updated: 2018/04/17 19:09:38 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static size_t	line_is_valid(char *line)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (ft_isdigit((int)line[i]))
			len++;
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	return (len);
}

static size_t	tab_is_valid(char **tab, t_wolf *wolf)
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
			wolf_exit(ERR_MAP, -1, wolf);
		i++;
	}
	ft_putstr("Map OK!");
	return (len);
}

static void		usage(char *bin)
{
	ft_putstr("Error: Usage ");
	ft_putstr(bin);
	ft_putendl(" [file.txt]");
	ft_exit(NULL, -1);
}

void			wolf_exit(char *str, int status, t_wolf *wolf)
{
	if (wolf && wolf->map)
		ft_freetab(wolf->map);
	ft_exit(str, status);
}

/*
**	Les event clavier sont gere par mlx_hook sur un appui de touche
*/

int				main(int ac, char **av)
{
	char	*line;
	int		fd;
	t_wolf	wolf;

	line = NULL;
	ft_bzero(&wolf, sizeof(wolf));
	if (ac != 2)
		usage(av[0]);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		ft_exit(ERR_OPEN, -1);
	while ((get_next_line(fd, &line)) > 0)
	{
		wolf.map = ft_tabadd(wolf.map, line);
		ft_strdel(&line);
	}
	tab_is_valid(wolf.map, &wolf);
	if (close(fd) < 0)
		wolf_exit(ERR_CLOSE, -1, &wolf);
	init(&wolf);
	mlx_mouse_hook(wolf.win, mousehook, &wolf);
	mlx_loop_hook(wolf.mlx, refresh, &wolf);
	mlx_hook(wolf.win, KEY_PRESS, KEY_PRESS_MASK, keypress, &wolf);
	mlx_hook(wolf.win, KEY_RELEASE, KEY_RELEASE_MASK, keyrelease, &wolf);
	mlx_loop(wolf.mlx);
	return (0);
}
