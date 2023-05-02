# Run with sh mingw64buildPython3_6.sh


COMPILE="g++ -D MINGW -std=c++17 -shared -fPIC -static-libgcc -static-libstdc++ -I./include/ -I./pybind11/include/ `python3.6 -m pybind11 --includes` ./src/*.cpp ./src/ComponentSystem/*.cpp ./src/Managers/*.cpp ./src/Pybind/*.cpp -o ./bin/StuartLittleEngine.pyd `python3.6-config --ldflags` -lmingw32 -lSDL2main -lSDL2 -mwindows -L ./lib/libwinpthread-1.dll"


echo $COMPILE
echo "-------------------------------------------"
eval $COMPILE
