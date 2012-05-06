#-Wno-switch to prevent the compiler from complaining about not 
#including all possible window events in switch statement.
#
#Last includes are so OGLFT can be configured property
CXXFLAGS = -g -Wall -Wno-switch -I/usr/include/freetype2 -I/usr/include/qt4/Qt -I/usr/include/qt4 -I../

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
	
OBJS = Mesh3DS.o Shader.o Camera.o ResourceManager.o CfgFile.o InputProcessor.o InputEvent.o KeySequence.o

all: engine

engine: $(OBJS)
	g++ -shared -g -Wall -o libengine.so.1.0.1 $^ $(LIBS)

%.o:%.cpp
	g++ -c $(CXXFLAGS) -fPIC -o $@ $< 

clean: 
	rm -f *.o *.so.*