/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 20:00:50 by banthony          #+#    #+#             */
/*   Updated: 2018/09/10 15:29:26 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Cette fonction verifie que les blocs adjacent d'une porte sont:
**	Deux blocs vide en ligne et Deux murs en ligne.
**	Le premier if correspond a deux murs en ligne vertical (y).
**	Le deuxieme corresspond a deux murs en ligne horizontal (x).
*/

static void		check_empty(char **map, t_coord i, int *j)
{
	if (map[i.y][i.x] == '0')
		*j += 1;
}

static int		check_adjacent_to_door(char **map, t_coord i)
{
	if (map[i.y][i.x] == '0' + T_DOOR)
	{
		if ((ft_strchr(WALL, map[i.y - 1][i.x])
		&& ft_strchr(WALL, map[i.y + 1][i.x]))
		&& ft_strchr(EMPTY_BLOC, map[i.y][i.x - 1])
		&& ft_strchr(EMPTY_BLOC, map[i.y][i.x + 1]))
			;
		else if ((ft_strchr(WALL, map[i.y][i.x - 1])
		&& ft_strchr(WALL, map[i.y][i.x + 1]))
		&& ft_strchr(EMPTY_BLOC, map[i.y - 1][i.x])
		&& ft_strchr(EMPTY_BLOC, map[i.y + 1][i.x]))
			;
		else
		{
			ft_putstr(ERR_DOOR_PLACEMENT);
			ft_putnbr(i.y);
			ft_putstr(" x ");
			ft_putnbr(i.x);
			ft_putendl(" coordinate.");
			return (1);
		}
	}
	return (0);
}

static int		map_is_incoherent(char **map)
{
	t_coord i;
	int		j;
	int		error;

	j = 0;
	error = 0;
	i.y = -1;
	while (map[++i.y])
	{
		i.x = -1;
		while (map[i.y][++i.x])
		{
			check_empty(map, i, &j);
			error |= check_adjacent_to_door(map, i);
		}
	}
	if (j == 0 || error)
	{
		ft_putendl(ERR_MAP);
		return (1);
	}
	ft_printtab(map, ft_putstr, "\n");
	ft_putstr("\nMap OK!\n");
	return (0);
}

static size_t	line_is_valid(char *line, size_t y, size_t sizetab, int *spawn)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!ft_strchr(WALL, line[0])
		|| !ft_strchr(WALL, (int)line[ft_strlen(line) - 1]))
		return (0);
	while (line[i])
	{
		if ((y == 0 || y == sizetab) && !ft_strchr(WALL, line[i]))
			return (0);
		if (line[i] == '0' + T_SPAWN)
			*spawn += 1;
		if (ft_isdigit((int)line[i]))
			len++;
		else if (line[i] != '0' + T_SPAWN)
			return (0);
		i++;
	}
	if (*spawn > 1)
		return (0);
	return (len);
}

size_t			map_is_valid(char **map, t_wolf *wolf, int save_size)
{
	int		i;
	size_t	len;
	size_t	tmp;
	int		spawn;

	spawn = 0;
	if ((len = ft_tablen(map)) > MAP_MAX || len < MAP_MIN)
		wolf_exit(ERR_MAP, -1, wolf);
	i = -1;
	if (save_size)
		wolf->map_size.y = (int)len;
	while (++i < (int)len)
	{
		if (!(tmp = line_is_valid(map[i], (size_t)i, len - 1, &spawn))
			|| tmp < MAP_MIN || tmp > MAP_MAX)
		{
			ft_putendl(ERR_MAP);
			return (0);
		}
		if ((int)tmp > wolf->map_size.x && save_size)
			wolf->map_size.x = (int)tmp;
	}
	if (map_is_incoherent(map))
		return (0);
	return (len);
}
