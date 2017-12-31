#!/bin/sh

BASEDIR="$(dirname "$(realpath "$0")")"
SRCDIR="$BASEDIR/src"
COMPILER="$BASEDIR/glslangValidator.app"

if [ -z "$1" ]
then
    for f in $(find "$BASEDIR/src" -name "*.vert" -or -name "*.tesc" -or -name "*.tese" -or -name "*.geom" -or -name "*.frag" -or -name "*.comp")
    do
	pushd "$(dirname "$f")" &> /dev/null
	"$COMPILER" -V "$f"
	popd &> /dev/null
    done
elif [ "$1" == "clean" ]
then
    for f in $(find "$BASEDIR/src" -name "*.spv")
    do
	rm "$f"
    done
fi

