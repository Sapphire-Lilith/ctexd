#!/bin/bash

gcc ./ctexd.c -o ctexd
sudo mv ./ctexd /usr/local/bin
echo ========= texd installed! ==========
