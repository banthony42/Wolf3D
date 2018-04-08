/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 23:28:27 by banthony          #+#    #+#             */
/*   Updated: 2018/04/08 11:46:00 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int  keyhook(int keycode, t_wolf *wolf)
{
	if (keycode == MLX_KEY_ESCAPE)
		ft_exit(ERR_QUIT, 0);
	(void)wolf;
	return (0);
}
