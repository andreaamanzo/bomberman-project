MAIN = report

all:
	xelatex -shell-escape $(MAIN).tex
	xelatex -shell-escape $(MAIN).tex
	mv report.pdf ../
	make clean

clean:
	rm -f *.aux *.log *.out *.toc 
	rm -rf _minted*
	rm -f *.fls *.fdb_latexmk *.synctex.gz
