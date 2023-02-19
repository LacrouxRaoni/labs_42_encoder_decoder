NAME	=	decoder

SRC_DIR	=	sources
SHARE_PATH	=	../../ft_encoder/sources/

PATH_OBJ	=	objects

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror

RM	=	rm -rf

SRC_FILES	=	decoder.c\
				dc_memory_share.c\
				$(SHARE_PATH)memory.c\
				dc_huffman_list.c\
				dc_huffman_tree.c\
				decompress.c\
				dc_utils.c\
				log_data.c

INCLUDES	=	-I ./includes

SRC	=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ	=	$(SRC:$(SRC_FILES)/%.c=$(PATH_OBJ)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo done!!
	@$(CC) $(CFLAGS) $(OBJ) -g3 -o $(NAME) $(INCLUDES)

$(PATH_OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(PATH_OBJ)
	$(CC) $(CFLAGS) -g3 -o $@ $<

clean:
	@$(RM) $(PATH_OBJ)
	@echo obj removed

fclean: clean
	@$(RM) $(NAME)
	@echo clean everything

re: fclean all
