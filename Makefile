.SUFFIXES:
.SUFFIXES: .cpp

GCC = g++

.cpp:
	$(GCC) -Wall -Wunused -std=c++11 -O2 $< -o $@ `pkg-config --cflags --libs opencv4 cairo`


pdf:
	asciidoctor-pdf -r asciidoctor-diagram -r asciidoctor-mathematical --theme default-theme.yml -o report.pdf report.asc
