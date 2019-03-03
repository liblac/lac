#!/bin/bash
# Exit on Any Command Failing
set -e
set -o pipefail

if [ "$#" -ne 1 ]; then
  echo "Expected a destination directory argument."
  exit 1
fi

DESTDIR=$1

EXIST_FILE=.lac-hugo-website

if [ ! -f $DESTDIR/$EXIST_FILE ]; then
  echo "[FATAL] :$DESTDIR does not contain hugo generated website."
  echo "Exiting..."
  exit 1
fi

hugo # if using a theme, replace with `hugo -t <YOURTHEME>`
rsync -aAXv public/ $DESTDIR/
touch $DESTDIR/$EXIST_FILE
rm -rf public
