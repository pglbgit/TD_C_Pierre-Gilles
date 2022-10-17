TARGET_DW = dwApp
TARGET_CB = cbApp
all: $(TARGET_DW) $(TARGET_CB)

CC = gcc -std=c99
CFLAGS = -g 

OUTDIR = ./BinApp
DATADIR = $(OUTDIR)/data
SUBDIR_DW = ApplicationLayer/DigitalWheel \
	DomainLayer/DigitalWheel \
	DomainLayer/Generic \
	DomainLayer/Generator \
	InfrastructureLayer/DigitalWheel/FileDB \
	UserInterfaceLayer/DigitalWheel

SUBDIR_CB = ApplicationLayer/CircularBuffer \
	DomainLayer/CircularBuffer \
	DomainLayer/Generic \
	DomainLayer/Generator \
	InfrastructureLayer/CircularBuffer/FileDB \
	UserInterfaceLayer/CircularBuffer	
	
DIR_OBJ = $(OUTDIR)/obj

INCS_DW = $(wildcard *.h $(foreach fd, $(SUBDIR_DW), $(fd)/*.h))
INCS_CB = $(wildcard *.h $(foreach fd, $(SUBDIR_CB), $(fd)/*.h))
SRCS_DW = $(wildcard *.c $(foreach fd, $(SUBDIR_DW), $(fd)/*.c))
SRCS_CB = $(wildcard *.c $(foreach fd, $(SUBDIR_CB), $(fd)/*.c))
NODIR_SRC_DW = $(notdir $(SRCS_DW))
NODIR_SRC_CB = $(notdir $(SRCS_CB))

OBJS_DW = $(addprefix $(DIR_OBJ)/, $(SRCS_DW:c=o)) # obj/xxx.o obj/folder/xxx .o
OBJS_CB = $(addprefix $(DIR_OBJ)/, $(SRCS_CB:c=o)) # obj/xxx.o obj/folder/xxx .o
INC_DIRS_DW = -I./ $(addprefix -I, $(SUBDIR_DW))
INC_DIRS_CB = -I./ $(addprefix -I, $(SUBDIR_CB))

LIBS = 
LIB_DIRS = 


$(TARGET_CB):  $(OBJS_CB)
	$(CC) -o $(OUTDIR)/$@ $(OBJS_CB) $(LIB_DIRS) $(LIBS)
	
$(TARGET_DW): $(OBJS_DW)
	$(CC) -o $(OUTDIR)/$@ $(OBJS_DW) $(LIB_DIRS) $(LIBS)	
	
			
$(DIR_OBJ)/%.o: %.c $(INCS_CB) $(INCS_DW)
	mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $< $(INC_DIRS_CB) $(INC_DIRS_DW)

PHONY += clean
clean:
	rm -rf $(OUTDIR)/* $(DATADIR)/* $(DIR_OBJ)/*

PHONY += echoes
echoes:
    @echo "INC files: $(INCS)"
    @echo "SRC files: $(SRCS)"
    @echo "OBJ files: $(OBJS)"
    @echo "LIB files: $(LIBS)"
    @echo "INC DIR: $(INC_DIRS)"
    @echo "LIB DIR: $(LIB_DIRS)"


