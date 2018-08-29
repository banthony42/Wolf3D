/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 13:39:30 by banthony          #+#    #+#             */
/*   Updated: 2018/08/29 20:25:04 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Retourne la position du spawn sur la map.
**	Sinon retourne la position de la premiere case vide.
*/

static t_vector	find_spawn(char **map, t_texture spawner)
{
	t_vector	spawn;
	char		*find;
	int			i;

	find = NULL;
	i = -1;
	while (map[++i])
	{
		if ((find = ft_strchr(map[i], '0' + spawner)))
		{
			spawn.y = (i * BLOC_SIZE) + BLOC_SIZE / 2;
			spawn.x = ((int)(find - map[i]) * BLOC_SIZE) + BLOC_SIZE / 2;
			return (spawn);
		}
	}
	return (find_spawn(map, T_FLOOR));
}

static void		init_raycast(t_wolf *w)
{
	t_vector	spawn;
	double		incr;
	int			i;

	i = -1;
	incr = (double)FOV / (double)WIN_W;
	while (++i < WIN_W)
		w->cam.ray_dir[i] = (i * incr) - (FOV / 2);
	i = -1;
	while (++i < 360)
	{
		w->cos_table[i] = d_cos(i);
		w->sin_table[i] = d_sin(i);
	}
	spawn = find_spawn(w->map, T_SPAWN);
	spawn.angle = 180;
	w->cam.pos = spawn;
	w->cam.heightView = WIN_H / 2;
	w->cam.screenDist = (double)(WIN_W / 2) / d_tan(FOV / 2);
	w->cam.lengthView = 100 * BLOC_SIZE;
	w->cam.spd_move = 300;
	w->cam.spd_angle = 100;
	w->textured = 1;
	w->door_timer = 1;
	w->door_incr = -1;
}

static void		init_img(t_wolf *w)
{
	new_img(w, MAIN_MENU, (t_coord) {WIN_W, WIN_H, CLR});
	new_img(w, GAME, (t_coord) {WIN_W, WIN_H, CLR});
	new_img(w, MAP_CREATOR, (t_coord) {MAP_CRT_W, MAP_CRT_H, CLR});
	new_img(w, GAME_I, (t_coord) {INTRF_W, INTRF_H, CLR});
	new_img(w, MAP_I, (t_coord) {MAPI_W, MAPI_H, CLR});
	w->map_crea.m_size.x = w->img[MAP_I].size.x / ITEM_SIZE;
	w->map_crea.m_size.y = w->img[MAP_I].size.y / ITEM_SIZE;
	w->map_crea.map = ft_newtab(w->map_crea.m_size.y,
									w->map_crea.m_size.x, (int)'0');
	w->map_crea.texture = T_STONE;
	w->map_crea.grid_pos.x = (MAP_CRT_W - MAPI_W) / 2;
	w->map_crea.grid_pos.y = (MAP_CRT_H - MAPI_H) / 2;
	w->mini_map.x = (WIN_W - MAPI_W) / 2;
	w->mini_map.y = (WIN_H - MAPI_H) / 2;
}

void			init(t_wolf *wolf)
{
	wolf->mlx = mlx_init();
	wolf->win = mlx_new_window(wolf->mlx, WIN_W, WIN_H, WIN_NAME);
	wolf->draw[MAIN_MENU] = draw_main_menu;
	wolf->draw[GAME] = draw_game;
	wolf->draw[GAME_END] = draw_game_end;
	wolf->draw[MAP_CREATOR] = draw_map_creator;
	wolf->event_key[MAIN_MENU] = eventk_menu;
	wolf->event_key[GAME] = eventk_game;
	wolf->event_key[GAME_END] = eventk_game_end;
	wolf->event_key[MAP_CREATOR] = eventk_map_creator;
	wolf->event_mouse[MAIN_MENU] = eventm_menu;
	wolf->event_mouse[GAME] = eventm_game;
	wolf->event_mouse[GAME_END] = eventm_game_end;
	wolf->event_mouse[MAP_CREATOR] = eventm_map_creator;
	wolf->current_page = MAIN_MENU;
	wolf->cursor = 1;
	init_time_struct(&wolf->time);
	init_img(wolf);
	init_raycast(wolf);
	if (!(load_texture(wolf)))
		wolf_exit(ERR_TEXTURE, -1, wolf);
}
