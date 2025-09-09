mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3d");
			img = mlx_new_image(mlx, 1920, 1080);
			addr = mlx_get_data_addr(img, bit_p, size_line, endian);

			while (i < data->map->height_map)
			{
				j = 0;
				while (j < data->map->width_map)
				{
					k = 0;
					while (k < 10)
					{
						addr[(i * *size_line) + (j * 4)] = 10;
						k++;
					}
					j++;
				}
				i++;