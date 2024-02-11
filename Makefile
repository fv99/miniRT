# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvonsovs <fvonsovs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 18:06:10 by fvonsovs          #+#    #+#              #
#    Updated: 2024/02/11 19:42:12 by fvonsovs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g
NAME		=	miniRT
SRCS		=	minirt.c 
OBJS		=	${SRCS:.c=.o}
LIBC		=	ar -cq
RM			=	rm -f
LIBFT		=	./libft/libft.a
MINILIBX	=	./minilibx-linux/libmlx.a

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
	make -C ./minilibx-linux
	@echo "$(YELLOW)Linking objects...$(RESET)"
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${MINILIBX} -L/usr/lib -lm -lXext -lX11
	@echo "$(GREEN)Compilation successful.$(RESET)"

clean: 
	@echo "$(YELLOW)Removing object files...$(RESET)"
	@${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	@echo "$(YELLOW)Removing executable...$(RESET)"
	@${RM} ${NAME} ${BONUS_NAME}

re: fclean all

.PHONY:	all clean fclean re