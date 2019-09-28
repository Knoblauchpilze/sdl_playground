#!/bin/sh

CURR_DIR=$(dirname $0)
./bin/sdl_playground $(cat data/config/local)
