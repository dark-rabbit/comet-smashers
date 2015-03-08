#!/bin/bash

g++ -c SpaceShip.cpp main.cpp 
g++ main.o -o comet-smashers -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
rm main.o SpaceShip.o
