/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_constante.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:53:57 by banthony          #+#    #+#             */
/*   Updated: 2018/04/17 18:02:40 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		WOLF_CONSTANTE_H
# define	WOLF_CONSTANTE_H

/*
**	Message d'Erreur
*/
# define ERR_MAP "Error: Invalid Map"
# define ERR_OPEN "Error: While openning the file"
# define ERR_CLOSE "Error: While closing the file"
# define ERR_IMG "Error: While creating new image"
# define ERR_TEXTURE "Error: While loading texture"
# define ERR_QUIT "User exit"

/*
** MACRO CALCUL
*/
# define PERCENTAGE(p, x) ((p * x) / 100)

/*
**	Parametre fenetre
*/
# define WIN_W 1200
# define WIN_H 1080
# define WIN_NAME "Wolf3D"
# define CENTERWIN_W(x) (WIN_W - x) / 2
# define CENTERWIN_H(x) (WIN_H - x) / 2

/*
** Parametre Interface Joueur
*/
# define INTRF_W WIN_W
# define INTRF_H PERCENTAGE(17, WIN_H)
# define CENTERINTRF_W(x) (INTRF_W - x) / 2
# define CENTERINTRF_H(x) (INTRF_H - x) / 2

/*
**	Parametre ecran du jeu
*/
# define SCREEN_W WIN_W
# define SCREEN_H WIN_H - INTRF_H
# define CENTERSCR_W(x) (SCREEN_W - x) / 2
# define CENTERSCR_H(x) (SCREEN_H - x) / 2

/*
** Parametre Interface map, overlay on game screen
*/
# define MAPI_W PERCENTAGE(80, SCREEN_W)
# define MAPI_H PERCENTAGE(80, SCREEN_H)
# define CENTERIMAP_W(x) (IMAP_W - x) / 2
# define CENTERIMAP_H(x) (IMAP_H - x) / 2

/*
** Wolf3D
*/
# define MAP_MAX 20
# define BOX 50

/*
**	Color
*/
# define MAP_OVERLAY 0x0d1f1f1f


# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

#endif




















