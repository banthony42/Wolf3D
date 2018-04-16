/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:33:23 by banthony          #+#    #+#             */
/*   Updated: 2018/04/16 16:29:11 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void img_size(t_wolf *wolf)
{
	t_coord size;

	size.x = WIN_W;
	size.y = WIN_H;
	if (!(new_img(wolf, MAIN_MENU, size)))
		return ;
	if (!(new_img(wolf, MAP_CREATOR, size)))
		return ;
	size.x = SCREEN_W;
	size.y = SCREEN_H;
	if (!(new_img(wolf, GAME, size)))
		return ;
	size.x = INTRF_W;
	size.y = INTRF_H;
	if (!(new_img(wolf, GAME_I, size)))
		return ;
	size.x = MAPI_W;
	size.y = MAPI_H;
	if (!(new_img(wolf, MAP_I, size)))
		return ;
}

void init(t_wolf *wolf)
{
	int width;

	width = WIN_W;
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
	{
		ft_putendl("Error: mlx_new_image");
		return (0);
	}
	wolf->img[page].width = size.x;
	wolf->img[page].data = mlx_get_data_addr(wolf->img[page].ptr, &wolf->img[page].bpp,
										 &wolf->img[page].width, &wolf->img[page].endian);
	wolf->img[page].octet = (unsigned int)(wolf->img[page].bpp / 8);
	return (1);
}

void expose(t_wolf *wolf)
{
	wolf->draw[wolf->current_page](wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img[wolf->current_page].ptr, 0, 0);
	if (wolf->current_page == GAME)
		mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img[GAME_I].ptr, 0, wolf->img[GAME].size.y);
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
	if (!(new_img(wolf, wolf->current_page, size)))
		return (0);
	expose(wolf);
	return (1);
}
