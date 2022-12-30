shell/init.sh

shell/SHA-1_Compile.sh
shell/Crypto_Compile.sh

h=`dist/crypto abc`
if [ `dist/crypto abc` = "a9993e364706816aba3e25717850c26c9cd0d89d" ]
then
    echo -e -n "\033[32m"
    echo -n "SHA-1: ok"
    echo -e -n "\033[0m"
fi
echo ""
