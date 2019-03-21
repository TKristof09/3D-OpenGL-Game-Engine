@echo off
cd Build/Windows
cmake -A x64 ../../
MSBuild.exe 3DGameEngine.sln -m -p:NoWarn=4514