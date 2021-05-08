#!/bin/bash
make

cp ./chatclient ./test/bin/my_chatclient
cd test
go run main.go
