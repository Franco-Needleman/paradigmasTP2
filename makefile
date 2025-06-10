HEADERS2 = -I Ejercicio_2/headers/


SRC_COMMON2 = Ejercicio_2/sources/*.cpp


ej2:
	g++ -std=c++20 -Wall -Wextra -Wpedantic $(HEADERS2) -g Ejercicio_2/main2.cpp $(SRC_COMMON2) -o ejercicio2
	./ejercicio2

	

clean:
	rm -f ejercicio1 ejercicio2 ejercicio3 vuelo.bin
	rm -rf *.dSYM/