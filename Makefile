SRC			= main.c parsing/parsing.c

SRCS		= ${SRC}

OBJS		= ${SRCS:.c=.o}

# LIB FLAGS
LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

LIBMLX_DIR	= minilibx-linux

LIBMLX		= -L$(LIBMLX_DIR) -lmlx_Linux -lX11 -lXext

# Include paths
INCLUDES	= -Iinclude -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

NAME		= cub3d

AR			= ar rc

RM			= rm -f

RANLIB		= ranlib

GCC			= gcc

CFLAGS		= -Wall -Werror -Wextra -g

all:		${NAME}

.c.o:
	${GCC} ${CFLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

${NAME}:	${OBJS} $(LIBFT)
	$(GCC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LIBMLX) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} ${NAME}
	$(MAKE) -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re