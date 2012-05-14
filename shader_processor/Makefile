CXXFLAGS = -g -Wall

SHADER_OBJS = ParallaxShader.o
SHADER_LOCATION = shaders

OBJS = main.o ShaderParser.o ShaderVariable.o ShaderClassGenerator.o Shader.o ParallaxShader.o

#need the glu inclusion to compile the headers
LIBS = 	-lGLU \
		-lGLEW 
		
all: shader_parser

shader_parser: $(OBJS)
	g++ -g -Wall -o $@ $^ $(LIBS)

%.o:%.cpp
	g++ -c $(CXXFLAGS) -o $@ $< 
	
#Rules for making the shaders
ParallaxShader.o: $(SHADER_LOCATION)/parallax.vert.glsl $(SHADER_LOCATION)/parallax.frag.glsl
	./shader_parser $(SHADER_LOCATION)/parallax ParallaxShader; g++ -c $(CXXFLAGS) ParallaxShader.cpp -o $@ 
	
clean:
	rm -rf *.o