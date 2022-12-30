make: A.cpp CD.cpp E.cpp fig.py spline.h
	g++ A.cpp -o A -ljsoncpp --std=c11
	g++ CD.cpp -o CD -ljsoncpp --std=c11
	g++ E.cpp -o E -ljsoncpp --std=c11
	./A
	./CD
	./E
	python fig.py
	rm -f A B CD E *.log *.aux