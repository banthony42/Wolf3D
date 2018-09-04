/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:45:46 by banthony          #+#    #+#             */
/*   Updated: 2018/09/04 18:20:46 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELTA_TIME_H
# define DELTA_TIME_H

# include <sys/time.h>

/*
**	Implementation du delta time pour les projets graphique ou autre.
**	Inclure les fichiers dans le projets.
**	Declarer une structure t_delta_time dans votre code.
**	Initialiser votre structure avec la fonction init_time_struct(&votre_struct)
**	Appeler update_time(&votre_struct) a chaque debut de boucle
**	print_delta_time vous fournit un debug / affichage des variables
*/

typedef void	(*t_ft_dtime)(void *delta_time_struct);

typedef struct		s_delta_time
{
	struct timeval	begin_time;
	struct timeval	present_time;
	struct timeval	old_time;
	double			elapsed;
	double			delta;
	double			fps;
	t_ft_dtime		update;
	t_ft_dtime		print;
}					t_delta_time;

void				init_time_struct(t_delta_time *ts);
void				update_time(void *delta_time_struct);
void				print_delta_time(void *delta_time_struct);

#endif
