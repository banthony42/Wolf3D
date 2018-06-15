/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:11:01 by banthony          #+#    #+#             */
/*   Updated: 2018/06/15 13:54:24 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Remplit le pixel de coordonees pt, et de l'image *img, avec color.
*/

void		put_pixel_img(t_coord pt, int color, t_img *img)
{
	unsigned int pos;

	pos = (unsigned int)(pt.y * img->width) + ((unsigned int)pt.x * img->octet);
	if (pt.y >= WIN_H || pt.y < 0 || pt.x >= WIN_W || pt.x < 0)
		return ;
	if (pos > (unsigned)(img->width * WIN_W))
		return ;
	ft_memcpy(img->data + pos, &color, (unsigned)img->octet);
}

/*
**	Remplit le pixel pti de l'img avec le pixel ptt de la texture text.
*/

void		put_pixel_from_txt(t_coord pti, t_coord ptt, t_img *txt, t_img *img)
{
	unsigned int pos;
	unsigned int pos_txt;

	if (ptt.x > txt->size.x || ptt.y > txt->size.y || ptt.x < 0 || ptt.y < 0)
		return ;
	if (pti.y >= WIN_H || pti.y < 0 || pti.x >= WIN_W || pti.x < 0)
		return ;
	pos = (unsigned int)(pti.y * img->width)
			+ ((unsigned int)pti.x * img->octet);
	pos_txt = (unsigned int)(ptt.y * txt->width)
			+ ((unsigned int)ptt.x * txt->octet);
	if (pos > (unsigned)(img->width * WIN_W))
		return ;
	ft_memcpy(img->data + pos, txt->data + pos_txt, (size_t)img->octet);
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
	error = load_img("./texture/interface_creator.xpm", &w->texture[T_CREATOR_INTERFACE], w);
	error = load_img("./texture/map_creator.xpm", &w->texture[T_MAP_CREATOR], w);
	error = load_img("./texture/eraser_icon.xpm", &w->texture[T_ERASER], w);
	if (error)
		wolf_exit(ERR_TEXTURE, -1, w);
	return (0);
}

void		put_texture_on_img_at(t_img *dest, t_img *text, t_coord at, t_coord text_size)
{
	t_coord pt;
	t_coord ptt;
	t_coord pt_max;

	pt_max.x = at.x + text_size.x;
	pt_max.y = at.y + text_size.y;
	pt.y = at.y;
	if (!dest || !text)
		return ;
	while (pt.y < pt_max.y)
	{
		pt.x = at.x;
		while (pt.x < pt_max.x)
		{
			ptt.x = (text->size.x * (pt.x - at.x)) / text_size.x;
			ptt.y = (text->size.y * (pt.y - at.y)) / text_size.y;
			put_pixel_from_txt(pt, ptt, text, dest);
			pt.x++;
		}
		pt.y++;
	}
}

void		put_texture_on_img(t_img *dest, t_img *text)
{
	t_coord pt;
	t_coord ptt;

	pt.y = 0;
	if (!dest || !text)
		return ;
	while (pt.y < dest->size.y)
	{
		pt.x = 0;
		while (pt.x < dest->size.x)
		{
			ptt.x = (text->size.x * pt.x) / dest->size.x;
			ptt.y = (text->size.y * pt.y) / dest->size.y;
			put_pixel_from_txt(pt, ptt, text, dest);
			pt.x++;
		}
		pt.y++;
	}
}

/*
**	FONCTION TEMPORAIRE
**	Remplit l'image avec la couleur en parametre
*/

void		fill_img(t_img *img, int color)
{
	t_coord pt;

	pt.y = 0;
	while (pt.y < img->size.y)
	{
		pt.x = 0;
		while (pt.x < img->size.x)
		{
			put_pixel_img(pt, color, img);
			pt.x++;
		}
		pt.y++;
	}
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

void draw_box(t_coord size, t_coord start, int offset, t_img *img)
{
	t_coord i;
	t_coord max;

	start.x += offset;
	start.y += offset;
	i.x = start.x;
	i.y = start.y;
	max.x = start.x + size.x;
	max.y = start.y + size.y;
	while (i.y < max.y)
	{
		i.x = start.x;
		while (i.x < max.x)
		{
			if (i.x == start.x || i.y == start.y
				|| i.x == max.x - 1 || i.y == max.y - 1)
				put_pixel_img(i, size.color, img);
			i.x++;
		}
		i.y++;
	}
}
