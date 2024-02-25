
OBJECTS_MAIN = main.o StrList.o 

CFlags = -Wall -Wextra -g

prograbola : $(OBJECTS_MAIN)
	gcc $(CFlags) -o $@ $^

StrList.o : StrList.h # adding a dependency to the h file!

%.o: %.c
	gcc $(CFlags) -c -o $@ $<

clean:
	rm *.o prograbola