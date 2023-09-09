all: program.c database.c kaydet.c
	cc -o program program.c
	cc -o database database.c
	cc -o kaydet kaydet.c