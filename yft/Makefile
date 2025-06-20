# define standard colors
BOLD			= \033[1m
BLACK    		= \033[30m    # Black
RED      		= \033[31m    # Red
GREEN    		= \033[32m    # Green
YELLOW   		= \033[33m    # Yellow
BLUE     		= \033[34m    # Blue
MAGENTA  		= \033[35m    # Magenta
CYAN     		= \033[36m    # Cyan
WHITE    		= \033[37m    # White
LIGHT_RED		= \033[91m
LIGHT_GREEN		= \033[92m
LIGHT_CYAN		= \033[96m
RESET			= \033[0m

NAME			:= hpc.a
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

#adds stuff inside the outer libft
LIBFT			= $(shell find .. -type d -name "libft")
MLX_DIR			= $(shell find .. -type d -name "minilibx*")

#Linkers
LINKS			= -L/usr/lib -L$(MLX_DIR) -lXext -lX11 -lm -lz -lpthread

#Includes
INKS			= -I$(CURDIR) -I$(LIBFT) -I$(MLX_DIR)

ifeq ($(UNAME),Darwin)
	MLX			= $(MLX_DIR)/libmlx.a
	DEFS		= -D __APPLE__
	INKS		+= -I/usr/X11/include
	LINKS		+= -I/opt/homebrew/include -I/usr/X11/include -L/usr/X11/lib -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	DEFS		=
	INKS		+= -I/usr/include
	LINKS		+= -lmlx_Linux
else
	UNAME = Error
endif

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= main.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

VPATH 			= 

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

#-D DEBUG=1
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

$(LIBFT)libft.a:
	@$(MAKE) all -C $(LIBFT) --quiet

$(MLX):
	@rm -f $(MLX_DIR)/libmlx.a
	@$(MAKE) -C $(MLX_DIR) --quiet

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
#	@ar rcs $(LIBFT)libft.a $(LIBFT)$(OBJS_DIR)* $(OBJS_DIR)*

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)*

fclean: clean
	@rm -rf $(OBJS_DIR) $(NAME)

lre: clean all

re: fclean all