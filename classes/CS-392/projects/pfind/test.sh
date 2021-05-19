#!/bin/bash
make
cp main tests/pfind
cd tests
python test_pfind.py
cd ..
