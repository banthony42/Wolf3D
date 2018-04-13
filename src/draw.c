/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:11:01 by banthony          #+#    #+#             */
/*   Updated: 2018/04/13 12:53:03 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	put_pixel_img(t_coord pt, int color, t_img *img)
{
	unsigned int pos;

	pos = (unsigned int)(pt.y * img->width) + ((unsigned int)pt.x * img->octet);
	if (pt.y >= WIN_H || pt.y < 0 || pt.x >= WIN_W || pt.x < 0)
		return ;
	if (pos > (unsigned)(img->width * WIN_W))
		return ;
	ft_memcpy(img->data + pos, &color, (unsigned)img->octet);
}

static int load_img(char *path, t_img *i, t_wolf *wolf)
{
	i->endian = 0;
	i->ptr = mlx_xpm_file_to_image(wolf->mlx, path, &i->size.x, &i->size.y);
	if (!i->ptr)
	{
		ft_putstr("Texture ");
		ft_putstr(path);
		ft_putstr(" : NOT LOADED !!\n");
		return (1);
	}
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->width, &i->endian);
	i->octet = (unsigned int)(i->bpp / 8);
	i->max_size = i->octet * (unsigned int)(i->size.x * i->size.y);
	ft_putstr("Texture ");
	ft_putstr(path);
	ft_putstr(" : LOADED - size in px: ");
	ft_putnbr(i->size.x);
	ft_putstr(" x ");
	ft_putnbrendl(i->size.y);
	return (0);
}

int load_texture(t_wolf *wolf)
{
	int error;

	error = 0;
	error = load_img("./texture/doom_font.xpm", &wolf->texture[T_POLICE], wolf);
	if (error)
		ft_exit("Error while loading texture", 0);
	return (0);
}
