/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:33:23 by banthony          #+#    #+#             */
/*   Updated: 2018/08/09 18:39:16 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Initialisation des variables constantes utile au raycast
*/
static void init_raycast(t_wolf *w)
{
	double raydir[WIN_W];
	double incr;
	int		i;

	i = -1;
	incr = (double)FOV / (double)WIN_W;
	while (++i < WIN_W)
		raydir[i] = i * incr;
	w->player = (t_player) {{WIN_W / 2, WIN_H/2, 90}, {0}, 8 * 64, FOV, FOV / 2, 400, 200};
	ft_memcpy(&w->player.ray_dir, &raydir, sizeof(raydir));
}

static void	init_img(t_wolf *w)
{
	new_img(w, MAIN_MENU, (t_coord){WIN_W, WIN_H, CLR});
	new_img(w, GAME, (t_coord){WIN_W, WIN_H, CLR});
	new_img(w, MAP_CREATOR, (t_coord){MAP_CRT_W, MAP_CRT_H, CLR});
	new_img(w, GAME_I, (t_coord){INTRF_W, INTRF_H, CLR});
	new_img(w, MAP_I, (t_coord){MAPI_W, MAPI_H, CLR});
	w->map_crea.m_size.x = w->img[MAP_I].size.x / ITEM_SIZE;
	w->map_crea.m_size.y = w->img[MAP_I].size.y / ITEM_SIZE;
	w->map_crea.map = ft_newtab(w->map_crea.m_size.y,
									w->map_crea.m_size.x, (int)'0');
	w->map_crea.texture = T_NULL;
	init_raycast(w);
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
	init_time_struct(&wolf->time);
	wolf->cursor = 1;
	init_img(wolf);
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
	w->img[page].data_size = w->img[page].octet * (unsigned int)size.x * (unsigned int)size.y;
	return (1);
}

/*
**	Contrairement aux event et draw, pour l'instant il n'y a qu'une fonction
**	pour le refresh et l'expose, pour chaque page.
**	Si les if deviennent trop nombreux, un tableau de fonction sera utilise.
**	Les pages GAME et MAP_CREATOR ont besoin respectivement de la gestion
**	de la map et map + interface.
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
			pt = (t_coord){(WIN_W - MAPI_W) / 2, (WIN_H - MAPI_H) / 2, CLR};
			mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_I].ptr
									, pt.x, pt.y);
		}
	}
	else if (w->current_page == MAP_CREATOR)
	{
		pt = (t_coord){(MAP_CRT_W - MAPI_W) / 2, (MAP_CRT_H - MAPI_H) / 2, CLR};
		mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_I].ptr
									, pt.x, pt.y);
		mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, 0,
								w->img[MAP_CREATOR].size.y);
	}
}

static void img_clear(t_wolf *w, t_page page)
{
	t_coord size;

	size = w->img[page].size;
	mlx_destroy_image(w->mlx, w->img[page].ptr);
	new_img(w, page, size);
/*
**	Bizarrement la ligne ci dessous est plus couteuse en fps
**	ft_memset(w->img[page].data, 0, w->img[page].data_size);
*/
}

/*
**	La page GAME et MAP_CREATOR contiennent deux images.
*/

int			refresh(void *wptr)
{
	t_wolf	*wolf;

	wolf = NULL;
	if (!(wolf = (t_wolf*)wptr))
		return (0);
	wolf->time.update(&wolf->time);
	wolf->time.print(&wolf->time);
	img_clear(wolf, wolf->current_page);
	if (wolf->current_page == MAP_CREATOR)
	{
		img_clear(wolf, MAP_I);
		img_clear(wolf, GAME_I);
	}
	if (wolf->current_page == GAME)
		img_clear(wolf, MAP_I);
	expose(wolf);
	return (1);
}
