/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:58:57 by banthony          #+#    #+#             */
/*   Updated: 2018/04/10 17:45:06 by banthony         ###   ########.fr       */
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
**	Message d'Erreur
*/
# define ERR_MAP "Invalid Map"
# define ERR_QUIT "User exit"

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

typedef enum	e_item
{
	VOID, STONE, BRICK, WOOD, DOOR, HEAL, WEAPON, AMO, SPAWN, NB_ITEM,
}				t_item;

typedef enum	e_texture
{
	T_FLOOR, T_SKY, T_STONE, T_BRICK, T_WOOD, T_DOOR, T_HEAL, T_WEAPON, T_AMO, T_SPAWN,
	T_MAIN_MENU, T_GAME_OVER, T_GAME_WIN, T_MAP_CREATOR, T_GAME_INTERFACE, T_MINI_MAP,
	NB_TEXTURE,
}				t_texture;

/*
** Definition des etats du jeux.
** Menu principal, Ecran du jeu, Ecran de fin de jeu (win/loose), creation de map
*/
typedef enum	e_page
{
	MAIN_MENU, GAME, GAME_OVER, GAME_WIN, MAP_CREATOR, NB_PAGE,
}				t_page;

typedef struct		t_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_pixel
{
	t_coord			pos;
	int				color;
}					t_pixel;

typedef struct		s_img
{
	void			*ptr;
	t_coord			size;
	char			*data;
	int				width;
	int				bpp;
	int				endian;
	int				max_size;
	unsigned int	octet;
	int				padding4;
}					t_img;

typedef struct		s_wolf
{
	void			*mlx;
	void			*win;
	t_img			img[NB_PAGE];
	t_coord			img_size[NB_PAGE];
	t_img			texture[NB_TEXTURE];
	t_coord			size_win;
	char			**map;
}					t_wolf;

int					keyhook(int keycode, t_wolf *wolf);
int					new_img(t_wolf *wolf, t_page page);
void				expose(t_wolf *wolf);
int					refresh(void *wptr);
void				init(t_wolf *wolf);

#endif
