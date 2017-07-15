# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/17 16:07:18 by fpasquer          #+#    #+#              #
#    Updated: 2017/07/01 09:15:44 by fpasquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_nm

SRC_NAME		= main.c init_flags.c del_nm.c loop_nm.c exe_nm.c func_32.c		\
				  func_32_cigan.c func_64.c func_64_cigan.c func_fat_cigam.c	\
				  func_fat_magic.c

INCLUDES		= ft_nm.h

LIBRARY			= libft/libft.a

OTHERS			= libft Makefile auteur

OTHER_FLAGS 	=

GCC				= gcc
CFLAGS			= -Wall -Wextra -Werror
OBJ_NAME		= $(SRC_NAME:.c=.o)

SRCDIR			= srcs
OBJDIR			= objs
INCDIR			= incs

SRC				= $(addprefix $(SRCDIR)/, $(SRC_NAME))
OBJ				= $(addprefix $(OBJDIR)/, $(OBJ_NAME))
INC				= $(addprefix $(INCDIR)/, $(INCLUDES))

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

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf $(OBJDIR)
	rm -rf $(LINK_NAME)
	make -C libft fclear

re : fclean All

norm:
	norminette $(SRC) $(INC) libft/*.[ch]
