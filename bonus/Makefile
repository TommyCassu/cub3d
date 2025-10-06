FILES			=	main.c \
					error/free_utils.c \
					error/free.c \
					initialisation/init.c \
					initialisation/init_raycasting.c \
					minimap/contour_minimap.c \
					minimap/drawing_onMinimap.c \
					parsing/parsing_map.c \
					parsing/parsing_utils.c \
					parsing/parsing.c \
					player/key_events.c \
					player/movements.c \
					reading_data/read_data.c \
					reading_data/read_map.c \
					door/init_doors.c \
					door/utils_doors.c \
					rendering/drawing_func.c \
					rendering/init_render_raycast.c \
					rendering/render_raycast.c \
					rendering/utils_raycasting.c \

SRCS		= ${SRC}

OBJS = $(addprefix $(OBJDIR)/, $(FILES:.c=.o))

OBJDIR = obj

# LIB FLAGS
LIBFT_DIR	= ../libft

LIBFT		= $(LIBFT_DIR)/libft.a

LIBMLX_DIR	= ../minilibx-linux

LIBMLX		= -Lmlx_linux -lmlx_Linux -L$(LIBMLX_DIR) -Imlx_linux -lX11 -lXext -lm -lz

# Include paths
INCLUDES	= -Iinclude -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

NAME		= ../cub3d_bonus

AR			= ar rc

RM			= rm -f

RANLIB		= ranlib

CC			= cc

CFLAGS		= 

all:		${NAME}

.c.o:
	${CC} ${CFLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LIBMLX) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[1;32m" "Cleaning .o \033[0m"
	@rm -rf $(OBJDIR)

fclean:		clean
	@echo "\033[1;32m" "Cleaning program \033[0m"
	@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re