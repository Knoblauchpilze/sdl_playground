#!/bin/sh

CURR_DIR=$(dirname $0)

gdb --args ./bin/sdl_playground $(cat data/config/local)
