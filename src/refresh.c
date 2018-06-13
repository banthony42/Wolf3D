/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:33:23 by banthony          #+#    #+#             */
/*   Updated: 2018/06/13 17:51:12 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	img_size(t_wolf *wolf)
{
	t_coord size;

	size.x = WIN_W;
	size.y = WIN_H;
	new_img(wolf, MAIN_MENU, size);
	size.x = SCREEN_W;
	size.y = SCREEN_H;
	new_img(wolf, GAME, size);
	new_img(wolf, MAP_CREATOR, size);
	size.x = INTRF_W;
	size.y = INTRF_H;
	new_img(wolf, GAME_I, size);
	size.x = MAPI_W;
	size.y = MAPI_H;
	new_img(wolf, MAP_I, size);
}

void		init(t_wolf *wolf)
{
	wolf->mlx = mlx_init();
	wolf->win = mlx_new_window(wolf->mlx, WIN_W, WIN_H, WIN_NAME);
	wolf->draw[MAIN_MENU] = draw_main_menu;
	wolf->draw[GAME] = draw_game;
	wolf->draw[GAME_END] = draw_game_end;
	wolf->draw[MAP_CREATOR] = draw_map_creator;
	wolf->event_key[MAIN_MENU] = eventk_menu;
	wolf->event_key[GAME] = eventk_game;
	wolf->event_key[GAME_END] = eventk_game_end;
	wolf->event_key[MAP_CREATOR] = eventk_map_creator;
	wolf->event_mouse[MAIN_MENU] = eventm_menu;
	wolf->event_mouse[GAME] = eventm_game;
	wolf->event_mouse[GAME_END] = eventm_game_end;
	wolf->event_mouse[MAP_CREATOR] = eventm_map_creator;
	wolf->current_page = MAIN_MENU;
	wolf->cursor = 1;
	img_size(wolf);
	if (!(load_texture(wolf)))
		return ;
}

int			new_img(t_wolf *w, t_page page, t_coord size)
{
	ft_memset((void*)&w->img[page], 0, sizeof(t_img));
	w->img[page].size = size;
	w->img[page].ptr = mlx_new_image(w->mlx, size.x, size.y);
	if (!w->img[page].ptr)
		wolf_exit(ERR_IMG, -1, w);
	w->img[page].width = size.x;
	w->img[page].data = mlx_get_data_addr(w->img[page].ptr, &w->img[page].bpp,
									&w->img[page].width, &w->img[page].endian);
	w->img[page].octet = (unsigned int)(w->img[page].bpp / 8);
	return (1);
}

/*
**	Contrairement aux event, pour l'instant il n'y a qu'une fonction
**	pour le refresh et l'expose, pour chaque page.
**	Si les if deviennent trop nombreux, un tableau de fonction sera utilise.
**	La page GAME a besoin de la gestion de l'overlay de la map.
*/

void		expose(t_wolf *w)
{
	t_coord pt;

	w->draw[w->current_page](w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[w->current_page].ptr, 0, 0);
	if (w->current_page == GAME)
	{
		if (w->keypress[KEY_TAB])
		{
			pt.x = (SCREEN_W - MAPI_W) / 2;
			pt.y = (SCREEN_H - MAPI_H) / 2;
			mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_I].ptr
									, pt.x, pt.y);
		}
		mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, 0,
								w->img[GAME].size.y);
	}
	else if (w->current_page == MAP_CREATOR)
	{
		pt.x = (SCREEN_W - MAPI_W) / 2;
		pt.y = (SCREEN_H - MAPI_H) / 2;
		mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_I].ptr
									, pt.x, pt.y);
		mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, 0,
								w->img[GAME].size.y);
	}
}

/*
**	La page GAME contient deux images.
*/

int			refresh(void *wptr)
{
	t_coord	size;
	t_wolf	*wolf;

	wolf = NULL;
	if (!(wolf = (t_wolf*)wptr))
		return (0);
	size = wolf->img[wolf->current_page].size;
	mlx_destroy_image(wolf->mlx, wolf->img[wolf->current_page].ptr);
	new_img(wolf, wolf->current_page, size);
	if (wolf->current_page == GAME)
	{
		size = wolf->img[GAME_I].size;
		mlx_destroy_image(wolf->mlx, wolf->img[GAME_I].ptr);
		new_img(wolf, GAME_I, size);
		size = wolf->img[MAP_I].size;
		mlx_destroy_image(wolf->mlx, wolf->img[MAP_I].ptr);
		new_img(wolf, MAP_I, size);
	}
	else if (wolf->current_page == MAP_CREATOR)	// Voir si necessaire pour le map creator
	{
		size = wolf->img[GAME_I].size;
		mlx_destroy_image(wolf->mlx, wolf->img[GAME_I].ptr);
		new_img(wolf, GAME_I, size);
		size = wolf->img[MAP_I].size;
		mlx_destroy_image(wolf->mlx, wolf->img[MAP_I].ptr);
		new_img(wolf, MAP_I, size);
	}
	expose(wolf);
	return (1);
}










