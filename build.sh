#! /bin/bash
set -eo pipefail

# run script to build executable

# get source dir
source=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# remove build directory
build_dir="${source}/build"
if [ -d $build_dir ]; then
    rm -r $build_dir
fi

mkdir $build_dir
cmake $source -B $build_dir -G "Ninja"
cmake --build $build_dir

if [ $1 = "run" ]; then
    $build_dir/asl
fi