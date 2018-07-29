/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 18:57:47 by banthony          #+#    #+#             */
/*   Updated: 2018/07/29 19:51:44 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define CUSTOM_MAP_NAME "./custom_map_0.txt"
#define MAP_CREA_MAX_MAP '9' + 1

void		save_map_into_file(t_wolf *w)
{
	char	*tmp;
	char	*path;
	char	c;
	int		fd;

	c = '0' - 1;
	path = ft_strdup(CUSTOM_MAP_NAME);
	while ((fd = open(path, O_CREAT | O_WRONLY | O_EXCL, 0700)) < 0
				&& ++c < MAP_CREA_MAX_MAP)
	{
		if ((tmp = ft_strrchr(path, '_')) && ft_strlen(tmp) > 1)
			ft_strncpy(tmp + 1, &c, 1);
	}
	ft_putendl(path);
	ft_strdel(&path);
	if (fd < 0)
	{
		perror(strerror(errno));
		return ;
	}
	c = -1;
	while ((int)++c < w->map_crea.m_size.y)
		ft_putendl_fd(w->map_crea.map[(int)c], fd);
}

void		wolf_exit(char *str, int status, t_wolf *wolf)
{
	if (wolf && wolf->map)
		ft_freetab(wolf->map);
	ft_exit(str, status);
}

/*
**	Charge dans une structure img, un fichier xpm.
*/

static int	load_img(char *path, t_img *i, t_wolf *wolf)
{
	i->endian = 0;
	i->ptr = mlx_xpm_file_to_image(wolf->mlx, path, &i->size.x, &i->size.y);
	if (!i->ptr)
	{
		ft_putstr("Texture ");
		ft_putstr(path);
		ft_putstr(" : NOT LOADED !!\n");
		return (1);
	}
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->width, &i->endian);
	i->octet = (unsigned int)(i->bpp / 8);
	i->max_size = i->octet * (unsigned int)(i->size.x * i->size.y);
	ft_putstr("Texture ");
	ft_putstr(path);
	ft_putstr(" : LOADED - size in px: ");
	ft_putnbr(i->size.x);
	ft_putstr(" x ");
	ft_putnbrendl(i->size.y);
	return (0);
}

int			load_texture(t_wolf *w)
{
	int error;

	error = 0;
	error = load_img("./texture/doom_font.xpm", &w->texture[T_FONT], w);
	error = load_img("./texture/main_menu.xpm", &w->texture[T_MAIN_MENU], w);
	error = load_img("./texture/stone.xpm", &w->texture[T_STONE], w);
	error = load_img("./texture/wood.xpm", &w->texture[T_WOOD], w);
	error = load_img("./texture/metal.xpm", &w->texture[T_METAL], w);
	error = load_img("./texture/door.xpm", &w->texture[T_DOOR], w);
	error = load_img("./texture/interface_creator.xpm",
						&w->texture[T_CREATOR_INTERFACE], w);
	error = load_img("./texture/map_creator.xpm",
						&w->texture[T_MAP_CREATOR], w);
	error = load_img("./texture/eraser_icon.xpm", &w->texture[T_ERASER], w);
	if (error)
		wolf_exit(ERR_TEXTURE, -1, w);
	return (0);
}

/*
**	FONCTION TEMPORAIRE
**	Trace un repere pour mieux visualiser le centre de la fenetre
*/

void		draw_landmark(t_img *img)
{
	t_coord pt;

	pt.y = 0;
	while (pt.y < img->size.y)
	{
		pt.x = 0;
		while (pt.x < img->size.x)
		{
			if (pt.x == img->size.x / 2)
				put_pixel_img(pt, 0xff0000, img);
			if (pt.y == img->size.y / 2)
				put_pixel_img(pt, 0xff0000, img);
			pt.x++;
		}
		pt.y++;
	}
}
