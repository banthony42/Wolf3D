/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:11:01 by banthony          #+#    #+#             */
/*   Updated: 2018/04/16 18:21:31 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Remplit le pixel de coordonees pt, et de l'image *img, avec color.
*/
void	put_pixel_img(t_coord pt, int color, t_img *img)
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
void put_pixel_from_texture(t_coord pti, t_coord ptt, t_img *text, t_img *img)
{
	unsigned int pos;
	unsigned int pos_text;

	if (ptt.x > text->size.x || ptt.y > text->size.y || ptt.x < 0 || ptt.y < 0)
		return ;
	if (pti.y >= WIN_H || pti.y < 0 || pti.x >= WIN_W || pti.x < 0)
		return ;
	pos = (unsigned int)(pti.y * img->width) + ((unsigned int)pti.x * img->octet);
	pos_text = (unsigned int)(ptt.y * text->width) + ((unsigned int)ptt.x * text->octet);
	if (pos > (unsigned)(img->width * WIN_W))
		return ;
	ft_memcpy(img->data + pos, text->data + pos_text, (size_t)img->octet);
}

/*
**	Charge dans une structure img, un fichier xpm.
*/
static int load_img(char *path, t_img *i, t_wolf *wolf)
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

int load_texture(t_wolf *wolf)
{
	int error;

	error = 0;
	error = load_img("./texture/doom_font.xpm", &wolf->texture[T_FONT], wolf);
	error = load_img("./texture/main_menu.xpm", &wolf->texture[T_MAIN_MENU], wolf);
	if (error)
		ft_exit("Error while loading texture", 0);
	return (0);
}

void put_texture_on_img(t_img *dest, t_img *text, t_wolf *w)
{
	t_coord pt;
	t_coord ptt;

	pt.y = 0;
	if (!dest || !text || !w)
		return ;
	while (pt.y < dest->size.y)
	{
		pt.x = 0;
		while (pt.x < dest->size.x)
		{
			ptt.x = (text->size.x * pt.x) / dest->size.x;
			ptt.y = (text->size.y * pt.y) / dest->size.y;
			put_pixel_from_texture(pt, ptt, text, dest);
			pt.x++;
		}
		pt.y++;
	}
}

/* FONCTION TEMPORAIRE*/

/*
**	Trace deux ligne pour mieux visualiser le centre de la fenetre
*/
void draw_grid(t_wolf *w)
{
	t_coord pt;

	pt.y = 0;
	while (pt.y < w->img[w->current_page].size.y)
	{
		pt.x = 0;
		while (pt.x < w->img[w->current_page].size.x)
		{
			if (pt.x == w->img[w->current_page].size.x / 2)
				put_pixel_img(pt, 0xff0000, &w->img[w->current_page]);
			if (pt.y == w->img[w->current_page].size.y / 2)
				put_pixel_img(pt, 0xff0000, &w->img[w->current_page]);
			pt.x++;
		}
		pt.y++;
	}
}
