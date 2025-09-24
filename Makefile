FILES			= main.c parsing/parsing.c parsing/parsing_map.c parsing/parsing_utils.c reading_data/read_data.c reading_data/read_map.c error/free.c initialisation/init.c initialisation/init_raycasting.c  player/key_events.c player/movements.c rendering/render_raycast.c rendering/utils_raycasting.c rendering/init_render_raycast.c rendering/drawing_func.c

FILESBONUS		= main.c parsing/parsing.c parsing/parsing_map.c parsing/parsing_utils.c reading_data/read_data.c reading_data/read_map.c error/free.c initialisation/init.c initialisation/init_raycasting.c minimap/drawing_onMinimap.c player/key_events.c player/movements.c rendering/render_raycast.c rendering/utils_raycasting.c rendering/init_render_raycast.c rendering/drawing_func.c minimap/contour_minimap.c

OBJS = $(addprefix $(OBJDIR)/, $(FILES:.c=.o))

OBJSBONUS = $(addprefix $(OBJDIRBONUS)/, $(FILESBONUS:.c=.o))

OBJDIR = mandatory/obj

OBJDIRBONUS = bonus/obj

# LIB FLAGS
LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

LIBMLX_DIR	= minilibx-linux

LIBMLX		= -Lmlx_linux -lmlx_Linux -L$(LIBMLX_DIR) -Imlx_linux -lX11 -lXext -lm -lz

# Include paths
INCLUDES	= -Iinclude -I$(LIBFT_DIR) -I$(LIBMLX_DIR)

NAME		= cub3d

NAMEBONUS	= cub3d_bonus

AR			= ar rc

RM			= rm -f

RANLIB		= ranlib

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

all:		${NAME}

.c.o:
	${CC} ${CFLAGS} -c ${INCLUDES} $< -o ${<:.c=.o}

${NAME}:	${OBJS} $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LIBMLX) -o $(NAME)

${NAMEBONUS}: ${OBJSBONUS} $(LIBFT)
	$(CC) $(CFLAGS) $(OBJSBONUS) -L$(LIBFT_DIR) -lft $(LIBMLX) -o $(NAMEBONUS)
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIRBONUS)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)



bonus:	${NAMEBONUS}

clean:
	@echo "\033[1;32m" "Cleaning .o \033[0m"
	@rm -rf $(OBJDIR)
	@make -C libft/ clean

fclean:		clean
	@echo "\033[1;32m" "Cleaning program \033[0m"
	@rm -f $(NAME)
	@rm -f $(NAMEBONUS)
	@make -C libft/ fclean

re:			fclean all

.PHONY:		all bonus clean fclean re