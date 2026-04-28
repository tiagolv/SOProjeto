#!/bin/bash
# Script File sc1.sh
# assume that /tmp is a local not network disk
#
bigFile=/tmp/bigFile
if [ ! -e $bigFile ]; then
    # create 16MB file in /tmp with random values
    dd if=/dev/urandom of=${bigFile} bs=16M count=1
    # mac users may have to replace 16M with 16000000
fi
size=4096
tmpFile=$(mktemp)
while [ $size -gt 1 ]; do
   echo -n $size "  "
   solowlevelcp $bigFile  $tmpFile   $size 
   #./a.out $bigFile  $tmpFile   $size 
   rm $tmpFile
   let size=size/4
done
