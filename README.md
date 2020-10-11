# Babel


## Installation
```bash
echo "
[requires]
zstd/1.3.5@bincrafters/stable
zlib/1.2.11@conan/stable
bzip2/1.0.8@conan/stable
qt/5.14.2@bincrafters/stable
portaudio/v190600.20161030@bincrafters/stable
opus/1.2.1@bincrafters/stable
boost_asio/1.69.0@bincrafters/stable


[generators]
cmake" > "conanfile.txt"

sudo apt-get install "^libxcb.*" libx11-xcb-dev libglu1-mesa-dev libxrender-dev;
conan remote add conan https://api.bintray.com/conan/conan/conan-center;
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan;
conan remote add epitech https://api.bintray.com/conan/epitech/public-conan;
mkdir build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake --build .
```

### Building

```
mkdir build;
cd build;
conan install .. --build=missing;
cmake ..;
make;
```
Your binary will be create in `/build/bin/`.

### Documentation

You can found the documentation inside the doc folder.
Inside the doc folder you have:
- a html folder with an index.html that you can open
- a UML folder with the UML Datagram for the client & server
