#!/bin/bash

STYLE=$(which clang-format)
if [ $? -ne 0 ]; then
    echo "clang-format not installed. Unable to check source file format policy." >&2
    exit 1
fi

RE=0
ALLFILES=$(find . -not \( -path ./third_party -prune \) -name '*.hpp' -o -name '*.ipp'  -o -name '*.cpp')
for FILE in $ALLFILES; do
  $STYLE $FILE | cmp -s $FILE -
  if [ $? -ne 0 ]; then
    echo "FATAL : Found incorrectly formatted file "$FILE   " . Exiting..."
    $STYLE -i $FILE
    RE=1
  fi
done

exit $RE
