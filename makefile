HEADERS1 = -I Ejercicio_1/headers/


SRC_COMMON1 = Ejercicio_1/sources/*.cpp


ej1:
	g++ -std=c++17 -Wall -Wextra -Wpedantic $(HEADERS1) -g Ejercicio_1/main1.cpp $(SRC_COMMON1) -o ejercicio1
	./ejercicio1


clean:
	rm -f ejercicio1 ejercicio2 ejercicio3 vuelo.bin
	rm -rf *.dSYM/