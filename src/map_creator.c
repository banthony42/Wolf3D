/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/04/17 16:39:29 by banthony         ###   ########.fr       */
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
		(void)wolf;
	else if (keyhook == MLX_KEY_RIGHT)
		(void)wolf;
	else if (keyhook == MLX_KEY_UP)
		(void)wolf;
	else if (keyhook == MLX_KEY_LEFT)
		(void)wolf;
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

void	draw_map_creator(void *wolf)
{
	t_wolf *w;
	t_coord pt;

	if (!(w = (t_wolf*)wolf))
		return ;
	fill_img(&w->img[MAP_CREATOR], 0x311111);
	fill_img(&w->img[GAME_I], 0x2f2f2f);
	draw_grid(&w->img[MAP_CREATOR]);
	draw_grid(&w->img[GAME_I]);
	mlx_put_image_to_window(w->mlx, w->win, w->img[MAP_CREATOR].ptr, 0, 0);
	pt.x = 100;
	pt.y = 100;
	string_to_img("Map creator  Work in progress ...", pt, &w->img[GAME], w);

	pt.x = 0;
	pt.y = w->img[GAME].size.y;
	mlx_put_image_to_window(w->mlx, w->win, w->img[GAME_I].ptr, pt.x, pt.y);

	pt.x = 16;
	pt.y = 32;
	string_to_img("Interface Work in progress ...", pt, &w->img[GAME_I], w);
}

// ** CODE TEMPORAIRE
/*


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
*/
// ** FIN CODE TEMPORAIRE
