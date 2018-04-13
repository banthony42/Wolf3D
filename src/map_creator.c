/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/04/13 20:27:46 by banthony         ###   ########.fr       */
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
static void put_pixel_from_texture(t_coord pti, t_coord ptt, t_img *text, t_img *img)
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

#define NB_C 18
#define GET_Y(c) ((c - ' ') / NB_C)
#define GET_X(c) ((c - ' ') % NB_C)
#define	GET_POS_X(c) (34 + (32 * GET_X(c)) )	//premier pixel en x de la case
#define GET_POS_Y(c) (34 + (48 * GET_Y(c)) )	//premier pixel en y de la case
#define BOX_X 30
#define BOX_Y 46

/*
**	Le caractere '6' est manquant dans la texture doom_font.xpm
**	Nous devons donc utiliser le '9', auquel on applique une rotation de 180deg.
**	Il est necessaire d'appliquer une constante de repositionnement,
**	afin que le caractere soit centre dans un mot.
*/
static void	handle_six(t_coord pt, t_img *img, t_wolf *wolf)
{
	t_coord			i;
	t_coord			calc;
	t_coord			pt_t;
	int				constante;

	constante = 5;
	i.y = -1;
	while (++i.y < BOX_Y)
	{
		i.x = -1;
		while (++i.x < BOX_X - constante)
		{
			calc.x = ((-1 * i.x)) + (pt.x + (BOX_X - constante));
			calc.y = (-1 * (i.y - constante)) + (pt.y + (BOX_Y) / 2);
			pt_t.x = i.x + GET_POS_X('9' - 1);
			pt_t.y = i.y + GET_POS_Y('9' - 1);
			put_pixel_from_texture(calc, pt_t, &wolf->texture[T_POLICE], img);
		}
	}
}

static char handle_exceptions(char c, t_coord *var, t_coord *pt_t)
{
	if (c == '6')
		return ('6');
	if (c > '6')
		var->y = 1;
	pt_t->x = GET_POS_X(c - var->y);
	pt_t->y = GET_POS_Y(c - var->y);
	if (c == 'l')
		var->x = 14;
	if (c == 'm')
	{
		var->x += 16;
		pt_t->x -= 16;
	}
	return (0);
}

static void	char_to_img(char c, t_coord pt, t_img *img, t_wolf *wolf)
{
	unsigned int	pos;
	unsigned int	text_pos;
	t_coord			pt_t;
	t_coord			var;

	var.y = 0;
	var.x = BOX_X;
	if (!c || c <= 32 || pt.x + BOX_X > WIN_W || pt.y + BOX_Y > WIN_H || pt.x < 0 || pt.y < 0)
		return ;
	if ((handle_exceptions(c, &var, &pt_t)) == '6')
		handle_six(pt, img, wolf);
	var.y = -1;
	while (++var.y < BOX_Y && c != '6')
	{
		pos = (unsigned int)((var.y + pt.y) * img->width)
				+ ((unsigned int)pt.x * img->octet);
		text_pos = (unsigned int)((pt_t.y + var.y) * wolf->texture[T_POLICE].width)
				+ ((unsigned int)pt_t.x * wolf->texture[T_POLICE].octet);
		ft_memcpy(img->data + pos, wolf->texture[T_POLICE].data
				  + text_pos, (size_t)((img->octet) * (unsigned int)(var.x)));
	}
}

static void string_to_img(char *str, t_coord pt, t_img *img, t_wolf *wolf)
{
	char *tiny_char;
	int i;

	tiny_char = ".,1l!':;]Iij|[";
	i = -1;
	if (!str)
		return;
	while (str[++i])
	{
		char_to_img(str[i], pt, img, wolf);
		if (ft_strchr(tiny_char, str[i]))
			pt.x -= 15;
		pt.x += BOX_X;
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
			put_pixel_from_texture(pt, pt, text, dest);
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
	ft_bzero(&pt, sizeof(pt));
	while (pt.y < WIN_H)
	{
		pt.x = -1;
		while (++pt.x < WIN_W)
			put_pixel_img(pt, 0x000000, &w->img[MAP_CREATOR]);
		pt.y++;
	}
	display_font(&w->img[MAP_CREATOR], &w->texture[T_POLICE], w);
	if (!w->font_cursor.x && !w->font_cursor.y)
	{
		w->font_cursor.x = 34;
		w->font_cursor.y = 34;
	}
	if (!w->cursor)
		w->cursor = (int)' ';
	target(w->font_cursor.x, w->font_cursor.y, rectgl, &w->img[MAP_CREATOR]);

	test.x = 10;
	test.y = 450;
	char_to_img((char)w->cursor, test, &w->img[MAP_CREATOR], w);
	test.y += 48;
	string_to_img(".,16l!':;]ij6|[", test, &w->img[MAP_CREATOR], w);

	(void)wolf;
}
