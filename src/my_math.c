/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 19:11:32 by banthony          #+#    #+#             */
/*   Updated: 2018/08/10 12:04:17 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**	Necessaire pour usiliser cos, car la fonction de la libMath
**	utilise des radians.
*/

static double	to_radian(double degree)
{
	return (M_PI / 180 * degree);
}

double	d_cos(double degree)
{
	return (cos(to_radian(degree)));
}

double	d_sin(double degree)
{
	return (sin(to_radian(degree)));
}

double	d_tan(double degree)
{
	return (tan(to_radian(degree)));
}
