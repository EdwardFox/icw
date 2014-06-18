CXX = g++
SOURCES = src/Main.cpp src/Game.cpp src/GameObject.cpp src/World.cpp src/Grid.cpp src/components/TestAIComponent.cpp src/components/DefaultGraphicComponent.cpp src/components/TestInputComponent.cpp src/components/DefaultPhysicsComponent.cpp
EXE = build/run
PROJECT_ROOT = $(shell pwd)
INC = /home/adrian/dev/cpp/projects/plat

all: $(EXE)
	./$(EXE)

$(EXE):
	$(CXX) -g -Wall -I$(INC) -o $@ $(SOURCES) -lsfml-graphics -lsfml-window -lsfml-system -lBox2D -std=c++11

.PHONY: $(EXE)

clean:
	rm $(EXE)
