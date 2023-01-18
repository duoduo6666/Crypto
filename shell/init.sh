if [ -d "dist/" ]
then
    rm -r dist/*
else
    mkdir dist/
fi

if [ ! -d "dist/lib" ]
then
    mkdir dist/lib/
fi
