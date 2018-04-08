/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:58:57 by banthony          #+#    #+#             */
/*   Updated: 2018/04/08 12:29:33 by banthony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		WOLF_H
# define	WOLF_H

#ifdef __linux__
#include "mlx_linux_key.h"
#elif __APPLE__
#include "mlx_macos_key.h"
#endif

#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

/*
** MACRO CALCUL
*/
# define PERCENTAGE(p, x) ((p * x) / 100)

/*
**	Parametre fenetre
*/
# define WIN_W 800
# define WIN_H 600
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
** Parametre Interface mini map
*/
# define IMAP_W PERCENTAGE(10, INTRF_W)
# define IMAP_H INTRF_W
# define CENTERIMAP_W(x) (IMAP_W - x) / 2
# define CENTERIMAP_H(x) (IMAP_H - x) / 2

/*
**	Parametre ecran du jeu
*/
# define SCREEN_W WIN_W
# define SCREEN_H WIN_H - INTRF_H
# define CENTERSCR_W(x) (SCREEN_W - x) / 2
# define CENTERSCR_H(x) (SCREEN_H - x) / 2

/*
** Wolf3D
*/
# define MAP_MAX 20
# define BOX 50

enum {VOID, STONE, BRICK, WOOD, DOOR, HEAL, WEAPON, AMO, SPAWN};

typedef struct	s_wolf
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*img_d;
	int			img_dsize;
	int			img_bpp;
	int			img_endian;
	int			win_w;
	int			win_h;
	int			_pad4;
	char		**map;
}				t_wolf;

/*
**	Message d'Erreur
*/
# define ERR_MAP "Invalid Map"
# define ERR_QUIT "User exit"

int  keyhook(int keycode, t_wolf *wolf);
void init(t_wolf *wolf);

#endif
