#!/usr/bin/env sh

# Move to the app directory
cd "$(dirname "$(readlink -f "$0")")" || exit

SOURCE_FILE="src/main.cpp"
DBE16_FILE="src/dbe16.cpp"
OUTPUT_FILE="example"

# Compile the app
exec g++ $SOURCE_FILE $DBE16_FILE -o $OUTPUT_FILE --std=c++17 `pkg-config --cflags --libs gtk+-3.0` -I/usr/lib/include -lboost_system "$@"
