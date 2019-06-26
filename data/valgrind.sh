#!/bin/sh

CURR_DIR=$(dirname $0)
echo $(cat data/config/local)
valgrind --leak-check=yes ./bin/sdl_playground $(cat data/config/local)
