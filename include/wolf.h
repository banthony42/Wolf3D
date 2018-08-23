/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grdalmas <grdalmas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:58:57 by banthony          #+#    #+#             */
/*   Updated: 2018/08/23 19:16:24 by grdalmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# ifdef __linux__
#  include "mlx_linux_key.h"
# elif __APPLE__
#  include "mlx_macos_key.h"
# endif

# include "mlx.h"
# include "libft.h"
# include "wolf_constante.h"
# include "delta_time.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# include <stdio.h>

/*
**	Enumeration des textures
**	Cela permet de creer un tableau d'image de taille NB_TEXTURE,
**	contenant chaque textures. On peut ainsi acceder a notre texture
**	dans le code plus simplement: tab[NOM_DE_LA_TEXTURE]
*/
typedef enum	e_texture
{
	T_FLOOR, T_STONE, T_WOOD, T_REDBRICK, T_DOOR, T_ERASER, T_FLOOR2, T_WEAPON,
	T_AMO, T_SPAWN, T_SKY, T_MAIN_MENU, T_GAME_OVER, T_GAME_WIN,
	T_MAP_CREATOR, T_GAME_INTERFACE, T_CREATOR_INTERFACE, T_MINI_MAP, T_FONT,
	NB_TEXTURE,
}				t_texture;

/*
**	Enumeration des etats du jeux.
**	Menu principal, Ecran du jeu, Ecran de fin de jeu (win/loose),
**	et Creation de map.
**	Un etat de jeux corresspond a une page / une scene.
**	Chaque page doit avoir sa propre fonction de dessin,
**	de gestion d'evenement et sa propre image.
**	Grace a l'enum on va pouvoir faire un tableau de pointeur sur fonction.
**	L'index de ce tableau correspondra a une valeur de l'enum.
**	Cela nous permet d'ecrire dans le code:
**	draw_ptr_func[PAGE]() qui dessinera la page correspondante.
**	event_ptr_func[PAGE]() qui gerera les event de la page correspondante.
**	image[PAGE] qui nous permet d'acceder a l'image de la page correspondante.
**	GAME_I et MAP_I sont des exceptions et sont de simple image.
**	Elles sont utilise dans les page GAME et MAP_CREATOR
*/
typedef enum	e_page
{
	MAIN_MENU, GAME, MAP_CREATOR, GAME_END, NB_PAGE, GAME_I, MAP_I, NB_IMG,
}				t_page;

/*
**	Enumeration des touches qui peuvent etre presse ensemble
**	Exemple: Avancer + decalage droit (W + D)
**	Utile aussi pour sauvegarder l'etat de la touche
**	pour agir en consequence dans l'expose.
*/
typedef enum	e_keystate
{
	LAST_KEY_PRESS,
	KEY_TAB, KEY_W, KEY_A, KEY_S, KEY_D,
	KEY_LEFT, KEY_RIGHT,
	NB_KEYSTATE,
}				t_keystate;

typedef enum	e_direction
{
	NORTH, SOUTH, EST, WEST,
}				t_direction;

/*
**	Enumeration des entrees du menu principal
**	Cela permet de sauvegarder une variable cursor sur une valeur de l'enum
**	pour afficher le curseur de selection a l'ecran, au bon endroit.
*/
typedef enum	e_menu
{
	TITLE, RUN, MAP_CREA, EXIT, NB_MENU_ENTRY,
}				t_menu;

/*
**	Definit un pixel.
**	Utilise aussi pour definir une taille. (exemple: image)
*/
typedef struct		s_coord
{
	int				x;
	int				y;
	unsigned int	color;
}					t_coord;

/*
**	Definit un vecteur ou un point dans l'espace.
*/
typedef struct		s_vector
{
	double			x;
	double			y;
	double			angle;
}					t_vector;

/*
**	Definit un ensemble de variable utile a la gestion d'image de la mlx.
**	ptr:	Pointeur renvoye par mlx_new_image()
**	data:	Buffer de l'image renvoyer par mlx_get_data_addr()
**	size:	Taille de l'image
**	width:	Largeur de l'image
**	bpp:	Nombre de bit utilise pour un pixel
**	endian:	Definit le sens d'encodage
**	octet:	Nombre d'octet pour un pixel
*/
typedef struct		s_img
{
	void			*ptr;
	char			*data;
	t_coord			size;
	int				width;
	int				bpp;
	int				endian;
	unsigned int	octet;
	char			padding[4];
}					t_img;

/*
**	Definit les valeurs utiles lors d'un lancer de rayon fructueux.
**	object:	Valeur de l'enum de la texture touche par le rayon
**	point:	Point ou le rayon a touche l'objet
**	dist:	Distance parcouru par le rayon
**	side:	Info sur quel face de l'objet a ete touche (point.x ou point.y)
*/
typedef struct		s_hit_info
{
	t_vector		point;
	double			dist;
	double			side;
	t_img			object;
	char			padding[8];
}					t_hit_info;

