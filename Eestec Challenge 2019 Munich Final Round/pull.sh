#!/bin/bash

## ena scriptaki gia na kanei kaneis 
## eukola pull
## ektelite os:
## ./pull arg1
## opou arg1 to minima p tha periexete mesa sto commit
## enjoy

var="${1}"

git add *
git commit -m "$var$"
git pull origin master

