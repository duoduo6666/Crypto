# Preprocessing (预处理)
gpp src/SHA-1_x64.c             \
    -m64                        \
    -O3                         \
    -o dist/lib/SHA-1_x64.i

# Compilation (编译)
gcc -S dist/lib/SHA-1_x64.i     \
    -fPIC                       \
    -m64                        \
    -O3                         \
    -o dist/lib/SHA-1_x64.s

# Assembly (汇编)
as  dist/lib/SHA-1_x64.s        \
    --64                        \
    -Os                         \
    -o dist/lib/SHA-1_x64.o

# Linking (链接)
ld  dist/lib/SHA-1_x64.o        \
    -m elf_x86_64               \
    -fPIC                       \
    -shared                     \
    -o dist/lib/libSHA-1_x64.so