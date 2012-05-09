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
LIBS = -L../engine  \
	-lsfml-network \
	-lsfml-window \
	-lsfml-graphics \
	-lsfml-system \
	-lassimp \
	-lOGLFT \
	-lGLU \
	-lGLEW \
	-lengine
	
OBJS = main.o Character.o InputResponder.o Tile.o CloseWindowEvent.o

all: sd

sd: $(OBJS) ../engine/libengine.so.1.0.1
	g++ -g -Wall -o $@ $^ $(LIBS)

%.o:%.cpp
	g++ -c $(CXXFLAGS) -o $@ $< 

#Don't want to add this to LD so we do a quick hack while we're coding	
run: sd
	LD_LIBRARY_PATH=/home/emint/Documents/Projects/is/sd/engine ./sd
	
clean: 
	rm -f *.o