/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 01:01:07 by banthony          #+#    #+#             */
/*   Updated: 2018/09/08 16:19:30 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static size_t	line_is_valid(char *line, size_t y, size_t sizetab)
{
	size_t	i;
	size_t	len;
	int		spawner;

	i = 0;
	len = 0;
	spawner = 0;
	if (!ft_strchr(WALL, line[0])
		|| !ft_strchr(WALL, (int)line[ft_strlen(line) - 1]))
		return (0);
	while (line[i])
	{
		if ((y == 0 || y == sizetab) && !ft_strchr(WALL, line[i]))
			return (0);
		if ((ft_strchr(";", line[i])))
			spawner++;
		if (ft_isdigit((int)line[i]))
			len++;
		else if (line[i] != '0' + T_SPAWN)
			return (0);
		i++;
	}
	if (spawner > 1)
		return (0);
	return (len);
}

size_t			tab_is_valid(char **tab, t_wolf *wolf, int save_size)
{
	int		i;
	size_t	len;
	size_t	tmp;

	if ((len = ft_tablen(tab)) > MAP_MAX || len < MAP_MIN)
		wolf_exit(ERR_MAP, -1, wolf);
	i = -1;
	if (save_size)
		wolf->map_size.y = (int)len;
	while (++i < (int)len)
	{
		if (!(tmp = line_is_valid(tab[i], (size_t)i, len - 1))
			|| tmp < MAP_MIN || tmp > MAP_MAX)
		{
			ft_putendl(ERR_MAP);
			return (0);
		}
		if ((int)tmp > wolf->map_size.x && save_size)
			wolf->map_size.x = (int)tmp;
	}
	ft_printtab(tab, ft_putstr, "\n");
	ft_putstr("\nMap OK!\n");
	return (len);
}

static void		usage(char *bin)
{
	ft_putstr("Error: Usage ");
	ft_putstr(bin);
	ft_putendl(" [file.txt]\n\nGame control:");
	ft_putstr(KEY_1);
	ft_putstr(KEY_2);
	ft_putstr(KEY_3);
	ft_putendl("\nMap creator control:");
	ft_putendl(MC_USAGE);
	ft_putendl("To design a map you can use:");
	ft_putstr(HELP_1);
	ft_putstr(HELP_2);
	ft_putstr(HELP_3);
	ft_putendl("Spawn is optional.");
	ft_putendl("Minimum size map is 3 x 3 character.");
	ft_putendl("Maximum size map is 500 x 500 character.");
	ft_putstr("A map can contain only ");
	ft_putnbr(MAX_DOOR);
	ft_putendl(" doors.");
	ft_exit(NULL, -1);
}

static void		wolf_run(t_wolf wolf)
{
	init(&wolf);
	mlx_mouse_hook(wolf.win, mousehook, &wolf);
	mlx_loop_hook(wolf.mlx, refresh, &wolf);
	mlx_hook(wolf.win, DESTROY_NOTIFY, STRUCT_NOTIFY_MASK, close_win, &wolf);
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
	if (!(tab_is_valid(wolf.map, &wolf, 1)))
		wolf_exit(NULL, -1, &wolf);
	if (close(fd) < 0)
		wolf_exit(ERR_CLOSE, -1, &wolf);
	wolf_run(wolf);
	return (0);
}
