NAME			:= yft.a
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= yft_is_better.c \
				yft_string_put.c \
				\
				yft_draw_ascii.c \
				yft_fill_font.c \
				yft_fill_map.c \
				yft_monoline_file.c \
				yft_parse_file.c \
				yft_read_file.c \
				yft_strip_comments.c \
				\
				fill_spacing.c \
				\
				yft_libft.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))


all: $(NAME)
	@rm -rf $(OBJS_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

#-D DEBUG=1
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)*

fclean: clean
	@rm -rf $(OBJS_DIR) $(NAME)

lre: clean all

re: fclean all

.PHONY: all clean fclean re lre tar