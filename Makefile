NAME	=	caesar

SRC		=	CAESAR.cpp
		
#[ CMD ]########################################################################

CC		=	g++
RMV		=	rm -vf
RM		=	rm -f
ECHO	=	echo -e

#[ SYS ]########################################################################

OBJDIR	:=	obj
OBJS	:=	$(patsubst %,$(OBJDIR)/%.o,$(SRC))

VPATH	=	source

LDFLAGS += 
#LDFLAGS += ../DDS_LIB/obj/libsacppdds_vsm.a

ifeq ($(DEBUG), yes)
	CFLAGS	+= -O0
	CFLAGS	+= -g
	CFLAGS  += -DDEBUG_ON 
	CFLAGS  += -DVERBOSE 
else
	CFLAGS  += -O3
endif
CFLAGS	+=	-std=c++11
# CFLAGS	+=	-Wextra
CFLAGS	+=	-Wall
CFLAGS	+=	-Werror
# CFLAGS	+=	-W
CFLAGS	+=	-I include
# stop cflags
CFLAGS  +=  -c
# for dependencies
CFLAGS  +=  -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" 
DEPS	:=	$(OBJS:%.o=%.d)

#[ EXEC ]#######################################################################

$(NAME)	:   $(OBJS)
			@$(ECHO) "- - -"
			$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all		:	$(NAME)

$(OBJDIR)/%.o	:	%
	$(CC) $(CFLAGS) $< -o $@

$(OBJS)	:	| $(OBJDIR)

$(OBJDIR):
			mkdir -p $(OBJDIR)

clean	:
			@$(ECHO) "REMOVE..."
			@$(RMV) $(OBJS)
			@$(RMV) $(DEPS)

fclean	:	clean
			@$(RMV) $(NAME)
			@$(ECHO) "- - -"

re		:	fclean all

.PHONY	:	all $(OBJDIR)/%.o clean fclean re

################################################################################

-include   $(DEPS)
