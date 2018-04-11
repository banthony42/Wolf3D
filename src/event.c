/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 17:17:38 by banthony          #+#    #+#             */
/*   Updated: 2018/04/11 17:21:19 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int keyhook(int keycode, t_wolf *wolf)
{
	if (!wolf)
		return (0);
	wolf->event_key[wolf->current_page](keycode, wolf);
	return (0);
}

int mousehook(int button, int x, int y, t_wolf *wolf)
{
	if (!wolf)
		return (0);
	wolf->event_mouse[wolf->current_page](button, x, y, wolf);
	return (0);
}










