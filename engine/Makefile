#-Wno-switch to prevent the compiler from complaining about not 
#including all possible window events in switch statement.
#
#Last includes are so OGLFT can be configured property
CXXFLAGS = -g -Wall -Wno-switch -I/usr/include/freetype2 -I/usr/include/qt4/Qt -I/usr/include/qt4 -I../

#Shader location
SHADER_LOCATION = shaders

#Note that this expects your SFML libraries and headers to be
#installed as necessary

#This requires tha OGLFT is installed from:
#http://oglft.sourceforge.net/
#
#To get it working you also need libgle3 from repo and libqt4-dev

#Assumes assimp is installed on search path. 
LIBS = -lsfml-network \
	-lsfml-window \
	-lsfml-graphics \
	-lsfml-system \
	-lassimp \
	-lOGLFT \
	-lGLU \
	-lGLEW 
	
OBJS = Mesh3DS.o Shader.o Camera.o ResourceManager.o CfgFile.o InputProcessor.o \
InputEvent.o KeySequence.o TrackedSequence.o RenderingWindow.o ParallaxShader.o \
CharacterShader.o

all: engine

engine: $(OBJS)
	g++ -shared -g -Wall -o libengine.so.1.0.1 $^ $(LIBS)

%.o:%.cpp 
	g++ -c $(CXXFLAGS) -fPIC -o $@ $< 

clean: 
	rm -f *.o *.so.*
	
	
#Rules for making the shaders
ParallaxShader.o: $(SHADER_LOCATION)/parallax.vert.glsl $(SHADER_LOCATION)/parallax.frag.glsl
	./shader_parser $(SHADER_LOCATION)/parallax ParallaxShader; g++ -c $(CXXFLAGS) -fPIC ParallaxShader.cpp -o $@ 
	
CharacterShader.o: $(SHADER_LOCATION)/character.vert.glsl $(SHADER_LOCATION)/character.frag.glsl
	./shader_parser $(SHADER_LOCATION)/character CharacterShader; g++ -c $(CXXFLAGS) -fPIC CharacterShader.cpp -o $@
