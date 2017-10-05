# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/17 16:07:18 by fpasquer          #+#    #+#              #
#    Updated: 2017/10/05 17:02:11 by fpasquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_otool

SRC_NAME		= main.c ft_otool.c util.c exe_otool.c func_32.c func_64.c		\
				  func_fat.c print_segments.c

INCLUDES		= ft_otool.h

LIBRARY			= libft/libft.a

OTHERS			= libft Makefile auteur

OTHER_FLAGS 	=

GCC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g -std=c89
CFLAGS_32		= -m32
OBJ_NAME		= $(SRC_NAME:.c=.o)

SRCDIR			= srcs
OBJDIR			= objs
INCDIR			= incs

SRC				= $(addprefix $(SRCDIR)/, $(SRC_NAME))
OBJ				= $(addprefix $(OBJDIR)/, $(OBJ_NAME))
INC				= $(addprefix $(INCDIR)/, $(INCLUDES))

#partie 32bits
NAME_32bits		= $(NAME)_32
LIBRARY_32		= libft/libft_32.a
OBJDIR_32		= $(OBJDIR)_32
OBJ_32			= $(addprefix $(OBJDIR_32)/, $(OBJ_NAME))

All : $(NAME)

$(NAME) : $(OBJDIR) $(OBJ) $(LIBRARY)
	$(GCC) $(CFLAGS) $(OTHER_FLAGS) -o $(NAME) $(OBJ) $(LIBRARY)
	@echo "\033[0;32m"$(NAME) "DONE\033[0m"

$(LIBRARY) :
	@echo "\033[0;32mCOMPILE LIBFT\033[0m"
	make -C libft

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INC)
	$(GCC) -I $(INCDIR)/ $(CFLAGS) -o $@ -c $<

$(OBJDIR) : 
	mkdir -p $(OBJDIR)

32bis : $(OBJDIR_32) $(OBJ_32) $(LIBRARY_32)
	$(GCC) $(CFLAGS) $(CFLAGS_32) $(OTHER_FLAGS) -o $(NAME_32bits) $(OBJ_32) $(LIBRARY_32)
	@echo "\033[0;32m"$(NAME_32bits) "DONE\033[0m"

$(LIBRARY_32) :
	@echo "\033[0;32mCOMPILE LIBFT_32bits\033[0m"
	make 32bis -C libft

$(OBJDIR_32)/%.o : $(SRCDIR)/%.c $(INC)
	$(GCC) -I $(INCDIR)/ $(CFLAGS) $(CFLAGS_32) -o $@ -c $<

$(OBJDIR_32) : 
	mkdir -p $(OBJDIR_32)

clean :
	rm -rf $(OBJ)
	rm -rf $(OBJ_32)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME_32bits)
	rm -rf $(NAME).dSYM
	rm -rf $(NAME_32bits).dSYM
	rm -rf $(OBJDIR)
	rm -rf $(OBJDIR_32)
	make -C libft fclear

re : fclean All

norm:
	norminette $(SRC) $(INC) libft/*.[ch]