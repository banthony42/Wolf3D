/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:42:07 by banthony          #+#    #+#             */
/*   Updated: 2018/04/11 15:46:55 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int					eventk_game(int keyhook, void *wolf)
{
	(void)keyhook;
	(void)wolf;
return (0);
}

int					eventm_game(int button, int x, int y, void *wolf)
{
	(void)wolf;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}

void	draw_game(void *wolf)
{
	(void)wolf;
}
