#!/bin/bash

##
# A shell script to generate a skeleton project for an Advent of Code 2019 day
#
# It makes use of the simple template specification called "Mustache", in it's
# bash implementation from https://github.com/tests-always-included/mo.
#
# It works on the template files in the template/ directory.
#
# Execution: ./template.sh <TARGET_DIR> <DAY_NUMBER> <NAME>
##

ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

USAGE='template.sh <TARGET_DIR> <DAY_NUMBER> <NAME>

The <DAY> needs to be given in the form \"DD\", e.g. \"01\" or \"22\".
The <NAME> needs to be a valid filename.'

die() {
    echo "$1"
    exit 1
}

template() {
    local templ="$1"
    local target="$2"
    echo "Templating ${templ}"
    "${ROOT_DIR}/third_party/mo" \
        < "${ROOT_DIR}/template/${templ}" \
        > "${TARGET_DIR}/${target}"
}

if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    echo "$USAGE"
    exit 0
fi

if [[ "$#" -ne "3" ]]; then
    echo "$USAGE"
    exit 1
fi

TARGET_DIR="$(realpath ${1})"
export DAY="$2"
export NAME="$3"

if [ -d "$TARGET_DIR" ]; then
    echo "Target dir: \"$TARGET_DIR\" already exists, aborting."
    exit 1
fi

mkdir -p "$TARGET_DIR" || die "Day Directory creation for $TARGET_DIR failed."

echo "Beginning templating..."
template "CMakeLists.txt.templ" "CMakeLists.txt"
template "day.cpp.templ" "day_${DAY}.cpp"
template "day_ut.cpp.templ" "day_${DAY}_ut.cpp"
template "impl.cpp.templ" "${NAME}.cpp"
template "impl.hpp.templ" "${NAME}.hpp"

echo "Creating initial build..."
mkdir -p "${TARGET_DIR}/build"
cmake -S "${TARGET_DIR}" -B "${TARGET_DIR}/build" -DUNITTESTS_ENABLED=ON -DCMAKE_BUILD_TYPE=Debug
pushd "${TARGET_DIR}/build" > /dev/null
make -j "$(nproc)"
popd > /dev/null

echo "Generating symlink for compile_commands.json"
ln -s "${TARGET_DIR}/build/compile_commands.json" "${TARGET_DIR}/compile_commands.json"
