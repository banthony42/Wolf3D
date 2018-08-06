/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:00:24 by grdalmas          #+#    #+#             */
/*   Updated: 2018/08/06 19:19:25 by grdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	right(t_wolf *w)
{
	
}

void	left(t_wolf *w)
{
	
}

void	horizontal_mv(int key, t_wolf *w)
{
	
}

void	lateral_mv(int key, t_wolf *w)
{
	
}
/*
** Creation de fonction de mouvement (Deso je savais pas pas quoi commencer xD)
*/

void	player_move(int key, t_wolf *w)
{
	horizontal_mv(key, w);
	lateral_mv(key, w);
	if (key == MLX_KEY_PAD_4)
		left(w); // a coder
	if (key == MLX_KEY_PAD_6)
		right(e); // a coder
	if (key == MLX_KEY_SPACEBAR)
		//variable saut a reflechir genre jump != jump a creuser
	if (key == MLX_KEY_SHIFT_LEFT)
		//variable sprint meme modele que jump
	if (key == MLX_KEY_ESCAPE)
	{
		mlx_destroy_window(w->mlx, w->win)
		exit(0);
	}
}
