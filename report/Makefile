MAIN = report

all:
	xelatex -shell-escape $(MAIN).tex
	xelatex -shell-escape $(MAIN).tex

clean:
	rm -f *.aux *.log *.out *.toc *.fls *.fdb_latexmk *.synctex.gz
	rm -rf _minted-*