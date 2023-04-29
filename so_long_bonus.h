/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 18:26:08 by ggiboury          #+#    #+#             */
/*   Updated: 2023/04/29 17:46:33 by ggiboury         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

void			start_bonus(t_case ***map, t_entity *ents);
void			my_hooks_bonus(void *game);
void			checks_bonus(t_game *g, t_entity *player);

/***************************** PARSING *****************************/

int				case_is_valid_bonus(t_case *box);
void			ft_flood_bonus(t_case ***map, t_node **visited, int x, int y);
t_case			***ft_parse_bonus(int fd);
t_case			***init_map_bonus(char **input, int y, int x);
int				map_is_possible_bonus(t_case ***map, t_entity *p, int nb_coin);
void			test_textures_bonus(t_game *g);

/******************************** UI *******************************/

void			build_entities_bonus(t_game *g);
mlx_texture_t	**init_textures_bonus(t_game *g);
int				init_ui_bonus(t_game *game, t_entity *ents);
void			render_panel(t_game *g);
void			update_ct(t_game *g, char c);

/******************************* UTILS *****************************/

void			get_coin_bonus(t_game *g, t_entity *coin);
int				is_enemy(t_entity *ent);
void			get_coin_bonus(t_game *g, t_entity *coin);

#endif