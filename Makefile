all: pres.pdf pres_part_1.pdf pres.html

pres.pdf: pres.md
	pandoc -t beamer -o pres.pdf pres.md

pres_part_1.pdf: pres_part-1.md
	pandoc -t beamer -o pres_part_1.pdf pres_part-1.md

pres.html: pres.md
	pandoc -s -t revealjs -V revealjs-url=./reveal.js \
	-V theme=solarized -o pres.html pres.md
