g++ -c main.cpp
g++ main.o -o bin/test -lsfml-graphics -lsfml-window -lsfml-system
rm main.o
./bin/test
