# Run with sh mingw64build.sh


COMPILE="g++ -D MINGW -std=c++14 -shared -fPIC -static-libgcc -static-libstdc++ -I./include/ -I./pybind11/include/ `python3.9 -m pybind11 --includes` ./src/*.cpp ./src/ComponentSystem/*.cpp ./src/Managers/*.cpp ./src/Pybind/*.cpp -o ./bin/StuartLittleEngine.pyd `python3.9-config --ldflags` -lmingw32 -lSDL2main -lSDL2 -mwindows -L libwinpthread-1.dll"


echo $COMPILE
echo "-------------------------------------------"
eval $COMPILE
