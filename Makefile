# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 18:49:17 by ggiboury          #+#    #+#              #
#    Updated: 2023/07/29 23:21:37 by ggiboury         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

FLAGS = -Wall -Werror -Wextra

NAME = so_long
NAME_BONUS = so_long_bonus

SRCS = 	ft_actions.c			\
		ft_actions2.c			\
		game.c					\
		ft_init.c				\
		ft_itos.c				\
		ft_parse.c				\
		ft_str_utils.c			\
		ft_write.c				\
		ft_free.c				\
		ft_map_valid.c			\
		ft_map_utils.c			\
		ft_map_utils2.c			\
		ft_grid_utils.c			\
		ft_hooks.c				\
		ft_hooks2.c				\
		ft_flood.c

S_MAIN = so_long.c

OBJS_COMMON = $(SRCS:.c=.o)

OBJ_MAIN = $(S_MAIN:.c=.o)


SRCS_BONUS = animations.c		\
		ft_bonus.c				\
		ft_bonus2.c				\
		ft_parse_bonus.c

S_MAIN_BONUS = so_long_bonus.c

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

OBJ_MAIN_BONUS = $(S_MAIN_BONUS:.c=.o)


LIBFT_DIR = libft
LIBFT_FILE = $(LIBFT_DIR)/libft.a
LIBFT = ./libft.a

LIBMLX = ./MLX42

LIB = -framework Cocoa -framework OpenGL -framework IOKit -L"/Users/${USER}/.brew/opt/glfw/lib/" -lglfw -lmlx42 -L. -lft
HEADERS = -I $(LIBMLX)/include

NC=\033[0m
GREEN=\033[0;32m
RED=\033[0;31m


all : $(NAME)

$(LIBFT) :
	@echo "Loading $(BOLD)libft$(NC)"
	@make -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/libft.a $(LIBFT)
	@if [ ! -f $(LIBFT) ]; then \
		echo "$(RED)Echec while loading libft.$(NC)";\
	else \
		echo "$(GREEN)$(LIBFT) loaded.$(NC)";\
	fi

lib : $(LIBFT) 
	@if [ ! -d MLX42 ]; then \
		echo "Downloading miniLibX..."; \
		git clone https://github.com/codam-coding-college/MLX42 $(LIBMLX); \
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4; \
	else \
		echo "$(GREEN)MiniLibX already installed.$(NC)";\
	fi
	@if [ -f libft.a ] && [ -d $(LIBMLX) ] && [ -f $(LIBMLX)/build/libmlx42.a ] && [ -f $(LIBMLX)/include/MLX42/MLX42.h ] ; then \
		echo "$(GREEN)All libraries present.$(NC)"; \
		if [ ! -f ./libmlx42.a ]; then \
			cp $(LIBMLX)/build/libmlx42.a ./ ;\
		fi \
	else \
		echo "$(RED)ERROR : failed while installing libs.$(NC)"; \
	fi

$(OBJS_COMMON) : $(SRCS)
	@gcc $(FLAGS) $? -c $(HEADERS)

$(OBJ_MAIN) : $(S_MAIN)
	@gcc $(FLAGS) $? -c $(HEADERS)
	
$(NAME) : lib $(OBJS_COMMON) $(OBJ_MAIN)
	@gcc $(FLAGS) $(OBJS_COMMON) $(OBJ_MAIN) -o $(NAME) $(LIB) $(HEADERS)

re : fclean $(NAME)

clean :
	@make -C $(LIBFT_DIR) clean
	@/bin/rm -rf $(OBJS_COMMON)
	@/bin/rm -rf $(OBJ_MAIN)
	@/bin/rm -rf $(OBJS_BONUS)
	@/bin/rm -rf $(OBJ_MAIN_BONUS)
	@echo ".o files removed."

fclean : clean
	@if [ -d $(LIBMLX) ]; then \
		echo "Removing LIBMLX";\
		/bin/rm -rf $(LIBMLX);\
	fi
	@/bin/rm -f libft.a
	@/bin/rm -f libmlx42.a
	@make -C $(LIBFT_DIR) fclean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(LIBFT)
	@echo "$(GREEN)All compiled files removed.$(NC)"
	@/bin/rm -f $(NAME_BONUS)

$(OBJS_BONUS) : $(SRCS_BONUS)
	@gcc $(FLAGS) $? -c $(HEADERS)

$(OBJ_MAIN_BONUS) : $(S_MAIN_BONUS)
	@gcc $(FLAGS) $? -c $(HEADERS)

bonus : lib $(OBJS_COMMON) $(OBJS_BONUS) $(OBJ_MAIN_BONUS)
	@gcc $(FLAGS) $(OBJS_COMMON) $(OBJS_BONUS) $(OBJ_MAIN_BONUS) -o $(NAME_BONUS) $(LIB) $(HEADERS)
