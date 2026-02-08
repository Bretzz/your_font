NAME		:= your_demo
UNAME		:= $(shell uname)
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra

# Libraries
YFT			:= ../

#Linkers
LINKS			= -L/usr/lib -L$(MLX_DIR) -lXext -lX11 -lm -lz -lpthread

#Includes
INKS			= -I$(MLX_DIR) -I$(YFT)include

ifeq ($(UNAME),Darwin)
	MLX_DIR		= minilibx_opengl
	MLX			= $(MLX_DIR)/libmlx.a
	CLONE		= curl https://cdn.intra.42.fr/document/document/34410/minilibx_macos_opengl.tgz --output $(MLX_DIR).tgz \
				&& tar -xf $(MLX_DIR).tgz && rm -f $(MLX_DIR).tgz \
				&& ls $(MLX_DIR) || mv `ls | grep $(MLX_DIR)` $(MLX_DIR)
	DEFS		= -D __APPLE__
	INKS		+= -I/usr/X11/include
	LINKS		+= -I/opt/homebrew/include -I/usr/X11/include -L/usr/X11/lib -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLX_DIR		= minilibx-linux
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	CLONE		= git clone https://github.com/42paris/minilibx-linux.git
	DEFS		=
	INKS		+= -I/usr/include
	LINKS		+= -lmlx_Linux
else
	UNAME = Error
endif

SRCS	:= test.c
OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

$(YFT)yft.a:
	@make -C ../ --quiet

$(MLX_DIR):
	@echo "${BOLD}creating $(MLX_DIR)...${RESET}"
	$(CLONE) && $(MAKE) -C $(MLX_DIR)

$(MLX): $(MLX_DIR)
	@rm -f $(MLX_DIR)/libmlx.a
	@$(MAKE) -C $(MLX_DIR) --quiet

$(NAME): $(MLX) $(YFT)yft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(YFT)yft.a $(MLX) $(INKS) $(LINKS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -rf $(MLX_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re

