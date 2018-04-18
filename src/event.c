/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:17:38 by banthony          #+#    #+#             */
/*   Updated: 2018/04/18 16:15:57 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	keyhook(int keycode, t_wolf *wolf)
{
	if (!wolf)
		return (0);
	wolf->event_key[wolf->current_page](keycode, wolf);
	return (0);
}

int	mousehook(int button, int x, int y, t_wolf *wolf)
{
	if (!wolf)
		return (0);
	wolf->event_mouse[wolf->current_page](button, x, y, wolf);
	return (0);
}

int	keypress(int keycode, void *w)
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf*)w))
		return (0);
	if (keycode == MLX_KEY_TAB)
		wolf->keypress[KEY_TAB] = 1;
	keyhook(keycode, wolf);
	return (1);
}

int	keyrelease(int keycode, void *w)
{
	t_wolf *wolf;

	if (!(wolf = (t_wolf*)w))
		return (0);
	if (keycode == MLX_KEY_TAB)
		wolf->keypress[KEY_TAB] = 0;
	return (1);
}
