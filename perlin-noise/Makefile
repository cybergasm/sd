#-Wno-switch to prevent the compiler from complaining about not 
#including all possible window events in switch statement.

CXXFLAGS = -g -Wall -Wno-switch -I../ 

SHADER_LOCATION = shaders
#Note that this expects your SFML libraries and headers to be
#installed as necessary
#Assumes assimp is installed on search path. 
LIBS = -L../engine  \
	-lsfml-network \
	-lsfml-window \
	-lsfml-graphics \
	-lsfml-system \
	-lassimp \
	-lGLU \
	-lGLEW \
	-lengine
	
OBJS = main.o PerlinNoiseGenerator.o TextureShader.o CloseWindowEvent.o

all: perlin

perlin: $(OBJS) ../engine/libengine.so.1.0.1
	g++ -g -Wall -o $@ $^ $(LIBS)

%.o:%.cpp
	g++ -c $(CXXFLAGS) -o $@ $< 

#Don't want to add this to LD so we do a quick hack while we're coding	
run: sd
	LD_LIBRARY_PATH=/home/emint/Documents/Projects/is/sd/engine ./perlin 
	
clean: 
	rm -f *.o
	
#Rules for making the shaders
TextureShader.o: $(SHADER_LOCATION)/simpletexture.vert.glsl $(SHADER_LOCATION)/simpletexture.frag.glsl
	./shader_parser $(SHADER_LOCATION)/simpletexture TextureShader; g++ -c $(CXXFLAGS) TextureShader.cpp -o $@ 	