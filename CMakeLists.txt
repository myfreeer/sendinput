cmake_minimum_required(VERSION 2.6)
project(sendinput)

set(SOURCE_FILES
    sendinput.c
    command.h
    mouse.h
    sendkey.h
    crc32.h
	)

add_executable(sendinput ${SOURCE_FILES})
