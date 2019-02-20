CC=gcc
newshell: MainShell.c
	$(CC) -o shell $(CFLAGS) MainShell.c
clean:
	$(RM) shell
