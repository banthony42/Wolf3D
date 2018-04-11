/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:57:27 by banthony          #+#    #+#             */
/*   Updated: 2018/04/11 15:59:03 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int					eventk_game_end(int keyhook, void *wolf)
{
	(void)keyhook;
	(void)wolf;
return (0);
}

int					eventm_game_end(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
return (0);
}

void	draw_game_end(void *wolf)
{
	(void)wolf;
}
