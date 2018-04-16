/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banthony <banthony@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:58:57 by banthony          #+#    #+#             */
/*   Updated: 2018/04/16 17:56:37 by banthony         ###   ########.fr       */
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
# define MAPI_W PERCENTAGE(10, INTRF_W)
# define MAPI_H INTRF_W
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
	T_FLOOR, T_SKY, T_STONE, T_BRICK, T_WOOD, T_METAL, T_DOOR, T_HEAL, T_WEAPON, T_AMO, T_SPAWN,
	T_MAIN_MENU, T_GAME_OVER, T_GAME_WIN, T_MAP_CREATOR, T_GAME_INTERFACE, T_MINI_MAP,
	T_FONT, NB_TEXTURE,
}				t_texture;

/*
** Definition des etats du jeux.
** Menu principal, Ecran du jeu, Ecran de fin de jeu (win/loose), creation de map
*/
typedef enum	e_page
{
	MAIN_MENU, GAME, MAP_CREATOR, GAME_END, NB_PAGE, GAME_I, MAP_I, NB_IMG,
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
	unsigned int	max_size;
	unsigned int	octet;
	int				padding4;
}					t_img;

/*
**	Variables et gestion du joueur
*/
typedef struct		s_player
{
	t_coord			pos;
}					t_player;

/*
**	Variables et gestion de la creation de map
*/
typedef struct		s_creator
{
	char			**map;
}					t_creator;

/*
** Definit les fonctions qui dessine les pages
*/
typedef void		(*t_draw)(void *wolf);

/*
** Definit les fonctions qui gere les event de chaque pages
*/
typedef int			(*t_event_k)(int keyhook, void *wolf);
typedef int			(*t_event_m)(int button, int x, int y, void *wolf);

/*
**	img.size = taille de la texture lors d'un chargement d'un fichier xpm
*/
typedef struct		s_wolf
{
	void			*mlx;
	void			*win;
	t_coord			size_win;
	t_img			img[NB_IMG];
	t_img			texture[NB_TEXTURE];
	t_draw			draw[NB_PAGE];
	t_event_k		event_key[NB_PAGE];
	t_event_m		event_mouse[NB_PAGE];
	char			**map;
	int				cursor;
	t_page			current_page;
	t_player		*player;
	t_creator		map_creator;
}					t_wolf;

t_coord				center_str_x(char *str, t_coord pt);
void				string_to_img(char *str, t_coord pt, t_img *img, t_wolf *wolf);
void				put_texture_on_img(t_img *dest, t_img *text, t_wolf *w);
void				put_pixel_from_texture(t_coord pti, t_coord ptt, t_img *text, t_img *img);
void				put_pixel_img(t_coord pt, int color, t_img *img);

int					eventk_menu(int keyhook, void *wolf);
int					eventk_game(int keyhook, void *wolf);
int					eventk_game_end(int keyhook, void *wolf);
int					eventk_map_creator(int keyhook, void *wolf);

int					eventm_menu(int button, int x, int y, void *wolf);
int					eventm_game(int button, int x, int y, void *wolf);
int					eventm_game_end(int button, int x, int y, void *wolf);
int					eventm_map_creator(int button, int x, int y, void *wolf);

void				draw_main_menu(void *wolf);
void				draw_game(void *wolf);
void				draw_game_end(void *wolf);
void				draw_map_creator(void *wolf);

int					mousehook(int button, int x, int y, t_wolf *wolf);
int					keyhook(int keycode, t_wolf *wolf);
int					new_img(t_wolf *wolf, t_page page, t_coord size);
void				expose(t_wolf *wolf);
int					load_texture(t_wolf *wolf);
int					refresh(void *wptr);
void				init(t_wolf *wolf);

/*TEMPORAIRE*/
void				draw_grid(t_wolf *w);
#endif