/*
**	Definit les variable de la camera
**	pos:		Position de la camera dans le monde
**	ray_dir:	Look up table contentant l'angle de direction des rayons.
**				Le numeros d'index correspond a une colonne sur l'ecran.
**				Les valeurs ne change pas donc, cette table est calcule
**				une fois dans l'init pour eviter des calculs inutile.
**	heightView:	Hauteur de la camera dans le monde
**	screenDist:	Distance de l'ecran par rapport a la camera
**	lengthView:	Distance de vision max
**	fov:		Field Of View, angle definissant le champs de vision de la camera
**	fov_half:	fov / 2, calcule dans l'init
**	spd_move:	Vitesse de deplacement de la camera dans le monde
**	spd_angle:	Vitesse de rotation de la camera dans le monde
*/
typedef struct		s_cam
{
	t_vector		pos;
	double			ray_dir[WIN_W];
	double			heightView;
	double			screenDist;
	double			lengthView;
	double			spd_move;
	double			spd_angle;
}					t_cam;

/*
**	Definit les variables pour la creation de map
**	map:		Tableau contenant la map cree par l'utilisateur
**	m_size:		Taille de la variable map
**	texture:	Texture selectionnee par l'utilisateur pour dessiner
*/
typedef struct		s_creator
{
	char			**map;
	t_coord			m_size;
	t_texture		texture;
}					t_creator;

/*
**	Definit les fonctions utile a chaque pages:
**	t_draw fonction qui dessine.
**	t_event_k fonction qui gere les evenements claviers.
**	t_event_m fonctions qui gere les evenements souris.
*/
typedef void		(*t_draw)(void *wolf);
typedef int			(*t_event_k)(int keyhook, void *wolf);
typedef int			(*t_event_m)(int button, int x, int y, void *wolf);

/*
**	Structure principale du jeu
**	mlx:			Pointeur recu lors d'un mlx_init()
**	win:			Pointeur de la fenetre du jeu recu lors d'un mlx_new_window()
**	map:			Map du jeu envoye par l'utilisateur
**	img:			Tableau d'image utile au jeu
**	texture:		Tableau d'image contenant les textures, Ainsi texture[T_WOOD]
**					donne accees a la struct image contenant la texture de BOIS.
**	draw:			Tableau de fonction de dessin, Ainsi l'appel a draw[MAIN_MENU]()
**					dessine le menu principal.
**	event_key:		Tableau de fonction de gestion d'evenements clavier,
**					Ainsi l'appel a event_key[MAIN_MENU]() gere les
**					evenements clavier du menu principal.
**	event_mouse:	Tableau de fonction de gestion d'evenements souris,
**					Ainsi l'appel a event_mouse[MAIN_MENU]() gere les
**					evenements souris du menu principal.
**	map_size:		Taille de la map envoye par l'utilisateur
**	current_page:	Etat du jeux, donne l'information sur quel page doit etre geree
**	cam:			Variable de la cameras
**	map_crea:		Variable pour la creation de map
**	time:			Structure independante au projets, qui gere le temps, les fps, etc ..
**					(Voir delta_time.c/.h)
**	keypress:		Tableau de sauvegarde des etats pour certaines touches
**	cursor:			Etat du curseur du menu
*/
typedef struct		s_wolf
{
	void			*mlx;
	void			*win;
	char			**map;
	t_img			img[NB_IMG];
	t_img			texture[NB_TEXTURE];
	t_draw			draw[NB_PAGE];
	t_event_k		event_key[NB_PAGE];
	t_event_m		event_mouse[NB_PAGE];
	t_coord			map_size;
	t_page			current_page;
	t_cam			cam;
	t_creator		map_crea;
	t_delta_time	time;
	t_hit_info		hit[WIN_W];
	int				keypress[NB_KEYSTATE];
	int				cursor;
	int				textured;
}					t_wolf;

void				raycast_1(t_wolf *w);

double				d_tan(double degree);
double				d_cos(double degree);
double				d_sin(double degree);
void				move_right(t_wolf *w);
void				move_left(t_wolf *w);
void				move_back(t_wolf *w);
void				move_forward(t_wolf *w);

void				draw_palette(t_wolf *w);

void				draw_text_button(char *str, t_wolf *w, t_page page,
											t_coord pt);

void				draw_map(t_wolf *w, char **map, t_coord map_size);
void				draw_grid(t_wolf *w, t_page page, int square);

void				draw_box(t_coord size, t_coord start, int offset,
											t_img *img);

void				draw_line_img(t_img *img, t_coord *pts_a,
											t_coord *pts_b);

t_coord				centerx_str(char *str, t_coord pt);

void				string_to_img(char *str, t_coord pt, t_img *img,
											t_wolf *wolf);

void				fill_img(t_img *img, unsigned int color);
void				put_texture_on_img(t_img *dest, t_img *text);

void				put_texture_on_img_at(t_img *dest, t_img *text, t_coord at,
											t_coord text_size);

void				put_pixel_from_txt(t_coord pti, t_coord ptt, t_img *text,
											t_img *img);

void				put_pixel_img(t_coord pt, unsigned int color, t_img *img);

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

int					keypress(int keycode, void *w);
int					keyrelease(int keycode, void *w);
int					mousehook(int button, int x, int y, t_wolf *wolf);
int					new_img(t_wolf *wolf, t_page page, t_coord size);
void				expose(t_wolf *wolf);
int					refresh(void *wptr);
int					ft_clos(void *wolf);
void				renderer(t_wolf *w, int ray_x, t_hit_info hit, double h_wall);
void				init(t_wolf *wolf);

void				save_map_into_file(t_wolf *w);
int					load_texture(t_wolf *wolf);
void				wolf_exit(char *str, int status, t_wolf *wolf);
double				map_scaler(t_coord map_size, t_coord img_size);

/*
**	Fonctions temporaire
*/
void				draw_landmark(t_img *img);

#endif
