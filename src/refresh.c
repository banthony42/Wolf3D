/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:33:23 by banthony          #+#    #+#             */
/*   Updated: 2018/04/11 17:44:25 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

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

	wolf->img_size[MAIN_MENU].x = WIN_W;
	wolf->img_size[MAIN_MENU].y = WIN_H;
	wolf->img_size[MAP_CREATOR].x = WIN_W;
	wolf->img_size[MAP_CREATOR].y = WIN_H;

	wolf->current_page = MAIN_MENU;
	if (!(new_img(wolf, MAIN_MENU)))
		return ;
	if (!(new_img(wolf, MAP_CREATOR)))
		return ;

	if (!(load_texture(wolf)))
		return ;
}

int	new_img(t_wolf *wolf, t_page page)
{
	ft_memset((void*)&wolf->img[page], 0, sizeof(t_img));
	wolf->img[page].ptr = mlx_new_image(wolf->mlx, wolf->img_size[page].x, wolf->img_size[page].y);
	if (!wolf->img[page].ptr)
	{
		ft_putendl("Error: mlx_new_image");
		return (0);
	}
	wolf->img[page].width = wolf->img_size[page].x;
	wolf->img[page].data = mlx_get_data_addr(wolf->img[page].ptr, &wolf->img[page].bpp,
										 &wolf->img[page].width, &wolf->img[page].endian);
	wolf->img[page].octet = (unsigned int)(wolf->img[page].bpp / 8);
	return (1);
}

void expose(t_wolf *wolf)
{
	wolf->draw[wolf->current_page](wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img[wolf->current_page].ptr, 0, 0);
}

int refresh(void *wptr)
{
	t_wolf *wolf;

	wolf = NULL;
	if (!wptr)
		return (0);
	wolf = (t_wolf*)wptr;
	mlx_destroy_image(wolf->mlx, wolf->img[wolf->current_page].ptr);
	if (!(new_img(wolf, wolf->current_page)))
		return (0);
	expose(wolf);
	return (1);
}














