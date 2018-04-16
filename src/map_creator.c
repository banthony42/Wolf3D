/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:58:11 by banthony          #+#    #+#             */
/*   Updated: 2018/04/16 16:41:07 by banthony         ###   ########.fr       */
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
		;
	else if (keyhook == MLX_KEY_RIGHT)
		;
	else if (keyhook == MLX_KEY_UP)
		;
	else if (keyhook == MLX_KEY_LEFT)
		;
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
	ft_bzero(&pt, sizeof(pt));
	pt.x = 660;
	pt.y = 490;
	string_to_img(".,16l!':;]ij6|[", pt, &w->img[MAP_CREATOR], w);

}

// ** CODE TEMPORAIRE
/*
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
*/
// ** FIN CODE TEMPORAIRE
