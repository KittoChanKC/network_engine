@REM #change current direction to this file

@REM change driver letter
@%~d0

@REM change current directory
@cd %~dp0

mkdir _build
cmake -B _build .

@pause