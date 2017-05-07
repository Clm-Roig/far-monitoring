obj_dir=obj/
bin_dir=bin/
data_dir=data/
src_dir=src/
CC=gcc
CFLAGS=-Wall  -g
LDFLAGS= -g
EXEC=$(bin_dir)serverPosition.exe

all: $(EXEC)

$(bin_dir)serverPosition.exe: $(obj_dir)fils.o  $(obj_dir)main.o $(obj_dir)serveur.o  $(obj_dir)util.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(obj_dir)* $(bin_dir)*
	rm -f $(data_dir)pipes/*
	touch $(bin_dir)hello.c
	touch $(obj_dir)hello.c
	touch $(data_dir)pipes/hello.fifo

start:
	./$(bin_dir)serverPosition.exe
