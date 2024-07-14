# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvonsovs <fvonsovs@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 18:06:10 by fvonsovs          #+#    #+#              #
#    Updated: 2024/06/27 13:20:41 by fvonsovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
NAME		=	miniRT
SRCS		=	minirt.c controls.c parser.c parser_scene.c parser_objects.c render.c \
				utils_tests.c utils_mem.c utils_number.c utils_parser.c utils_array.c \
				utils_vec.c utils_vec2.c utils_win.c
OBJS		=	${SRCS:.c=.o}
LIBC		=	ar -cq
RM			=	rm -f
LIBFT		=	./libft/libft.a
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	CFLAGS		+=	-fsanitize=address -g
	LDFLAGS		+=	-fsanitize=address -g
	MINILIBX	=	./minilibx-linux/libmlx.a
	LIBS		=	-lm -lXext -lX11
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS		+=	-fsanitize=address -g -I/usr/local/opt/readline/include
	LDFLAGS		+=	-lSystem -fsanitize=address -g -L/usr/local/opt/readline/lib
	MINILIBX	=	./minilibx-mac-osx/libmlx.a
	LIBS		=	-framework OpenGL -framework AppKit
endif

# Colors
GREEN		=	$(shell printf "\033[0;32m")
YELLOW		=	$(shell printf "\033[0;33m")
RESET		=	$(shell printf "\033[0m")

.c.o:
	@echo "$(YELLOW)Compiling: $(GREEN)$<$(RESET)"
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I. -I./libft -I/usr/include -I./minilibx-linux -O3

all: $(NAME)

$(NAME): ${OBJS}
	@echo "$(YELLOW)Compiling libraries...$(RESET)"
	make -C ./libft
ifeq ($(UNAME_S),Linux)
#	make -C ./minilibx-linux
endif
ifeq ($(UNAME_S),Darwin)
	make -C ./minilibx-mac-osx
endif
	@echo "$(YELLOW)Linking objects...$(RESET)"
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${MINILIBX} ${LIBS}
	@echo "$(GREEN)Compilation successful.$(RESET)"

clean: 
	@echo "$(YELLOW)Removing object files...$(RESET)"
	@${RM} ${OBJS}

fclean: clean
	@echo "$(YELLOW)Removing executable...$(RESET)"
	@${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re
