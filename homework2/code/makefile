make: B.cpp C.cpp D.cpp E.cpp NewtonInterpolation.h
	g++ -o B B.cpp
	g++ -o C C.cpp
	g++ -o D D.cpp
	g++ -o E E.cpp

test: make ./data/E.in
	./B
	./C
	./D
	./E
	python fig.py