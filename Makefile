MAKEFLAGS += -s

NAME = cub3d

INCLUDE = includes
INCLUDE_B = includes/bonus -I $(INCLUDE)
SRC_DIR = mandatory
BONUS_DIR = bonus
OBJ_DIR = objs
OBJ_BONUS_DIR = objs_bonus/

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx_Linux.a

CC = cc
FLAGS = -Wall -Wextra -Werror -g -O3
MLX_FLAGS = -lX11 -lXext -lm

FILES = main.c \
		free.c \
		player.c \
		set_mlx.c \
		controls.c \
		printing.c \
		treat_map.c \
		treat_file.c \
		treat_file_utils.c \
		store_image.c \
		display_utils.c \
		hooks.c \
		treat_map_utils.c \
		get_wall_dist.c \
		draw_texture.c \
		raycast.c

FILES_BONUS = main.c \
		\
		player/player.c \
		player/controls.c \
		player/display_stats.c \
		\
		mlx/hooks.c \
		mlx/set_mlx.c \
		\
		map_treatement/treat_map.c \
		map_treatement/treat_map_utils.c \
		map_treatement/treat_file.c \
		map_treatement/get_tiles.c \
		map_treatement/check_elems.c \
		map_treatement/treat_file_utils.c \
		\
		draw/store_image.c \
		draw/draw_texture.c \
		draw/draw_sprites.c \
		draw/get_wall_dist.c \
		draw/draw_ceil_and_floor.c \
		\
		entities/create_entity.c \
		entities/update_entities.c \
		\
		raycast/raycast.c \
		\
		utils/free.c \
		utils/libft.c \
		utils/printing.c \
		utils/display_utils.c \
		utils/raycast_utils.c

OBJS = $(FILES:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(FILES_BONUS:%.c=$(OBJ_BONUS_DIR)/%.o)

RM = rm -f

CYAN = "\033[36m"
RED    = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"

all: $(NAME)
#all : bonus

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo $(CYAN)"Compiling Cub3D..."$(RESET)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX) -I $(INCLUDE) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(LIBFT_DIR)/includes -o $(NAME) $(MLX_FLAGS)
	@echo $(GREEN)"$(NAME) executable created !"$(RESET)

bonus : $(LIBFT) $(MLX) $(OBJS_BONUS)
	@echo $(CYAN)"Compiling Cub3D..."$(RESET)
	@$(CC) $(FLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX) -I $(INCLUDE_B) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(LIBFT_DIR)/includes -o $(NAME) $(MLX_FLAGS)
	@echo $(GREEN)"$(NAME) executable created !"$(RESET)

$(LIBFT):
	@echo -n $(CYAN)"Compiling libft..."$(RESET)
	@make -C $(LIBFT_DIR) > /dev/null
	@echo $(GREEN)"\nLibft ready !"$(RESET)

$(MLX):
	@echo -n $(CYAN)"Compiling libmlx..."$(RESET)
	@make -C $(MLX_DIR) > /dev/null
	@echo $(GREEN)"\nLibmlx ready !"$(RESET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -I $(INCLUDE_B) -I $(LIBFT_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR) -c $< -o $@

clean:
	@echo $(GREEN)"Objets files cleared !"$(RESET)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_BONUS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo $(GREEN)"Libft cleared !"$(RESET)
	#@make -C $(LIBFT_DIR) fclean > /dev/null
	@echo $(GREEN)"$(NAME) cleared !"$(RESET)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re