echo off
CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
SET QTDIR=C:\Qt\5.12.6\msvc2017
SET SPEC=win32-msvc
SET PATH=%QTDIR%\bin;%PATH%
SET QMAKESPEC=%QTDIR%\mkspecs\%SPEC%

qmake -tp vc -r