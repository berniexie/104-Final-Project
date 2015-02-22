
CC = g++
CFLAGS = -g -Wall
LDFLAGS =
SRCS = 	

rb_test : rb_test.cpp bst.h rbbst.h
	@echo "Compiling rb_test"
	$(CC) $(CFLAGS) rb_test.cpp -o rb_test

teams 	: teams.cpp
	@echo "Compiling teams"
	$(CC) $(CFLAGS) teams.cpp -o teams

.PHONY:	cleanrbtest cleanteams	

cleanrbtest:
	rm -f rb_test *~

cleanteams:
	rm -f teams *~

