clean:
	rm -f A B C D E *.log *.aux
report: fig.py report.tex
	python fig.py
	xelatex report.tex
	make clean