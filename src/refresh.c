/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:33:23 by banthony          #+#    #+#             */
/*   Updated: 2018/04/17 18:42:57 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void img_size(t_wolf *wolf)
{
	t_coord size;

	size.x = WIN_W;
	size.y = WIN_H;
	new_img(wolf, MAIN_MENU, size);
	new_img(wolf, MAP_CREATOR, size);
	size.x = SCREEN_W;
	size.y = SCREEN_H;
	new_img(wolf, GAME, size);
	size.x = INTRF_W;
	size.y = INTRF_H;
	new_img(wolf, GAME_I, size);
	size.x = MAPI_W;
	size.y = MAPI_H;
	new_img(wolf, MAP_I, size);
}

void init(t_wolf *wolf)
{
	wolf->mlx = mlx_init();
	wolf->win = mlx_new_window(wolf->mlx, WIN_W, WIN_H, WIN_NAME);
	wolf->draw[MAIN_MENU] = draw_main_menu;		/* Draw l'interface du menu */
	wolf->draw[GAME] = draw_game;				/* Draw l'interface de jeu puis appel le moteur du jeu	*/
	wolf->draw[GAME_END] = draw_game_end;		/* Draw l'ecran de fin de jeu */
	wolf->draw[MAP_CREATOR] = draw_map_creator;	/* Draw l'interface de creation, appel le createur de map  */
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

int	new_img(t_wolf *wolf, t_page page, t_coord size)
{
	ft_memset((void*)&wolf->img[page], 0, sizeof(t_img));
	wolf->img[page].size = size;
	wolf->img[page].ptr = mlx_new_image(wolf->mlx, size.x, size.y);
	if (!wolf->img[page].ptr)
		wolf_exit(ERR_IMG, -1, wolf);
	wolf->img[page].width = size.x;
	wolf->img[page].data = mlx_get_data_addr(wolf->img[page].ptr, &wolf->img[page].bpp,
										 &wolf->img[page].width, &wolf->img[page].endian);
	wolf->img[page].octet = (unsigned int)(wolf->img[page].bpp / 8);
	return (1);
}

/*
**	Contrairement aux event, pour l'instant il n'y a qu'une fonction
**	pour le refresh et l'expose, pour chaque page.
**	Si les if deviennent trop nombreux, un tableau de fonction sera utilise.
*/
void expose(t_wolf *wolf)
{
	t_coord pt;

	wolf->draw[wolf->current_page](wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img[wolf->current_page].ptr, 0, 0);
	if (wolf->current_page == GAME)
	{
		/*Gestion de l'overlay affichage de la map*/
		if (wolf->keypress[KEY_M])
		{
			pt.x = (SCREEN_W - MAPI_W) / 2;
			pt.y = (SCREEN_H - MAPI_H) / 2;
			mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img[MAP_I].ptr, pt.x, pt.y);
		}
		mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img[GAME_I].ptr, 0, wolf->img[GAME].size.y);
	}
}

int refresh(void *wptr)
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
		/*La page game contient plusieurs images*/
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
