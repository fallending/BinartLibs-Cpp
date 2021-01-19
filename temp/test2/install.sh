#!/bin/sh

if [ "$#" -eq 0 ]
then 
    echo "use default install dir: target"
    INSTALL_DIR="../target"
elif [ "$#" -eq 1 ]
then 
    echo "use custom install dir: $1"
    INSTALL_DIR=$1
else
    echo "error"
fi

rm -drf bulid
rm -drf $INSTALL_DIR

mkdir bulid

cd bulid
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR ..
make
make install