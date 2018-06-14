/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:40:31 by banthony          #+#    #+#             */
/*   Updated: 2018/06/14 16:57:51 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define G_NAME "WOLF 3-D"
#define G_RUN "Game"
#define G_MC "Map Creator"
#define G_EXIT "Exit"
#define MENU_ENTRY 4

int			eventk_menu(int keyhook, void *wolf)
{
	t_wolf *w;

	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		wolf_exit("Escape menu", 0, w);
	else if (keyhook == MLX_KEY_UP && w->cursor > GAME)
		w->cursor--;
	else if (keyhook == MLX_KEY_DOWN && w->cursor < MAP_CREATOR + 1)
		w->cursor++;
	else if (keyhook == MLX_KEY_ENTER && w->cursor >= GAME
										&& w->cursor <= MAP_CREATOR)
		w->current_page = (t_page)w->cursor;
	else if (keyhook == MLX_KEY_ENTER)
		wolf_exit("Exit", 0, w);
	return (0);
}

int			eventm_menu(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

/*
**	Remplacer MENU_ENTRY par un enum
*/
static void	print_entry(t_coord (*pt)[MENU_ENTRY], t_wolf *w)
{
	(*pt)[0].x = PERCENTAGE(50, w->img[MAIN_MENU].size.x);
	(*pt)[0].y = PERCENTAGE(20, w->img[MAIN_MENU].size.y);
	(*pt)[1] = (*pt)[0];
	(*pt)[2] = (*pt)[0];
	(*pt)[3] = (*pt)[0];
	(*pt)[1].y += 240;
	(*pt)[2].y = (*pt)[1].y + 48;
	(*pt)[3].y = (*pt)[2].y + 48;
	string_to_img(G_NAME, centerx_str(G_NAME, (*pt)[0]), &w->img[MAIN_MENU], w);
	string_to_img(G_RUN, centerx_str(G_RUN, (*pt)[1]), &w->img[MAIN_MENU], w);
	string_to_img(G_MC, centerx_str(G_MC, (*pt)[2]), &w->img[MAIN_MENU], w);
	string_to_img(G_EXIT, centerx_str(G_EXIT, (*pt)[3]), &w->img[MAIN_MENU], w);
}

void		draw_main_menu(void *wolf)
{
	t_coord	pt[MENU_ENTRY];
	char	*entry[MENU_ENTRY];
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
	draw_grid(&w->img[MAIN_MENU]);
	entry[0] = G_NAME;
	entry[1] = G_RUN;
	entry[2] = G_MC;
	entry[3] = G_EXIT;
	put_texture_on_img(&w->img[MAIN_MENU], &w->texture[T_MAIN_MENU], w);
	mlx_put_image_to_window(w->mlx, w->win, w->img[w->current_page].ptr, 0, 0);
	print_entry(&pt, w);
	if (w->cursor)
	{
		pt[w->cursor].x -= 32 * (1 + (ft_strlen(entry[w->cursor]) / 2));
		string_to_img(">", pt[w->cursor], &w->img[MAIN_MENU], w);
		pt[w->cursor].x += 32 * (1 + (ft_strlen(entry[w->cursor])));
		string_to_img("<", pt[w->cursor], &w->img[MAIN_MENU], w);
	}
}
