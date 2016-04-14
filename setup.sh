#!/bin/sh

TOSH_BUILD_DIR=build-default

COL_GREEN='\033[0;32m'
COL_RED='\033[0;31m'
COL_NORM='\033[0m'

echo "Creating build directory..."

mkdir build-default
if [ $? -eq 0 ]; then
	echo -e "${COL_GREEN}Done${COL_NORM}"
else
	echo -e "${COL_RED}Failed to create build directory!${COL_NORM}"
	exit
fi

echo "Copying configuration file..."

cp config/tup_config build-default/tup.config
if [ $? -eq 0 ]; then
	echo -e "${COL_GREEN}Done${COL_NORM}"
else
	echo -e "${COL_RED}Failed to copy configuration file!${COL_NORM}"
	exit
fi

echo "Now run 'tup ${TOSH_BUILD_DIR}' to build TOSH"
