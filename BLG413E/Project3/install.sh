#!/bin/bash
{
	gcc map.c -o map -D_FILE_OFFSET_BITS=64 -lfuse
}