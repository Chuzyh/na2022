make: B.cpp C.cpp D.cpp E.cpp NewtonInterpolation.h
	g++ -o B B.cpp
	g++ -o C C.cpp
	g++ -o D D.cpp
	g++ -o E E.cpp

work: make ./data/E.in report.tex
	./B
	./C
	./D
	./E
	python fig.py
	xelatex report.tex
report: report.tex
	xelatex report.tex
	
clean:
	rm -f B C D E *.log *.aux