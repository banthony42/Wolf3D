/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 01:01:07 by banthony          #+#    #+#             */
/*   Updated: 2018/08/09 17:43:50 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static size_t	line_is_valid(char *line, size_t y, size_t sizetab)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	if (!ft_strchr(WALL, line[0])
		|| !ft_strchr(WALL, (int)line[ft_strlen(line) - 1]))
		return (0);
	while (line[i])
	{
		if ((y == 0 || y == sizetab) && !ft_strchr(WALL, line[i]))
			return (0);
		if (ft_isdigit((int)line[i]))
			len++;
		else
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

	len = 0;
	if (!tab || (len = ft_tablen(tab)) > MAP_MAX || len < MAP_MIN)
		wolf_exit(ERR_MAP, -1, wolf);
	i = 0;
	wolf->map_size.y = (int)len;
	while (i < len)
	{
		if (!(tmp = line_is_valid(tab[i], i, len))
			|| tmp < MAP_MIN || tmp > MAP_MAX)
			wolf_exit(ERR_MAP, -1, wolf);
		if ((int)tmp > wolf->map_size.x)
			wolf->map_size.x = (int)tmp;
		i++;
	}
	ft_printtab(tab, ft_putstr, "\n");
	ft_putstr("\nMap OK!\n");
	ft_putnbr(wolf->map_size.x);
	ft_putstr(" x ");
	ft_putnbrendl(wolf->map_size.y);
	return (len);
}

static void		usage(char *bin)
{
	ft_putstr("Error: Usage ");
	ft_putstr(bin);
	ft_putendl(" [file.txt]");
	ft_exit(NULL, -1);
}

static void		wolf_run(t_wolf wolf)
{
	init(&wolf);
	mlx_mouse_hook(wolf.win, mousehook, &wolf);
	mlx_loop_hook(wolf.mlx, refresh, &wolf);
	mlx_hook(wolf.win, KEY_PRESS, KEY_PRESS_MASK, keypress, &wolf);
	mlx_hook(wolf.win, KEY_RELEASE, KEY_RELEASE_MASK, keyrelease, &wolf);
	mlx_loop(wolf.mlx);
}

/*
**	Les event clavier sont gere par mlx_hook sur un appui de touche
*/

int				main(int ac, char **av)
{
	char	*tmp;
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
		tmp = ft_strtrim2(line);
		wolf.map = ft_tabadd(wolf.map, tmp);
		ft_strdel(&tmp);
		ft_strdel(&line);
	}
	tab_is_valid(wolf.map, &wolf);
	if (close(fd) < 0)
		wolf_exit(ERR_CLOSE, -1, &wolf);
	wolf_run(wolf);
	return (0);
}
