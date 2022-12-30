# -l         使用的动态链接库
# -L         将目录添加到要搜索的目录列表
# -Wl,-rpath 将目录添加到运行时的库搜索路径

gcc src/crypto.c                \
    -l SHA-1_x64                \
    -L dist/lib/                \
    -Wl,-rpath,'$ORIGIN'/lib/   \
    -O3                         \
    -o dist/crypto
