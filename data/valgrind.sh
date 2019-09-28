#!/bin/sh

CURR_DIR=$(dirname $0)
valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all ./bin/sdl_playground $(cat data/config/local)
