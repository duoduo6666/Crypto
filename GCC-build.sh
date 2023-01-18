export SHELLOPTS                            # 继承环境变量
shopt -s expand_aliases                     # 启用 alias
alias trace_on='set -x'                     # 启用 打印执行的命令
alias trace_off='{ set +x; } 2>/dev/null'   # 关闭 打印执行的命令
set -e                                      # 当遇到错误就停止


trace_on

shell/init.sh
shell/SHA-1_x64_Build.sh
shell/Crypto_Build.sh

trace_off

echo -e "\033[32mBuild OK!\033[0m"