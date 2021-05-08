#!/bin/bash
PORT=1234
HOST=127.0.0.1

mkdir -p logs

SRC=./bin/

# START SERVER
${SRC}chatserver ${PORT} &

${SRC}chatclient ${HOST} ${PORT}

# KILL SERVER
kill $(ps | grep chatserver | awk '{ print $1 }')
