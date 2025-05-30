MAKEFLAGS += -s

NAME = cub3d

INCLUDE = includes
SRC_DIR = mandatory
BONUS_DIR = bonus
OBJ_DIR = objs
OBJ_BONUS_DIR = objs_bonus/

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX = $(MLX_DIR)/libmlx_Linux.a

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Ofast
MLX_FLAGS = -lX11 -lXext -lm

FILES	 =  main.c \
			free.c \
			hooks.c \
			player.c \
			raycast.c \
			set_mlx.c \
			controls.c \
			printing.c \
			treat_map.c \
			treat_file.c \
			store_image.c \
			draw_texture.c \
			display_utils.c \
			get_wall_dist.c \
			treat_file_utils.c

FILES_BONUS = main.c \
			  free.c \
			  hooks.c \
			  libft.c \
			  player.c \
			  raycast.c \
			  minimap.c \
			  set_mlx.c \
			  controls.c \
			  printing.c \
			  treat_map.c \
			  treat_file.c \
			  store_image.c \
			  draw_texture.c \
			  draw_sprites.c \
			  display_utils.c \
			  get_wall_dist.c \
			  raycast_utils.c \
			  create_entity.c \
			  update_entities.c \
			  treat_file_utils.c

OBJS = $(FILES:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(FILES_BONUS:%.c=$(OBJ_BONUS_DIR)/%.o)

RM = rm -f

CYAN = "\033[36m"
RED    = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"

#all: $(NAME)
all : bonus

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo $(CYAN)"Compiling Cub3D..."$(RESET)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX) -I $(INCLUDE) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(LIBFT_DIR)/includes -o $(NAME) $(MLX_FLAGS)
	@echo $(GREEN)"$(NAME) executable created !"$(RESET)

bonus : $(LIBFT) $(MLX) $(OBJS_BONUS)
	@echo $(CYAN)"Compiling Cub3D..."$(RESET)
	@$(CC) $(FLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX) -I $(INCLUDE) -I $(MLX_DIR) -I $(LIBFT_DIR) -I $(LIBFT_DIR)/includes -o $(NAME) $(MLX_FLAGS)
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
	@mkdir -p $(OBJ_BONUS_DIR)
	@$(CC) $(FLAGS) -I $(INCLUDE) -I $(LIBFT_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR) -c $< -o $@

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
