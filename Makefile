# Project Structure
NAME	=	cub3d
SRCDIR	=	srcs
OBJDIR	=	objs
INCDIR	=	incs
LIBDIR	=	libs

# Other
RM	=	rm -rf

# Files
SRCS	:=	main.c
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

.PHONY: all clean fclean re bonus
