MAIN = report

all:
	xelatex -shell-escape $(MAIN).tex
	xelatex -shell-escape $(MAIN).tex

clean:
	rm -f *.aux *.log *.out *.toc 
	rm -rf _minted*
	rm -f *.fls *.fdb_latexmk *.synctex.gz
