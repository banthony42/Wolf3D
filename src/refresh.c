/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:33:23 by banthony          #+#    #+#             */
/*   Updated: 2018/03/29 23:50:22 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void init(t_wolf *wolf)
{
	int width;

	width = WIN_W;
	wolf->mlx = mlx_init();
	wolf->win = mlx_new_window(wolf->mlx, WIN_W, WIN_H, WIN_NAME);
	wolf->img = mlx_new_image(wolf->mlx, WIN_W, WIN_H);
	wolf->img_d = mlx_get_data_addr(wolf->img, &wolf->img_bpp, &width, &wolf->img_endian);
	wolf->img_dsize = (SCREEN_W * SCREEN_H) * (wolf->img_bpp / 8);
}
