#!/bin/bash
clear
mkdir -p static
latex --output-format pdf --output-dir static hello.tex
./main &
GO_PID=$!
fatal() {
	kill $GO_PID
}
trap 'fatal' 2
#google-chrome-stable http://localhost:3000/hello.pdf
xdotool search --onlyvisible --class "Chrome" windowfocus key F5
echo 
echo 
echo http://localhost:3000/hello.pdf
sleep 99999999
