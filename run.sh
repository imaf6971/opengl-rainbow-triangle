/usr/bin/cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S/home/imaf6971/opengl-rainbow-triangle -B/home/imaf6971/opengl-rainbow-triangle/build -G "Unix Makefiles"
cmake --build ./build --config Debug --target all -j 10 --
./build/opengl_project
