/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/04/11 19:29:20 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int					eventk_map_creator(int keyhook, void *wolf)
{
	t_wolf *w;

	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		w->current_page = MAIN_MENU;
	else if (keyhook == MLX_KEY_DOWN)
		w->font_cursor.y += 32;
	else if (keyhook == MLX_KEY_RIGHT)
		w->font_cursor.x += 32;
	else if (keyhook == MLX_KEY_UP)
		w->font_cursor.y -= 32;
	else if (keyhook == MLX_KEY_LEFT)
		w->font_cursor.x -= 32;
	return (0);
}

int					eventm_map_creator(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

static void put_pixel_from_texture(t_coord pt, t_img *text, t_img *img)
{
	unsigned int pos;
	unsigned int pos_text;

	pos = (unsigned int)(pt.y * img->width) + ((unsigned int)pt.x * img->octet);
	if (pt.x > text->size.x || pt.y > text->size.y)
		return ;
	pos_text = (unsigned int)(pt.y * text->width) + ((unsigned int)pt.x * text->octet);
	if (pt.y >= WIN_H || pt.y < 0 || pt.x >= WIN_W || pt.x < 0)
		return ;
	if (pos > (unsigned)(img->width * WIN_W))
		return ;
	ft_memcpy(img->data + pos, text->data + pos_text, (size_t)img->octet);
}

static void display_font(t_img *dest, t_img *text, t_wolf *w)
{
	t_coord pt;

	pt.y = 0;
	while (pt.y < w->img_size[MAP_CREATOR].y)
	{
		pt.x = 0;
		while (pt.x < w->img_size[MAP_CREATOR].x)
		{
			put_pixel_from_texture(pt, text, dest);
			pt.x++;
		}
		pt.y++;
	}
}

static void target(int x, int y, int square, t_img *img)
{
	t_coord i;

	i.y = y;
	while (i.y < y + square)
	{
		i.x = x;
		while (i.x < x + square)
		{
			if (i.x == x || i.y == y || i.x == x + square || i.y == y + square)
				put_pixel_img(i, 0x00ff00, img);
			if (i.x == x + square-1 || i.y == y + square -1)
				put_pixel_img(i, 0x00ff00, img);
			i.x++;
		}
		i.y++;
	}
}

void	draw_map_creator(void *wolf)
{
	t_wolf *w;
	t_coord pt;

	if (!(w = (t_wolf*)wolf))
		return ;
	pt.x = w->img_size[MAP_CREATOR].x / 2;
	pt.y = w->img_size[MAP_CREATOR].y / 2;
	put_pixel_img(pt, 0x0000ff, &w->img[MAP_CREATOR]);
	display_font(&w->img[MAP_CREATOR], &w->texture[T_POLICE], w);
	if (!w->font_cursor.x && !w->font_cursor.y)
	{
		w->font_cursor.x = 55;
		w->font_cursor.y = 148;
	}
	target(w->font_cursor.x, w->font_cursor.y, 32, &w->img[MAP_CREATOR]);
	(void)wolf;
}








