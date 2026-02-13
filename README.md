# Debug

To debug, we use `CMAKE_BUILD_TYPE`. For our wasm build, we run `emcmake cmake --DCMAKE_BUILD_TYPE=DEBUG` from within our build dir, e.g. `build-em`. This automatically passes the debug flag to our compiler of choice. There are however a few things that are not done automatically. First, within the `CMakeLists.txt` file we generate a binary (aside from the wasm file). Second, within the the source code, we include `main` so that our debugger will have an entry point. 

# Versioning

WIP: Bump versions for our npm publications.
