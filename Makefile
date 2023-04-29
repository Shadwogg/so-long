# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiboury <ggiboury@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 18:49:17 by ggiboury          #+#    #+#              #
#    Updated: 2023/04/29 18:48:04 by ggiboury         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# https://coolors.co/db2b39-29335c-f3a712-f0cea0-534d41
NAME = so_long
NAME_BONUS = so_long_bonus

SRC = so_long.c					\
		ft_actions.c			\
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

SRC_BONUS = so_long_bonus.c		\
		ft_actions.c			\
		ft_actions2.c			\
		ft_bonus.c				\
		ft_bonus2.c				\
		game.c					\
		ft_init.c				\
		ft_itos.c				\
		ft_parse.c				\
		ft_parse_bonus.c		\
		ft_str_utils.c			\
		ft_write.c				\
		ft_free.c				\
		ft_map_valid.c			\
		ft_map_utils.c			\
		ft_map_utils2.c			\
		ft_grid_utils.c			\
		ft_hooks.c				\
		ft_hooks2.c				\
		ft_flood.c				\

LIBFT_DIR = libft
LIBFT_FILE = $(LIBFT_DIR)/libft.a

LIBMLX = ./MLX42

LIB = -framework Cocoa -framework OpenGL -framework IOKit -L"/Users/${USER}/.brew/opt/glfw/lib/" -lglfw -lmlx42 -L. -lft
FLAGS = -Wall -Wextra -Werror 
HEADERS = -I $(LIBMLX)/include

NC=\033[0m
GREEN=\033[0;32m
RED=\033[0;31m

#LIBMLX 

all : $(NAME)

lib:
	@if [ ! -f libft.a ]; then \
		echo "Loading libft ...";\
		make -C $(LIBFT_DIR);\
		mv $(LIBFT_FILE) ./;\
	else \
		echo "$(GREEN)Libft already there.$(NC)";\
	fi
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

$(NAME) : lib
	@gcc $(FLAGS) $(SRC) -o $(NAME) $(LIB) $(HEADERS)

re : fclean $(NAME)

clean :
#	@rm -f $(OBJS)
	/bin/rm -f libft.a
	make -C $(LIBFT_DIR) clean

fclean : clean
	@if [ -d $(LIBMLX) ]; then \
		echo "Removing LIBMLX";\
		/bin/rm -rf $(LIBMLX);\
	fi
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(NAME_BONUS)

bonus : lib
	@gcc $(FLAGS) $(SRC_BONUS) -o $(NAME_BONUS) $(LIB) $(HEADERS)

test : $(NAME)
	./so_long maps/OmegaMap.ber
#	./so_long maps/maptest.ber
#	./so_long maps/blackhole.ber
#	./so_long_bonus maps/blackhole.ber

testb: bonus
	./so_long_bonus maps/small.ber
