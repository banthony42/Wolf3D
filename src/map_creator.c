/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/06/15 15:44:23 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define TITLE "MAP CREATOR"
#define INFO "Draw your map"
#define SAVE "save"
#define TEXT 5
#define TEXT_P 16
#define TEXT_SIZE 48

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

int			eventm_map_creator(int button, int x, int y, void *wolf)
{
	t_wolf	*w;
	t_coord pt;
	t_coord start;
	t_coord rest;
	t_coord text_size;

	if (!(w = (t_wolf*)wolf))
		return (0);

	/* Borne de MAP_I sur la WIN
	  MAP_I x = [ start.x , start.x + MAPI_W]
	  MAP_I y = [ start.y , start.y + MAPI_H]
	*/
	text_size.x = TEXT_SIZE;
	text_size.y = TEXT_SIZE;
	rest.x = (w->img[MAP_I].size.x % text_size.x) / 2;
	rest.y = (w->img[MAP_I].size.y % text_size.y) / 2;
	start.x = ((SCREEN_W - MAPI_W) / 2) + rest.x;
	start.y = ((SCREEN_H - MAPI_H) / 2) + rest.y;
	pt.x = (((x - start.x) / text_size.x) * text_size.x) + rest.x;
	pt.y = (((y - start.y) / text_size.y) * text_size.y) + rest.y;
	put_texture_on_img_at(&w->img[MAP_I], &w->texture[T_STONE], pt, text_size);
	ft_putendl("test");
	(void)button;
	return (0);
}

static void	draw_grid(t_wolf *w, t_page page)
{
	t_coord pt;
	t_coord	box_size;
	t_coord rest;

	box_size.x = TEXT_SIZE ;
	box_size.y = TEXT_SIZE ;
	box_size.color = 0x2f2f2f;

	rest.x = (w->img[page].size.x % box_size.x) / 2;
	rest.y = (w->img[page].size.y % box_size.y) / 2;
	pt.x = rest.x;
	pt.y = rest.y;
	while (pt.y < w->img[page].size.y - rest.y)
	{
		pt.x = rest.x;
		while (pt.x < w->img[page].size.x - rest.x)
		{
			draw_box(box_size, pt, 0, &w->img[page]);
			pt.x += box_size.x;
		}
		pt.y += box_size.y;
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
	t_coord text_size;
	t_coord	pt;
	t_coord	box_size;
	int		i;

	i = 0;
	box_size.x = TEXT_SIZE + 2;
	box_size.y = TEXT_SIZE + 2;
	text_size.x = TEXT_SIZE;
	text_size.y = TEXT_SIZE;
	put_interface_text(w);
	box_size.color = 0xd4af37;
	pt.y = PERCENTAGE(50, w->img[GAME_I].size.y);
	pt.x = (PERCENTAGE(50, w->img[GAME_I].size.x));
	pt.x -= ((TEXT / 2) * (box_size.x + TEXT_P));
	while (i < TEXT)
	{
		draw_box(box_size, pt, -1, &w->img[GAME_I]);
		put_texture_on_img_at(&w->img[GAME_I], &w->texture[T_STONE + i], pt, text_size);
		pt.x += box_size.x + TEXT_P;
		i++;
	}
	box_size.x = (int)(ft_strlen(SAVE) * 32);
	pt.x = PERCENTAGE(80, w->img[GAME_I].size.x);
	draw_box(box_size, pt, 0, &w->img[GAME_I]);
	pt.x += (box_size.x / 2) + 7;
	pt.y += 2;
	string_to_img(SAVE, centerx_str(SAVE, pt), &w->img[GAME_I], w);
}

void		draw_map_creator(void *wolf)
{
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
//	fill_img(&w->img[MAP_I], 0x2f2f2f);
	put_texture_on_img(&w->img[MAP_CREATOR], &w->texture[T_MAP_CREATOR]);
	put_texture_on_img(&w->img[GAME_I], &w->texture[T_CREATOR_INTERFACE]);
	mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_CREATOR].ptr, 0, 0);
	mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_I].ptr,
							(SCREEN_W - MAPI_W) / 2, (SCREEN_H - MAPI_H) / 2);
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, 0,
							w->img[GAME].size.y);
	draw_interface(w);
	draw_grid(w, MAP_I);
}
