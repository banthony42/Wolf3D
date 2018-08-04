/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_constante.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:53:57 by banthony          #+#    #+#             */
/*   Updated: 2018/08/04 22:06:17 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_CONSTANTE_H
# define WOLF_CONSTANTE_H

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
# ifdef __APPLE__
#  define WIN_W 1280
#  define WIN_H 960
# else
#  define WIN_W 800
#  define WIN_H 600
# endif
# define WIN_NAME "Wolf3D"
# define CENTERWIN_W(x) (WIN_W - x) / 2
# define CENTERWIN_H(y) (WIN_H - y) / 2

/*
** Parametre Interface Joueur
*/
# define INTRF_W WIN_W
# define INTRF_H PERCENTAGE(17, WIN_H)
# define CENTERINTRF_W(x) (INTRF_W - x) / 2
# define CENTERINTRF_H(y) (INTRF_H - y) / 2

/*
**	Parametre ecran du jeu
*/
# define SCREEN_W WIN_W
# define SCREEN_H WIN_H - INTRF_H
# define CENTERSCR_W(x) (SCREEN_W - x) / 2
# define CENTERSCR_H(y) (SCREEN_H - y) / 2

/*
** Parametre Interface map, overlay on game screen
*/
# define MAPI_W PERCENTAGE(70, SCREEN_W)
# define MAPI_H PERCENTAGE(70, SCREEN_H)
# define CENTERMAPI_W(x) (MAPI_W - x) / 2
# define CENTERMAPI_H(y) (MAPI_H - y) / 2

/*
** Wolf3D
*/
# define MAP_MIN 3
# define MAP_MAX 500
# define BOX 50
# define ITEM_SIZE 48

/*
**	Menu Principal
*/
#define G_NAME "WOLF 3-D"
#define G_RUN "Game"
#define G_MC "Map Creator"
#define G_EXIT "Exit"

/*
**	Map Creator
**	Nombre de texture dans la palette. (TEXT)
**	Ecart en pixel, (pitch) entre chaque box de texture. (TEXT_P)
*/
# define MC_TITLE "MAP CREATOR"
# define MC_INFO "Draw your map"
# define MC_SAVE "save"
# define TEXT 5
# define TEXT_P 16
# define CUSTOM_MAP_NAME "./custom_map_0.txt"
# define MAP_CREA_MAX_MAP '9' + 1

/*
**	Color
*/
# define MAP_OVERLAY 0x2f1f1f1f
# define DARK_RED 0xdf0000
# define DARK_GREY 0x939393
# define BROWN 0xcd661d

/*
**	Event pour mlx_hook
*/
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L<<0)
# define KEY_RELEASE_MASK (1L<<1)

/*
**	GESTION DE LA TEXTURE DE POLICE DOOM
**
**	Nombre de caractere par ligne dans la texture
*/
#define NB_C 18

/*
**	Les caracteres sont dans des cases de 32 x 48 pixel.
**	Afin de ne pas copier les contour de la case, nous recuperons
**	un rectangle legerement plus petit definit ci dessous.
**	La premiere case commence au pixel 34 en x et 34 en y.
*/
#define FRAME_X 32
#define FRAME_Y 48
#define BOX_X FRAME_X - 2
#define BOX_Y FRAME_Y - 2
#define START_XY 34

/*
**	Le tableau de caractere correspond a l'ordre d'un tableau ascii.
**	Cela permet de retrouver a quel ligne et quel rang le caractere voulu
**	se situe. Il suffira ensuite de calculer les coordonnes en pixel reel.
*/
#define GET_Y(c) ((c - ' ') / NB_C)
#define GET_X(c) ((c - ' ') % NB_C)

/*
**	Calcul de la position reel du caractere en pixel.
*/
#define GET_POS_X(c) (START_XY + (FRAME_X * GET_X(c)) )
#define GET_POS_Y(c) (START_XY + (FRAME_Y * GET_Y(c)) )

/*
**	Caractere a gerer differement pour l'espacement
**	lors de l'affichage d'une chaine de caractere.
**	(Caracteres qui rentre dans une case de 16 x 48 pixel).
*/
#define TINY_CHAR ".,1l!':;]Iij|["

#endif
