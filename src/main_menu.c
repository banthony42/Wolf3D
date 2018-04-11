/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:40:31 by banthony          #+#    #+#             */
/*   Updated: 2018/04/11 19:06:54 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int					eventk_menu(int keyhook, void *wolf)
{
	t_wolf *w;

	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		ft_exit("End menu", 0);
	else if (keyhook == MLX_KEY_M)
		w->current_page = MAP_CREATOR;
	(void)wolf;
	return (0);
}

int					eventm_menu(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

void	draw_main_menu(void *wolf)
{
	t_coord pt;
	t_wolf *w;

	w = (t_wolf*)wolf;
	pt.x = w->img_size[MAIN_MENU].x / 2;
	pt.y = w->img_size[MAIN_MENU].y / 2;
	put_pixel_img(pt, 0xff0000, &w->img[MAIN_MENU]);
	(void)wolf;
}
