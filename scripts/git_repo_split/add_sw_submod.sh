#!/bin/bash

git checkout master

git rm -r mxml
git submodule add https://bitbucket.org/tmidas/mxml.git mxml
git rm -r mscb
git submodule add https://bitbucket.org/tmidas/mscb.git mscb
git submodule init
git submodule update --recursive

git add .gitmodules
git commit -m "Configured submodules"
git push

mkdir sm_tmp
cp .gitmodules sm_tmp


git checkout develop

cp sm_tmp/.gitmodules .
rm -rf sm_tmp

git submodule init
git submodule update --recursive

git add .gitmodules
git commit -m "Configured submodules"
git push
