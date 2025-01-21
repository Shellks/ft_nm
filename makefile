NAME = ft_nm

CFLAGS = -Wall -Wextra -Werror

CC = gcc

HEADER_PATH = include/
SRCS_DIR = srcs/
OBJS_DIR = .objs/
LIBFT = srcs/utils/libft/libft.a

SRCS =	ft_nm.c \
		parser.c \
		utils/parser_utils.c \
		utils/file_list_utils.c \
		utils/ft_perror.c \
		file_manager.c \
		ft_exit.c

OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR)
	${CC} ${CFLAGS} -I ${HEADER_PATH} -MMD -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS} | $(LIBFT)
	echo "\033[1;34mCreating ft_nm.."
	${CC} ${CFLAGS} ${OBJS} $(LIBFT) -o ${NAME}
	echo "\033[1;32mSuccess!\033[1;33m"

clean:
	echo "\033[1;31mCleaning All objects.."
	$(MAKE) clean -C srcs/utils/libft
	rm -rf ${OBJS_DIR}

fclean: clean
	echo "\033[1;31mCleaning executable.."
	$(MAKE) fclean -C srcs/utils/libft
	rm -f ${NAME}

re: fclean all

# Compiling the libft.a library
$(LIBFT): force
	$(MAKE) -C srcs/utils/libft

# Creating the necessary directories
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)utils

force: 

-include $(OBJS:.o=.d)

.SILENT:

.PHONY: all clean fclean re