CXXFLAGS = -g -Wall

OBJS = main.o

all: shader_processor

shader_processor: $(OBJS)
	g++ -g -Wall -o $@ $^ 

%.o:%.cpp
	g++ -c $(CXXFLAGS) -o $@ $< 