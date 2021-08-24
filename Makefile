all: pres.pdf pres.html

pres.pdf: pres.md
	pandoc -t beamer -o pres.pdf pres.md

pres.html: pres.md
	pandoc -s -t revealjs -V revealjs-url=./reveal.js \
	-V theme=solarized -o pres.html pres.md
