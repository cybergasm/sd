CXXFLAGS = -g -Wall

OBJS = main.o ShaderParser.o ShaderVariable.o ShaderClassGenerator.o Shader.o

#need the glu inclusion to compile the headers
LIBS = 	-lGLU \
		-lGLEW 
		
all: shader_parser

shader_parser: $(OBJS)
	g++ -g -Wall -o $@ $^ $(LIBS)

%.o:%.cpp
	g++ -c $(CXXFLAGS) -o $@ $< 
	
clean:
	rm -rf *.o