/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:02:31 by banthony          #+#    #+#             */
/*   Updated: 2018/04/18 14:11:13 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	init_draw_line(t_coord *ic, t_coord *cd, t_coord *pta, t_coord *ptb)
{
	cd->x = abs(ptb->x - pta->x);
	cd->y = abs(ptb->y - pta->y);
	if (pta->x < ptb->x)
		ic->x = 1;
	else
		ic->x = -1;
	if (pta->y < ptb->y)
		ic->y = 1;
	else
		ic->y = -1;
}

static void	draw_first_case(t_coord dir, t_coord inc, t_coord *pt, t_img *img)
{
	int erreur;
	int i;

	i = -1;
	erreur = dir.x / 2;
	while (++i < dir.x)
	{
		pt->x += inc.x;
		erreur += dir.y;
		if (erreur > dir.x)
		{
			erreur -= dir.x;
			pt->y += inc.y;
		}
		put_pixel_img(*pt, pt->color, img);
	}
}

static void	draw_second_case(t_coord dir, t_coord inc, t_coord *pt, t_img *img)
{
	int erreur;
	int i;

	erreur = dir.y / 2;
	i = -1;
	while (++i < dir.y)
	{
		pt->y += inc.y;
		erreur += dir.x;
		if (erreur > dir.y)
		{
			erreur -= dir.y;
			pt->x += inc.x;
		}
		put_pixel_img(*pt, pt->color, img);
	}
}

void		draw_line_img(t_img *img, t_coord *pts_a, t_coord *pts_b)
{
	t_coord	pt;
	t_coord	dir;
	t_coord	inc;

	pt.x = pts_a->x;
	pt.y = pts_a->y;
	pt.color = pts_a->color;
	init_draw_line(&inc, &dir, pts_a, pts_b);
	if (dir.x > dir.y)
		draw_first_case(dir, inc, &pt, img);
	else
		draw_second_case(dir, inc, &pt, img);
	put_pixel_img(*pts_a, pts_a->color, img);
	put_pixel_img(*pts_b, pts_b->color, img);
}
