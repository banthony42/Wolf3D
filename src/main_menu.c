/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:40:31 by banthony          #+#    #+#             */
/*   Updated: 2018/04/16 18:33:52 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define G_NAME "W O L F 3-D"
#define G_RUN "Game"
#define G_MC "Map Creator"
#define MENU_ENTRY 3

int					eventk_menu(int keyhook, void *wolf)
{
	t_wolf *w;

	if (!(w = (t_wolf*)wolf))
		return (0);
	if (keyhook == MLX_KEY_ESCAPE)
		ft_exit("End menu", 0);
	else if (keyhook == MLX_KEY_UP && w->cursor > GAME)
			w->cursor--;
	else if (keyhook == MLX_KEY_DOWN && w->cursor < MAP_CREATOR)
			w->cursor++;
	else if (keyhook == MLX_KEY_ENTER && w->cursor >= GAME && w->cursor <= MAP_CREATOR)
		w->current_page = (t_page)w->cursor;
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

static void print_entry(t_coord (*pt)[MENU_ENTRY], t_wolf *w)
{
	(*pt)[0].x = w->img[MAIN_MENU].size.x / 2;
	(*pt)[0].y = (w->img[MAIN_MENU].size.y / 3);
	(*pt)[1] = (*pt)[0];
	(*pt)[2] = (*pt)[0];
	(*pt)[1].y += 140;
	(*pt)[2].y = (*pt)[1].y + 48;
	string_to_img(G_NAME, center_str_x(G_NAME, (*pt)[0]), &w->img[MAIN_MENU], w);
	string_to_img(G_RUN, center_str_x(G_RUN, (*pt)[1]), &w->img[MAIN_MENU], w);
	string_to_img(G_MC, center_str_x(G_MC, (*pt)[2]), &w->img[MAIN_MENU], w);
}

void	draw_main_menu(void *wolf)
{
	t_coord	pt[MENU_ENTRY];
	char	*entry[MENU_ENTRY];
	t_wolf	*w;

	if (!(w = (t_wolf*)wolf))
		return ;
	draw_grid(w);
	entry[0] = G_NAME;
	entry[1] = G_RUN;
	entry[2] = G_MC;
	put_texture_on_img(&w->img[MAIN_MENU], &w->texture[T_MAIN_MENU], w);
	print_entry(&pt, w);
	if (w->cursor)
	{
		pt[w->cursor].x -= 32 * (1 + (ft_strlen(entry[w->cursor]) / 2));
		string_to_img(">", pt[w->cursor], &w->img[MAIN_MENU], w);
		pt[w->cursor].x += 32 * (1 + (ft_strlen(entry[w->cursor])));
		string_to_img("<", pt[w->cursor], &w->img[MAIN_MENU], w);
	}
}
