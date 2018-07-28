/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/07/28 22:29:27 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define TITLE "MAP CREATOR"
#define INFO "Draw your map"
#define SAVE "save"

/*
**	Nombre de texture dans la palette. (TEXT)
**	Ecart en pixel, (pitch) entre chaque box de texture. (TEXT_P)
*/

#define TEXT 5
#define TEXT_P 16

int			eventk_map_creator(int keyhook, void *wolf)
{
	t_wolf *w;

	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		w->current_page = MAIN_MENU;
	else if (keyhook == MLX_KEY_DOWN)
		(void)wolf;
	else if (keyhook == MLX_KEY_RIGHT)
		(void)wolf;
	else if (keyhook == MLX_KEY_UP)
		(void)wolf;
	else if (keyhook == MLX_KEY_LEFT)
		(void)wolf;
	return (0);
}

static int	palette_choice(t_wolf *w, int x, int y)
{
	int i;
	t_coord pt;

	i = 0;
	pt.y = PERCENTAGE(50, w->img[GAME_I].size.y);
	pt.x = (PERCENTAGE(50, w->img[GAME_I].size.x));
	pt.x -= ((TEXT / 2) * ((ITEM_SIZE + 2) + TEXT_P));
	y -= w->img[GAME].size.y;
	while (i < TEXT)
	{
		if (x > pt.x && x < (pt.x + ITEM_SIZE) && y > pt.y && y < (pt.y + ITEM_SIZE))
			w->map_crea.texture = (t_texture)((int)T_STONE + i);
		i++;
		pt.x += ITEM_SIZE + 2 + TEXT_P;
	}
	pt.x = PERCENTAGE(80, w->img[GAME_I].size.x);
	if (x > pt.x && x < (pt.x + (int)(ft_strlen(SAVE) * 32)) && y > pt.y && y < (pt.y + ITEM_SIZE))
		ft_putendl("save function to be called");
	return (0);
}

static void map_creator_info(t_coord pt, t_wolf *w)
{
	printf("Clic on box x:%d, y:%d\n", pt.x, pt.y); // /!\ printf
	ft_putendl("Map Creator:\n------------------");
	ft_printtab(w->map_crea.map, ft_putstr, "\n");
	ft_putendl("\n------------------");
}

int			eventm_map_creator(int button, int x, int y, void *wolf)
{
	t_wolf	*w;
	t_coord pt;
	t_coord start;
	t_coord rest;

	if (!(w = (t_wolf*)wolf) && button >= 0)
		return (0);
	if (y > w->img[GAME].size.y)
		return (palette_choice(w, x, y));	// Clic dans l'interface
	rest.x = (w->img[MAP_I].size.x % ITEM_SIZE) / 2;
	rest.y = (w->img[MAP_I].size.y % ITEM_SIZE) / 2;
	start.x = ((SCREEN_W - MAPI_W) / 2) + rest.x;
	start.y = ((SCREEN_H - MAPI_H) / 2) + rest.y;
	if (x < start.x || y < start.y || x > (start.x + MAPI_W - rest.x * 2)
		|| y > (start.y + MAPI_H - rest.y * 2))
		return (0);
	pt.x = (((x - start.x) / ITEM_SIZE));
	pt.y = (((y - start.y) / ITEM_SIZE));
	/*Attention le calcul est trop limite sur les maximum de la map*/
	/*on tape hors limite sur les derniers pixel, ca fait segfault sur le char ** map*/
	printf("writ to map[%d][%d]\n", pt.x, pt.y);
	w->map_crea.map[pt.y][pt.x] = (char)('0' + w->map_crea.texture);
	if (w->map_crea.texture == T_ERASER)
		w->map_crea.map[pt.y][pt.x] = '0';
	map_creator_info(pt, w);	// Affiche le debug du char**
	return (0);
}

