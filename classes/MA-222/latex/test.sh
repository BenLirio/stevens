#!/bin/bash

fatal() {
	echo "SIGINT"
}

trap 'fatal' 2

sleep 4
