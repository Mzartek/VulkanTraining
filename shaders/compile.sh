#!/bin/sh

BASEDIR="$(dirname "$(realpath "$0")")"
SRCDIR="$BASEDIR/src"
COMPILER="$BASEDIR/glslangValidator.out"

compile_shaders()
{
    for f in $(find "$SRCDIR" -name "$1")
    do
	pushd "$(dirname "$f")" &> /dev/null
	"$COMPILER" -V "$f"
	popd &> /dev/null
    done
}

clean_shaders()
{
    for f in $(find "$SRCDIR" -name "*.spv")
    do
	rm "$f"
    done
}

if [ -z $1 ]
then
    compile_shaders "*.vert"
    compile_shaders "*.tesc"
    compile_shaders "*.tese"
    compile_shaders "*.geom"
    compile_shaders "*.frag"
    compile_shaders "*.comp"
elif [ $1 == "clean" ]
then
    clean_shaders
fi
