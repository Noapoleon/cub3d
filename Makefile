# Project Structure
NAME	=	cub3d
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs
LIBDIR	=	libs

# Other
RM	=	rm -rf
# Colors
COL_FRONT	=	\033[44;37;1m
COL_BACK	=	\033[7m
COL_ERR		=	\033[41;37;5;1m
COL_OK		=	\033[32;1m
COL_RESET	=	\033[0m

# Files
SRCS	:=	main.c \
			setup.c \
			parser.c \
			utils.c \
			utils_error.c \
			test_code/display_utils.c
OBJS	:=	$(SRCS:.c=.o)
SRCS	:=	$(addprefix $(SRCDIR)/, $(SRCS))
OBJS	:=	$(addprefix $(OBJDIR)/, $(OBJS))
LIBS	:=	libft.a \
			libmlx.a
LIBS	:=	$(addprefix $(LIBDIR)/, $(LIBS))

# Compiler Options
CC		=	cc
#CFLAGS	=	-Wall -Wextra -Werror -MD
CFLAGS	=	-Wall -Wextra -Werror -MD -g -gdwarf-4
CINCS	=	-I./$(INCDIR) -I./$(LIBDIR)/libft -I./$(LIBDIR)/libmlx
CLIBS	=	-L./$(LIBDIR) -lm -lft -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(CLIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
	fi
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

$(LIBDIR)/%.a:
	make -C $(LIBDIR)/$(basename $(notdir $@))
	cp $(LIBDIR)/$(basename $(notdir $@))/$(notdir $@) $(LIBDIR)/

clean:
	$(RM) $(OBJDIR)
	make clean -C $(LIBDIR)/libft
	make clean -C $(LIBDIR)/libmlx

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBS)
	make fclean -C $(LIBDIR)/libft

re: fclean all

bonus: all

-include $(OBJS:.o=.d)

norm:
	@echo -e "$(COL_FRONT)              $(COL_RESET)"
	@echo -e "$(COL_FRONT)  LIBS NORM:  $(COL_BACK)  $(COL_RESET)"
	@echo -e "$(COL_FRONT)              $(COL_BACK)  $(COL_RESET)"
	@echo -e " $(COL_BACK)               $(COL_RESET)"
	@norminette $(LIBDIR)/libft | awk '{if ($$NF == "OK!") { print "$(COL_OK)"$$0"$(COL_RESET)" } else if ($$NF == "Error!") { print "$(COL_ERR)"$$0"$(COL_RESET)" } else { print }}'
	@echo -e "\n"
	@echo -e "$(COL_FRONT)              $(COL_RESET)"
	@echo -e "$(COL_FRONT)  SRCS NORM:  $(COL_BACK)  $(COL_RESET)"
	@echo -e "$(COL_FRONT)              $(COL_BACK)  $(COL_RESET)"
	@echo -e " $(COL_BACK)               $(COL_RESET)"
	@norminette $(SRCDIR) | awk '{if ($$NF == "OK!") { print "$(COL_OK)"$$0"$(COL_RESET)" } else if ($$NF == "Error!") { print "$(COL_ERR)"$$0"$(COL_RESET)" } else { print }}'
	@echo -e "\n"
	@echo -e "$(COL_FRONT)              $(COL_RESET)"
	@echo -e "$(COL_FRONT)  INCS NORM:  $(COL_BACK)  $(COL_RESET)"
	@echo -e "$(COL_FRONT)              $(COL_BACK)  $(COL_RESET)"
	@echo -e " $(COL_BACK)               $(COL_RESET)"
	@norminette $(INCDIR) | awk '{if ($$NF == "OK!") { print "$(COL_OK)"$$0"$(COL_RESET)" } else if ($$NF == "Error!") { print "$(COL_ERR)"$$0"$(COL_RESET)" } else { print }}'

.PHONY: all clean fclean re bonus norm
