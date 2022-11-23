make: A.cpp B.cpp
	g++ -o B B.cpp
	g++ -o A A.cpp

clean:
	rm -f A B C D E *.log *.aux
work: make report.tex
	./B
	./A
	python fig.py
	xelatex report.tex
	make clean
report: report.tex
	xelatex report.tex
	