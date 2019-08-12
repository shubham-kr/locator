LOCAL_PATH := $(call my-dir)
PROJ_DIR=../..
CC=gcc
AR=ar
CFLAGS=-c -fPIC -fno-builtin -g -O3
LDFLAGS= -Xlinker -Map=locator_linux.map

SOURCEDIR_MAIN=../../source/  

SOURCES=\
../../source/lc_filter.c \
../../source/lc_locatorApp.c \
../../source/lc_matInvGJE.c \
../../source/lc_parser.c \
../../source/lc_position.c \
../../source/lc_reports.c \
../../source/lc_scenario.c \
../../source/lc_signalMeas.c \
../../source/lc_trace.c \
../../source/lc_wls.c

INCLUDE=\
-I$(PROJ_DIR)/source

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=locator_linux.exe

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ -lm 
#	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@ -lm 

main.o:$(PROJ_DIR)/source/lc_locatorApp.c
	$(CC) $(INCLUDE)   $(CFLAGS) $(PROJ_DIR)/source/lc_locatorApp.c

%.o:%.c
	$(CC)  $(INCLUDE)  $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)