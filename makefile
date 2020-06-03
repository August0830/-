cal: Calculator.o Func.o
	g++ -g Calculator.o Func.o -o cal
Calculator.o: Calculator.cpp Calculator.h
	g++ -g Calculator.cpp -c
Func.o: Func.cpp  
	g++ -g Func.cpp -c

clean:
	rm Func.o Calculator.o cal

