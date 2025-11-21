## Working maps : 

### white spaces : 
1. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_0.cub
3. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_1.cub
5. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_2.cub
7. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_3_only_spaces.cub
9. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_4_only_tabs.cub
2. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_5_mixed.cub           
4. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_6_W_before_textures.cub
6. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_7_W_before_colors.cub
8. LC_ALL=C valgrind ./cub3d ./maps/good/whitespaces_8_before_after_c_t.cub

---
## Test related to player : 

### Working player : 
...

### Bug in player :
1.	LC_ALL=C valgrind ./cub3d ./maps/bad/wall_hole_east.cub
2.	LC_ALL=C valgrind ./cub3d ./maps/bad/wall_hole_north.cub
3.	LC_ALL=C valgrind ./cub3d ./maps/bad/wall_hole_south.cub
4.	LC_ALL=C valgrind ./cub3d ./maps/bad/wall_hole_west.cub
5.	LC_ALL=C valgrind ./cub3d ./maps/bad/wall_none.cub

---
## Test related to player : 

### Working player : 
...

### Bug in player :
1.	LC_ALL=C valgrind ./cub3d ./maps/bad/player_multiple.cub
2.	LC_ALL=C valgrind ./cub3d ./maps/bad/player_none.cub
3.	LC_ALL=C valgrind ./cub3d ./maps/bad/player_on_edge.cub

---
## Test related to file : 

### Working file : 
...

### Bug in file : 
1.	LC_ALL=C valgrind ./cub3d ./maps/bad/file_letter_end.cub
2.	LC_ALL=C valgrind ./cub3d ./maps/bad/file_type_missing
3.	LC_ALL=C valgrind ./cub3d ./maps/bad/file_type_wrong.buc

---
## Test related to map : 

### Working file : 
1. LC_ALL=C valgrind ./cub3d ./maps/good/map_holes.cub

### Bug in file : 
1. LC_ALL=C valgrind ./cub3d ./maps/bad/map_hole.cub
2. LC_ALL=C valgrind ./cub3d ./maps/bad/map_middle.cub
3. LC_ALL=C valgrind ./cub3d ./maps/bad/map_missing.cub
4. LC_ALL=C valgrind ./cub3d ./maps/bad/map_no_1.cub
5. LC_ALL=C valgrind ./cub3d ./maps/bad/map_only_1.cub
6. LC_ALL=C valgrind ./cub3d ./maps/bad/map_only.cub
7. LC_ALL=C valgrind ./cub3d ./maps/bad/map_too_small.cub

---
## Test related to textures : 

### Working file : 
...

### Bug in file : 

1.	LC_ALL=C valgrind ./cub3d ./maps/bad/textures_bad_extention.cub
2.	LC_ALL=C valgrind ./cub3d ./maps/bad/textures_forbidden.cub
3.	LC_ALL=C valgrind ./cub3d ./maps/bad/textures_none.cub
4.	LC_ALL=C valgrind ./cub3d ./maps/bad/textures_dir.cub
5.	LC_ALL=C valgrind ./cub3d ./maps/bad/textures_invalid.cub
6.	LC_ALL=C valgrind ./cub3d ./maps/bad/textures_not_xpm.cub
7.	LC_ALL=C valgrind ./cub3d ./maps/bad/textures_duplicates.cub
8.	LC_ALL=C valgrind ./cub3d ./maps/bad/textures_S_missing.cub

---
## Test related to colors : 

### Working file : 

-	LC_ALL=C valgrind ./cub3d ./maps/good/colors_test_1.cub
-	LC_ALL=C valgrind ./cub3d ./maps/good/colors_test_2.cub
-	LC_ALL=C valgrind ./cub3d ./maps/good/colors_test_3.cub


### Bug in file : 

#### 	Duplicated 
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_ceiling_duplicated.cub
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_floor_duplicated.cub

####	Invalid amounts
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_invalid_rgb_amount_nbs.cub

####	Inputed amount
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_invalid_rgb_big_int.cub
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_invalid_rgb_negtive.cub

####	Missing 
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_missing_ceiling_color.cub
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_missing.cub
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_missing_floor_color.cub
- LC_ALL=C valgrind ./cub3d ./maps/bad/color_none.cub