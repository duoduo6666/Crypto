shopt -s expand_aliases
alias trace_on='set -x'
alias trace_off='{ set +x; } 2>/dev/null'
set -e


trace_on

shell/init.sh
shell/SHA-1_Compile.sh
shell/Crypto_Compile.sh

trace_off

echo -e "\033[32mBuild OK!\033[0m"