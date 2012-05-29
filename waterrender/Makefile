#-Wno-switch to prevent the compiler from complaining about not 
#including all possible window events in switch statement.

CXXFLAGS = -g -Wall -Wno-switch -I../ 

SHADER_LOCATION = shaders
SHADER_PARSER_LOC = ../shader_processor

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
	
OBJS = main.o CloseWindowEvent.o WavesShader.o KeyMovement.o MouseLookEvent.o \
 WaveRenderer.o ../perlin-noise/PerlinNoiseGenerator.o PerlinWavesShader.o \
 PerlinWavesRenderer.o

all: water

water: $(OBJS) ../engine/libengine.so.1.0.1
	g++ -g -Wall -o $@ $^ $(LIBS)

%.o:%.cpp
	g++ -c $(CXXFLAGS) -o $@ $< 

#Don't want to add this to LD so we do a quick hack while we're coding	
run: sd
	LD_LIBRARY_PATH=/home/emint/Documents/Projects/is/sd/engine ./water
	
clean: 
	rm -f *.o
	
#Rules for making the shaders
WavesShader.o: $(SHADER_LOCATION)/waves.vert.glsl $(SHADER_LOCATION)/waves.frag.glsl
	./shader_parser $(SHADER_LOCATION)/waves WavesShader; g++ -c $(CXXFLAGS) WavesShader.cpp -o $@ 	
	
PerlinWavesShader.o: $(SHADER_LOCATION)/perlinwaves.vert.glsl $(SHADER_LOCATION)/perlinwaves.frag.glsl
	$(SHADER_PARSER_LOC)/shader_parser $(SHADER_LOCATION)/perlinwaves PerlinWavesShader; g++ -c $(CXXFLAGS) PerlinWavesShader.cpp -o $@ 	