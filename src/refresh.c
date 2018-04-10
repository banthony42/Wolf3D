/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:33:23 by banthony          #+#    #+#             */
/*   Updated: 2018/04/10 17:31:09 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void init(t_wolf *wolf)
{
	int width;

	width = WIN_W;
	wolf->mlx = mlx_init();
	wolf->win = mlx_new_window(wolf->mlx, WIN_W, WIN_H, WIN_NAME);
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
	return (1);
}

void expose(t_wolf *wolf)
{
//	draw_main_menu(wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img[MAIN_MENU].ptr, 0, 0);
}

int refresh(void *wptr)
{
	t_wolf *wolf;

	wolf = NULL;
	if (!wolf)
		return (0);
	wolf = (t_wolf*)wptr;
	mlx_destroy_image(wolf->mlx, wolf->img[MAIN_MENU].ptr);
	if (!(new_img(wolf, MAIN_MENU)))
		return (0);
	expose(wolf);
	return (1);
}










