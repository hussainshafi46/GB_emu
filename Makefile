INCLUDEDIR = include
LIBDIR = libs
OBJDIR = build

TARGET = gbemu

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    EMU_LIB_NAME = libemulator.so
    LD_FLAGS = -L$(OBJDIR) -Wl,-rpath=. -lemulator 
else ifeq ($(UNAME), Darwin)
    EMU_LIB_NAME = libemulator.dylib
    LD_FLAGS = -L$(OBJDIR) -Wl,-rpath,. -lemulator
else
    EMU_LIB_NAME = libemulator.dll
    LD_FLAGS = -L$(OBJDIR) -lemulator
endif

EMU_LIB = $(OBJDIR)/$(EMU_LIB_NAME)

MAIN_SOURCE = main.c
LIB_SOURCES = $(wildcard $(LIBDIR)/*.c)

LIB_OBJECTS = $(patsubst $(LIBDIR)/%.c,$(OBJDIR)/%.o,$(LIB_SOURCES))
MAIN_OBJECT = $(patsubst %.c,$(OBJDIR)/%.o,$(MAIN_SOURCE))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDEDIR)
LDFLAGS = $(LD_FLAGS)

.PHONY: all clean
all: $(TARGET)

# Ensure build directory exists
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIB_OBJECTS): $(OBJDIR)/%.o: $(LIBDIR)/%.c | $(OBJDIR)
	@echo "--> Compiling library source $< -> $@"
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(EMU_LIB): $(LIB_OBJECTS)
	@echo "--> Building Shared Library: $@"
	$(CC) -shared $(LIB_OBJECTS) -o $@

$(MAIN_OBJECT): $(MAIN_SOURCE) | $(OBJDIR)
	@echo "--> Compiling main source $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(MAIN_OBJECT) $(EMU_LIB)
	@echo "--> Linking executable: $@"
	$(CC) $(MAIN_OBJECT) $(LDFLAGS) -o $@
	
	@cp $(EMU_LIB) .

clean:
	@echo "--> Cleaning up build directory ($(OBJDIR)), executable ($(TARGET)), and library ($(EMU_LIB_NAME))"
	@-rm -rf $(OBJDIR)
	@-rm -f $(TARGET) $(EMU_LIB_NAME)