/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 16:11:01 by banthony          #+#    #+#             */
/*   Updated: 2018/08/09 17:31:17 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Remplit le pixel de coordonees pt, et de l'image *img, avec color.
*/

void		put_pixel_img(t_coord pt, unsigned int color, t_img *img)
{
	unsigned int pos;

	if (pt.y >= WIN_H || pt.y < 0 || pt.x >= WIN_W || pt.x < 0)
		return ;
	pos = (unsigned int)(pt.y * img->width) + ((unsigned int)pt.x * img->octet);
	if (pos > (unsigned)(img->width * WIN_W))
		return ;
	ft_memcpy(img->data + pos, &color, (unsigned int)img->octet);
}

void		trace(t_img *img, t_coord a, t_coord b, unsigned int color)
{
	int	delta;
	int i;
	t_vector step;
	t_vector pt_d;
	t_coord pt;

	if (abs(b.x - a.x) >= abs(b.y - a.y))
		delta = abs(b.x - a.x);
	else
		delta = abs(b.y - a.y);
	step.x = ((double)b.x - (double)a.x) / (double)delta;
	step.y = ((double)b.y - (double)a.y) / (double)delta;
	pt_d.x = a.x + 0.5;
	pt_d.y = a.y + 0.5;
	i = -1;
	while (++i < delta)
	{
		pt.x = (int)pt_d.x;
		pt.y = (int)pt_d.y;
		put_pixel_img(pt, color, img);
		pt_d.x += step.x;
		pt_d.y += step.y;
	}
}

/*
**	Remplit le pixel pti de l'img avec le pixel ptt de la texture text.
*/

void		put_pixel_from_txt(t_coord pti, t_coord ptt, t_img *txt, t_img *img)
{
	unsigned int pos;
	unsigned int pos_txt;

	if (ptt.x > txt->size.x || ptt.y > txt->size.y || ptt.x < 0 || ptt.y < 0)
		return ;
	if (pti.y >= img->size.y || pti.y < 0 || pti.x >= img->size.x || pti.x < 0)
		return ;
	pos = (unsigned int)(pti.y * img->width)
			+ ((unsigned int)pti.x * img->octet);
	pos_txt = (unsigned int)(ptt.y * txt->width)
			+ ((unsigned int)ptt.x * txt->octet);
	if (pos > (unsigned)(img->width * WIN_W))
		return ;
	ft_memcpy(img->data + pos, txt->data + pos_txt, (unsigned int)img->octet);
}

void		put_texture_on_img_at(t_img *dest, t_img *text,
									t_coord at, t_coord text_size)
{
	t_coord pt;
	t_coord ptt;
	t_coord pt_max;

	pt_max.x = at.x + text_size.x;
	pt_max.y = at.y + text_size.y;
	pt.y = at.y;
	if (!dest || !text)
		return ;
	while (pt.y < pt_max.y)
	{
		pt.x = at.x;
		while (pt.x < pt_max.x)
		{
			ptt.x = (text->size.x * (pt.x - at.x)) / text_size.x;
			ptt.y = (text->size.y * (pt.y - at.y)) / text_size.y;
			put_pixel_from_txt(pt, ptt, text, dest);
			pt.x++;
		}
		pt.y++;
	}
}

void		put_texture_on_img(t_img *dest, t_img *text)
{
	t_coord pt;
	t_coord ptt;

	pt.y = 0;
	if (!dest || !text)
		return ;
	while (pt.y < dest->size.y)
	{
		pt.x = 0;
		while (pt.x < dest->size.x)
		{
			ptt.x = (text->size.x * pt.x) / dest->size.x;
			ptt.y = (text->size.y * pt.y) / dest->size.y;
			put_pixel_from_txt(pt, ptt, text, dest);
			pt.x++;
		}
		pt.y++;
	}
}

/*
**	Remplit l'image avec la couleur en parametre
*/

void		fill_img(t_img *img, unsigned int color)
{
	t_coord pt;

	pt.y = 0;
	while (pt.y < img->size.y)
	{
		pt.x = 0;
		while (pt.x < img->size.x)
		{
			put_pixel_img(pt, color, img);
			pt.x++;
		}
		pt.y++;
	}
}
