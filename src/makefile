CC = gcc
CFLAGS = -Wall -Wswitch-enum -O2
LDFLAGS = -Wall -lfl 
EXEC = aps

OBJ = Ast.o Enum.o ASTParc.o Env.o Closure.o

$(EXEC): lex.yy.o $(EXEC).tab.o  $(OBJ)
	$(CC) -o as $^ $(LDFLAGS)

$(EXEC).tab.c $(EXEC).tab.h: $(EXEC).y
	bison -d -v $(EXEC).y

lex.yy.c: $(EXEC).lex $(EXEC).tab.h
	flex $(EXEC).lex

Ast.o: Ast.c Ast.h
	gcc -c $< $(CFLAGS)
	
ASTParc.o: ASTParc.c ASTParc.h Env.h
	gcc -c $< $(CFLAGS)
	
Env.o: Env.c Env.h
	gcc -c $< $(CFLAGS)	
	
Closure.o: Closure.c Closure.h
	gcc -c $< $(CFLAGS)	
	
Enum.o: Enum.c Enum.h
	gcc -c $< $(CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f as lex.yy.* *.tab.c *.tab.h *.tab.o $(EXEC) *.o

test:
	bash 
git:
	git add .
	git commit -m "new"
	git push -u origin master
