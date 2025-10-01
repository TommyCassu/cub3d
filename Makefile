NAME		= cub3d

NAME		= cub3d_bonus

all:
	$(LIBFT)
	make -C mandatory
	make -C bonus

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "\033[1;32m" "Cleaning .o \033[0m"
	@make -C mandatory clean
	@make -C bonus clean
	@make -C libft/ clean

fclean:
	@echo "\033[1;32m" "Cleaning program \033[0m"
	@make -C mandatory fclean
	@make -C bonus fclean
	@make -C libft/ clean

re:			fclean all

.PHONY:		all clean fclean re