static void draw_map(t_wolf *w)
{
	t_coord pt;
	t_coord i;
	t_coord rest;
	t_texture text;
	t_coord item_size;

	if (!w)
		return ;
	item_size.x = ITEM_SIZE;
	item_size.y = ITEM_SIZE;
	rest.x = (w->img[MAP_I].size.x % item_size.x) / 2;
	rest.y = (w->img[MAP_I].size.y % item_size.y) / 2;
	i.y = 0;
	while (i.y < w->map_crea.m_size.y)
	{
		i.x = 0;
		pt.y = (i.y * item_size.y) + rest.y;
		while (i.x < w->map_crea.m_size.x)
		{
			pt.x = (i.x * item_size.x) + rest.x;
			if ((text = (t_texture)(w->map_crea.map[i.y][i.x] - '0')))
				put_texture_on_img_at(&w->img[MAP_I], &w->texture[text], pt, item_size);
			i.x++;
		}
		i.y++;
	}
}

static void	draw_grid(t_wolf *w, t_page page)
{
	t_coord pt;
	t_coord	box;
	t_coord rest;

	box.x = ITEM_SIZE ;
	box.y = ITEM_SIZE ;
	box.color = 0x2f2f2f;
	rest.x = (w->img[page].size.x % box.x) / 2;
	rest.y = (w->img[page].size.y % box.y) / 2;
	pt.x = rest.x;
	pt.y = rest.y;
	while (pt.y < w->img[page].size.y - rest.y)
	{
		pt.x = rest.x;
		while (pt.x < w->img[page].size.x - rest.x)
		{
			draw_box(box, pt, 0, &w->img[page]);
			pt.x += box.x;
		}
		pt.y += box.y;
	}
}

static void	put_interface_text(t_wolf *w)
{
	t_coord pt;

	pt.x = PERCENTAGE(50, w->img[MAP_CREATOR].size.x);
	pt.y = PERCENTAGE(2, w->img[MAP_CREATOR].size.y);
	string_to_img(TITLE, centerx_str(TITLE, pt), &w->img[MAP_CREATOR], w);
	pt.x = PERCENTAGE(50, w->img[GAME_I].size.x);
	pt.y = PERCENTAGE(5, w->img[GAME_I].size.y);
	string_to_img(INFO, centerx_str(INFO, pt), &w->img[GAME_I], w);
}

static void	draw_interface(t_wolf *w)
{
	t_coord	pt;
	t_coord	box;
	t_coord item_size;
	int		i;

	i = 0;
	item_size.x = ITEM_SIZE;
	item_size.y = ITEM_SIZE;
	box.x = item_size.x + 2;
	box.y = item_size.y + 2;
	put_interface_text(w);
	pt.y = PERCENTAGE(50, w->img[GAME_I].size.y);
	pt.x = (PERCENTAGE(50, w->img[GAME_I].size.x));
	pt.x -= ((TEXT / 2) * (box.x + TEXT_P));
	while (i < TEXT)
	{
		box.color = 0xd4af37;
		if (w->map_crea.texture == i + 1)
			box.color = 0xff0000;
		draw_box(box, pt, -1, &w->img[GAME_I]);
		put_texture_on_img_at(&w->img[GAME_I], &w->texture[T_STONE + i], pt, item_size);
		pt.x += box.x + TEXT_P;
		i++;
	}
	box.color = 0xd4af37;
	box.x = (int)(ft_strlen(SAVE) * 32);
	pt.x = PERCENTAGE(80, w->img[GAME_I].size.x);
	draw_box(box, pt, 0, &w->img[GAME_I]);
	pt.x += (box.x / 2) + 7;
	pt.y += 2;
	string_to_img(SAVE, centerx_str(SAVE, pt), &w->img[GAME_I], w);
}

void		draw_map_creator(void *wolf)
{
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
	put_texture_on_img(&w->img[MAP_CREATOR], &w->texture[T_MAP_CREATOR]);
	put_texture_on_img(&w->img[GAME_I], &w->texture[T_CREATOR_INTERFACE]);
	mlx_put_image_to_window(w->mlx, w->win, w->img[w->current_page].ptr, 0, 0);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, 0,
							w->img[GAME].size.y);
	draw_interface(w);
	draw_grid(w, MAP_I);
	draw_map(w);
}
