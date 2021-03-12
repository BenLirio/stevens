#!/bin/bash
clang -o client client.c
clang -o server server.c
./server
./client
