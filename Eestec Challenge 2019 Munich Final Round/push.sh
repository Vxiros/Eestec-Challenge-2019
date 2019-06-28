#!/bin/bash 

## ena skriptaki pou kanei eukola push
## ektelite os eksis:
## ./push arg1 opou:
## arg1 einai to minima p tha periexei to commit
## enjoy

var="${1}"

git add *
git commit -m  "$var"
git push origin master
