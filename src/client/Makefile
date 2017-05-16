obj_dir=obj/
bin_dir=bin/
data_dir=data/
src_dir=src/
CC=gcc
CFLAGS=-Wall  -g
LDFLAGS= -g
EXEC=$(bin_dir)serveurRobotPosition.exe

all: $(EXEC)

$(bin_dir)serveurRobotPosition.exe: $(obj_dir)serveurRobotPosition.o  $(obj_dir)serveurRobotPositionUtil.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(obj_dir)* $(bin_dir)*
	touch $(bin_dir)binHolder
	touch $(obj_dir)objHolder

start:
	./$(bin_dir)serveurRobotPosition.exe
