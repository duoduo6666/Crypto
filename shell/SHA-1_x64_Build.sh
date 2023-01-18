gcc src/SHA-1_x64.c             \
    -fPIC                       \
    -shared                     \
    -m64                        \
    -O3                         \
    -o dist/lib/libSHA-1_x64.so
