#!/bin/sh

CURR_DIR=$(dirname $0)
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/lib"

gdb --args ./bin/sdl_playground $(cat data/config/local)
