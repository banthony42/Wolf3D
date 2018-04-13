/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/04/13 14:49:57 by banthony         ###   ########.fr       */
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
	{
		w->font_cursor.y += 48;
		w->cursor += 18;
	}
	else if (keyhook == MLX_KEY_RIGHT)
	{
		w->font_cursor.x += 32;
		w->cursor++;
	}
	else if (keyhook == MLX_KEY_UP)
	{
		w->font_cursor.y -= 48;
		w->cursor -= 18;
	}
	else if (keyhook == MLX_KEY_LEFT)
	{
		w->font_cursor.x -= 32;
		w->cursor--;
	}
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

// ** CODE TEMPORAIRE
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

#define GET_Y(c) ((c - ' ') / 18)
#define GET_X(c) ((c - ' ') % 18)
#define	GET_POS_X(c) (34 + (32 * GET_X(c)) )	//premier pixel en x de la case
#define GET_POS_Y(c) (34 + (48 * GET_Y(c)) )	//premier pixel en y de la case
#define BOX_X 30
#define BOX_Y 46

static void	char_to_img(char c, t_coord pt, t_img *img, t_wolf *wolf)
{
	unsigned int pos;
	unsigned int text_pos;
	t_coord pt_text;
	t_coord i;

	i.y = pt.y;
	i.x = pt.x;
	if (!c)
		return ;
	pt_text.x = GET_POS_X(c);
	pt_text.y = GET_POS_Y(c);
	while (i.y < pt.y + BOX_Y)
	{
		pos = (unsigned int)(i.y * img->width) + ((unsigned int)i.x * img->octet);
		text_pos = (unsigned int)(pt_text.y * wolf->texture[T_POLICE].width) + ((unsigned int)pt_text.x * wolf->texture[T_POLICE].octet);
		ft_memcpy(img->data + pos, wolf->texture[T_POLICE].data + text_pos, (size_t)((img->octet) * BOX_X));
		i.y++;
		pt_text.y++;
	}
}

static void display_font(t_img *dest, t_img *text, t_wolf *w)
{
	t_coord pt;

	pt.y = 0;
	if (!dest || !text || !w)
		return ;
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

static void target(int x, int y, t_coord shape, t_img *img)
{
	t_coord i;

	i.y = y;
	while (i.y < y + shape.y)
	{
		i.x = x;
		while (i.x < x + shape.x)
		{
			if (i.x == x || i.y == y || i.x == x + shape.x || i.y == y + shape.y)
				put_pixel_img(i, 0x00ff00, img);
			if (i.x == x + shape.x - 1 || i.y == y + shape.y - 1)
				put_pixel_img(i, 0x00ff00, img);
			i.x++;
		}
		i.y++;
	}
}
// ** FIN CODE TEMPORAIRE

void	draw_map_creator(void *wolf)
{
	t_wolf *w;
	t_coord pt;
	t_coord test;
	t_coord rectgl;

	rectgl.x = (16 * 2);
	rectgl.y = (16 * 3);
	if (!(w = (t_wolf*)wolf))
		return ;
	pt.x = w->img_size[MAP_CREATOR].x / 2;
	pt.y = w->img_size[MAP_CREATOR].y / 2;
	put_pixel_img(pt, 0x0000ff, &w->img[MAP_CREATOR]);
	display_font(&w->img[MAP_CREATOR], &w->texture[T_POLICE], w);
	if (!w->font_cursor.x && !w->font_cursor.y)
	{
		w->font_cursor.x = 34;
		w->font_cursor.y = 34;
	}
	if (!w->cursor)
		w->cursor = (int)' ';
	target(w->font_cursor.x, w->font_cursor.y, rectgl, &w->img[MAP_CREATOR]);

	test.x = 400;
	test.y = 450;
	char_to_img((char)w->cursor, test, &w->img[MAP_CREATOR], w);

	(void)wolf;
}










