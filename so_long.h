/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:43:43 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/26 20:33:34 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define WIN_W 1024
# define WIN_H 1024

# define SIZE_IMG 64

# define NB_CASE 16

# include <errno.h> 
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <MLX42/MLX42.h>
# include "libft/libft.h"

/********************************* MODEL ********************************/

typedef struct s_entity{
	int				life;
	int				coo[2];
	char			n;
	struct s_entity	*next;
	mlx_image_t		*sprite;
}	t_entity;

// A box
typedef struct s_case{
	int				is_wall;
	struct s_entity	*ent;
	mlx_image_t		*sprite;
}	t_case;

// Nodes registering the boxes we already explored.
typedef struct s_node{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

// Controller
typedef struct s_game{
	mlx_t			*mlx;
	struct s_case	***map;
	mlx_texture_t	**textures;
	struct s_entity	*entities;
	mlx_image_t		*ct_img;
	mlx_image_t		*ct2_img;
	mlx_image_t		*str[2];
	int				ct_movement;
	int				ct_items;
}	t_game;

/******************************* PARSING THE MAP *****************************/

int				case_is_valid(t_case *box);
char			**ft_append_tab(char **tab, char *s);
t_case			***ft_parse(int fd);
int				ft_verify_file(char *file);
t_entity		*get_ents(t_case ***map);
t_case			*init_case(char c, int x, int y);
t_case			***init_map(char **input, int y, int x);
int				line_is_wall(t_case **line);
int				map_has_duplicates(t_case ***map);
void			map_is_invalid(t_case ***map, t_entity *ents);
int				map_is_rectangular(t_case ***map);
t_entity		*new_entity(char c, int x, int y);

/********************************* FLOOD ALGO ********************************/

int				map_is_possible(t_case ***map, t_entity *player, int nb_coin);
void			add_back(t_node **visited, int x, int y);
int				final_check(t_case ***map, t_node *visited, int nb_coin);
void			ft_flood(t_case ***map, t_node **visited, int x, int y);
int				is_visited(t_node *visited, int x, int y);

/****************************** BUILDING THE VIEW ****************************/

void			build_map(t_game *g);
void			build_entities(t_game *g);
mlx_texture_t	**init_textures(t_game *g);
int				init_ui(t_game *game, t_entity *ents);
void			render(t_game *g, int o_x, int o_y);
void			start(t_case ***map, t_entity *ents);
void			test_textures(t_game *g);

/***************************** UTILS *****************************/

void			free_append_tab(char **tab, char *s, char **new_tab);
void			free_entities(t_game g);
void			free_game(t_game g);
void			free_map(t_case ***map);
void			free_nodes(t_node *v);
void			free_print_error(char **str, char *s);
void			free2_print_error(t_game *g, char *s);
char			**free_tab_str(char **tab);
void			malloc_error_map(t_case ***map, int x, int y);

char			get_direction(int c[2]);
t_entity		*get_entity(t_entity *ents, char c);
t_entity		*get_first_ent(t_case ***map);
int				get_nb_coin(t_entity *ents);
int				get_off_x(t_case ***map, t_entity *p);
int				get_off_y(t_case ***map, t_entity *p);
int				get_wall_x(t_game *g);
int				get_wall_y(t_game *g);
int				get_x(t_case ***map);
int				get_y(t_case ***map);

int				itos_get_len(int x);
char			*ft_itos(unsigned int x);

int				print_error(char *s);
void			print_entities(t_entity *ent);
void			print_map(t_case ***map);
void			print_nodes(t_node *v);
void			print_on_mov(int moves);

/***************************** Action *****************************/

void			checks(t_game *g, t_entity *player);
int				collision(t_entity *p, t_entity *ent);
int				is_possible(t_case ***map, char direction, int x, int y);
int				is_border_far(t_game *g, t_entity *p, int c[2], char d);

int				close_game(t_game *g);
void			end(t_game *g, t_entity *p);
void			get_coin(t_game *g, t_entity *ent);
int				move(t_game *g, t_entity *p);
void			move_map(t_game *g, t_entity *p, int x, int y);
void			my_hooks(void *game);
void			update_coo(t_game *g, t_entity *p, int c[2], char d);

#endif