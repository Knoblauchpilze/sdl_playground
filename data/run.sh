#!/bin/sh

CURR_DIR=$(dirname $0)
echo $(cat data/config/local)
./bin/sdl_playground $(cat data/config/local)
