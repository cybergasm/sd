CXXFLAGS = -g -Wall

OBJS = main.o ShaderParser.o ShaderVariable.o

all: shader_parser

shader_parser: $(OBJS)
	g++ -g -Wall -o $@ $^ 

%.o:%.cpp
	g++ -c $(CXXFLAGS) -o $@ $< 