/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:46:03 by banthony          #+#    #+#             */
/*   Updated: 2018/08/05 18:47:45 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "delta_time.h"
#include <stdio.h>

/*
**	Initialise la structure delta time.
**	Recuperation du premier timestamp, (begin_time).
**	Assignation de la fonction update dans la structure.
*/

void	init_time_struct(t_delta_time *ts)
{
	if (!ts)
		return ;
	gettimeofday(&ts->begin_time, NULL);
	ts->present_time = ts->begin_time;
	ts->update = update_time;
	ts->print = print_delta_time;
}

/*
**	Met a jour la structure delta time.
**	Stockage du timestamp precedent.
**	Recuperation d'un nouveau timestamp.
**	Calcul du temps ecoule en millisecondes.
**	Calcul du delta time.
*/

void	update_time(void *delta_time_struct)
{
	t_delta_time *ts;

	ts = NULL;
	if (!(ts = (t_delta_time*)delta_time_struct))
		return ;
	ts->old_time = ts->present_time;
	gettimeofday(&ts->present_time, NULL);
	ts->elapsed = (ts->present_time.tv_sec - ts->old_time.tv_sec) * 1000.0;
	ts->elapsed += (ts->present_time.tv_usec - ts->old_time.tv_usec) / 1000.0;
	ts->delta = ts->elapsed / 1000;
	ts->fps = 1 / ts->delta;
}

/*
**	Affichage des variable de la structure delta time
*/

void	print_delta_time(void *delta_time_struct)
{
	t_delta_time *ts;

	ts = NULL;
	if (!(ts = (t_delta_time*)delta_time_struct))
		return ;
	printf("elapsed: %f ms - delta: %f - fps: %d\n", ts->elapsed, ts->delta, (int)ts->fps);
	// /!\ printf - recoder un putnbrf()
}
