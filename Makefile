SRC			= main.c parsing/parsing.c reading_data/read_data.c reading_data/read_map.c parsing/parsing_map.c error/free.c init.c

SRCS		= ${SRC}

OBJS		= ${SRCS:.c=.o}

# LIB FLAGS
LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

LIBMLX_DIR	= minilibx-linux

LIBMLX		= -Lmlx_linux -lmlx_Linux -L$(LIBMLX_DIR) -Imlx_linux -lX11 -lXext -lm -lz

# Include paths
INCLUDES	= -Iinclude -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

NAME		= cub3d

AR			= ar rc

RM			= rm -f

RANLIB		= ranlib

GCC			= gcc

CFLAGS		= 

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