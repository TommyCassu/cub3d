/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcassu <tcassu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:55:54 by tcassu            #+#    #+#             */
/*   Updated: 2025/10/01 22:35:30 by tcassu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define RES_X 1920
# define RES_Y 1080
# define RES_MMAP_X 256
# define RES_MMAP_Y 256
# define TILES_MINIMAP_SIZE 8
# define KEY_UP 1
# define KEY_DOWN 2
# define KEY_LEFT 3
# define KEY_RIGHT 4
# define KEY_W 5
# define KEY_S 6
# define KEY_A 7
# define KEY_D 8
# define KEY_JUMP 9
# define TEXT_SIZE 128
# define numSprites 19

typedef struct s_img
{
	void	*ptr;
	int		*addr;
	int		line_s;
	int		bpp;
	int		endian;
}			t_img;

typedef struct s_textdata
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
	t_img	*img[6];
}			t_textdata;

typedef struct s_player
{
	double	x;
	double	y;
	double	start_x;
	double	start_y;
	double	dir_x;
	double	dir_y;
	int		isjumping;
	double	jumpspeed;
	double	jumpoffset;
}			t_player;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		texture;
}			t_sprite;

typedef struct s_game
{
	double	time;
	double	oldtime;
	double	plane_x;
	double	plane_y;
	double	raydir_x;
	double	raydir_y;
	double	camera_x;
	double	movespeed;
	double	rotspeed;
	int		map_y;
	int		map_x;
	double	side_dist_y;
	double	side_dist_x;
	double	perp_wall_dist;
	double	delta_dist_y;
	double	delta_dist_x;
	int		text_num;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		head_view;
	int		key_tab[32];
	double	ray_dir_x0;
	double	ray_dir_y0;
	double	ray_dir_x1;
	double	ray_dir_y1;
	double	pos_z;
	int		p;
	int		color;
	float	row_distance;
	double	floor_x;
	double	floor_y;
	double	floor_step_y;
	double	floor_step_x;
	double	old_dir_x;
	double	old_plane_x;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		jumpoffsetresy;
	t_img	*img_minimap;
	t_img	*img_minimap_contour;
	t_sprite sprite[numSprites];
	int		tab_contour[256][256];
	double	frametime;
}			t_game;

typedef struct s_map
{
	char		**map_tab;
	t_player	*player;
	t_textdata	*textdata;
	int			floor_rgb;
	int			ceilling_rgb;
	int			height_map;
	int			width_map;
}				t_map;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	*img;
}			t_mlx;

typedef struct s_data
{
	t_map	*map;
	t_mlx	*mlx;
	t_game	*game;
	int		error_status;
}			t_data;

/* --- error --- */
/* free_utils.c */
void	free_map(t_map *map);
void	ft_free_map(t_data *data);
void	ft_free_imgs(t_data *data);
void	ft_free_mlx(t_data *data);
/* free.c */
int		ft_exit(void *param);
void	ft_free_cub3d(t_data *data);
void	ft_free(char **result);
/* --- initialisation --- */
/* init_raycasting.c */
void	init_raycast(t_data *data);
void	setup_text_img(t_data *data, t_textdata *textdata);
/* init.c */
void	init_tab_contour(t_data *data);
void	init_data(t_data *data);
void	init_mlx(t_mlx *mlx, t_data *data);
/* --- Parsing --- */
/* parsing_map.c */
int		spawn_count_is_1(int spawn_count);
int		check_spawn(t_map *map, int height, int width);
int		is_map_closed(char **map, int height, int width);
int		parsing_map(t_map *map);
/* parsing_utils.c */
int		is_player(char c);
int		is_valid(char c);
int		ft_verif_digit(char *str);
/* parsing.c */
int		check_valid_file(char *line);
int		parsing_texture(t_textdata *textures);
void	attribute_rgb(t_data *data, char **tab_value, char *direction);
void	parsing_rgb(t_data *data, char *line, char *direction);
int		parsing(t_data *data);
/* --- Player --- */
/* key_events.c */
int		key_press(int key, t_data *data);
int		key_release(int key, t_data *data);
void	turn_right(t_game *game, t_player *player);
void	turn_left(t_game *game, t_player *player);
int		key_handler(t_data *data, t_game *game, t_player *player);
/* movement.c */
int		go_forward(t_data *data, t_player *player);
int		go_backward(t_data *data, t_player *player);
int		go_right(t_data *data, t_player *player);
int		go_left(t_data *data, t_player *player);
void	move_head(t_game *game, t_player *player);
/* --- reading_data --- */
/* read_data.c */
void	config_memory(t_data *data, char *line, char *direction);
int		add_data(t_data *data, char *line);
void	malloc_map(t_map *map);
void	read_data(t_data *data, char *filename);
/* read_map.c */
int		is_map_line(char *line);
void	read_map(t_map *map, char *line);
void	write_line(t_map *map, char *line, int *i);
void	write_map(t_map *map, char *filename);
/* --- Rendering --- */
/* drawing_func */
void	pixels_to_image(t_data *data, int x, int y, int pixcolor);
void	draw_ceiling(t_data *data, t_game *game, int x, int color);
void	init_floor_params(t_data *data, t_game *game, int y);
void	draw_floor(t_data *data, t_game *game, t_map *map);
/* init_render_raycast */
void	init_ray(t_data *data, int x);
void	setup_angle_rayon(t_data *data);
void	dda_loop(t_data *data);
void	manage_draw_limits(t_data *data);
/* render_raycast */
void	get_texture_pos(t_data *data);
void	draw_wall_col(t_data *data, int x);
void	select_texture_side(t_game *game);
void	render_raycast(t_data *data, t_game *game);
void	calcul_jump_offset(t_data *data);
/* Utils_raycasting */
int		get_pixel(t_img *image, int x, int y);
long	get_time(void);
void	show_fps(t_data *data);
/* --- Minimap --- */
/* contour_minimap.c */
int		is_minimap_status(t_data *data, int x, int y);
void	pixels_to_image_minimap_player(t_data *data, int x, int y,
			int pixcolor);
void	write_contour_minimap(t_data *data);
/* drawing_onMinimap.c */
void	draw_player_minmap(t_data *data);
void	draw_cube_wall(t_data *data, int x, int y);
void	draw_cube_floor(t_data *data, int x, int y);
void	draw_cube_outside(t_data *data);
void	draw_mini_map(t_data *data);
/* --- Main.c --- */
void	print_map(t_map *map);
int		test_rend(t_data *data);
void	setup_minimap(t_data *data);

// void    transpose_test(t_mlx *mlx, t_img *img, int w, int h);
#endif