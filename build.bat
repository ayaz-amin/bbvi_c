@echo off

mkdir debug
pushd debug

set SRC=../src/*.cpp

clang-cl -O2 %SRC% /link /SUBSYSTEM:CONSOLE /OUT:main.exe

popd
