obj_dir=obj/
bin_dir=bin/
data_dir=data/
src_dir=src/
CC=gcc
CFLAGS=-Wall  -g
LDFLAGS= -g
EXEC=$(bin_dir)serverPosition.exe

all: $(EXEC)

$(bin_dir)serverPosition.exe: $(obj_dir)fils.o  $(obj_dir)main.o $(obj_dir)client.o  $(obj_dir)util.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(obj_dir)* $(bin_dir)serverPosition/exe
	touch $(obj_dir)objHolder

start:
	./$(bin_dir)serverPosition.exe
