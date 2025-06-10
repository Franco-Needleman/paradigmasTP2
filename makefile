HEADERS1 = -I Ejercicio_1/headers/
HEADERS2 = -I Ejercicio_2/headers/

SRC_COMMON1 = Ejercicio_1/sources/*.cpp
SRC_COMMON2 = Ejercicio_2/sources/*.cpp

ej1:
	g++ -std=c++17 -Wall -Wextra -Wpedantic $(HEADERS1) -g Ejercicio_1/main1.cpp $(SRC_COMMON1) -o ejercicio1
	./ejercicio1

ej2:
	g++ -std=c++20 -Wall -Wextra -Wpedantic $(HEADERS2) -g Ejercicio_2/main2.cpp $(SRC_COMMON2) -o ejercicio2
	./ejercicio2

	

clean:
	rm -f ejercicio1 ejercicio2 ejercicio3
	rm -rf *.dSYM/