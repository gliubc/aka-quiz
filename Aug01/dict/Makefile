all:dict

dict:list.o dict.o
	gcc -g $^ -o $@

list.o:list.c
	gcc -g -c $< -o $@

dict.o:dict.c
	gcc -g -c $< -o $@

clean:
	-rm -f *.o dict

.PHONY:clean
