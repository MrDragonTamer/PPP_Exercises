#!/bin/bash

set -euo pipefail
IFS=$'\n\t'

#Get new project name
read -p "Folder Name For Project: " dirName

#ensure dirName isn't empty

if [[ -z "${dirName}" ]]; then
    echo "Error: Empty Name" >&2
    exit 1
fi

#ensure directory doesn't already exist so we don't put random stuff into it

if [[ -d "${dirName}" ]]; then
    echo "Error: Directory already exists" >&2
    exit 1
fi

#make the project directory structure and copy over the files

mkdir -p "${dirName}/src"
mkdir -p "${dirName}/include"
mkdir -p "${dirName}/libs"
mkdir -p "${dirName}/build"
mkdir -p "${dirName}/tests"
mkdir -p "${dirName}/docs"
mkdir -p "${dirName}/tools"
mkdir -p "${dirName}/assets"
#cp ./makefile "${dirName}/build"
cp ./makefile "${dirName}"
cp ./PPPheaders.h "${dirName}/include"
cp ./PPP_support.h "${dirName}/include"
cp ./dirStructure.txt "${dirName}"
