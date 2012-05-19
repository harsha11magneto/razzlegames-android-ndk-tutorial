#!/bin/bash

#cgdb -d psp-gdb -x $PSPDIR/gdbremote.txt ./RazzlePuzzle.elf
cgdb -d ndk-gdb -x gdbremote.txt ./RazzlePuzzle.elf


