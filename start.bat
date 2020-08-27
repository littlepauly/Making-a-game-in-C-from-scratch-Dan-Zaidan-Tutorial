@echo off

subst w: "C:\Users\Paul\Documents\DevSpace\breakout"

w:

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall" x86_amd64

Start "" "C:\Program Files\4coder\4ed.exe"

call devenv "build\win32_platform.exe"

cmd