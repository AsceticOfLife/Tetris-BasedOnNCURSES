cc = g++
prom = tetris
deps1 = ./Mytetris/mytetris.h
deps2 = ./Mytetris/chunk.h

RM = cmd /c del

obj = code.o mytetris.o chunk.o

# 繁琐的写法
$(prom) : $(obj)
	$(cc) -o $(prom) $(obj) -L ./lib -l ncursesw

code.o : code.cpp
	$(cc) -c code.cpp

mytetris.o : ./Mytetris/mytetris.cpp $(deps1)
	$(cc) -c ./Mytetris/mytetris.cpp

chunk.o : ./Mytetris/chunk.cpp $(deps2)
	$(cc) -c ./Mytetris/chunk.cpp

clean:
	$(RM) $(obj)

