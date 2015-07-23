cmake_minimum_required(VERSION 3.0)
project(object_oriented_c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c11 -Wall")

set(SOURCE_FILES
Class.h

Set/Set.h Set/Set.r
Set/Set.c Set/Set_Methods.c

Object/Object.h Object/Object.r
Object/Object.c

String/String.h String/String.r
String/String.c String/String_Methods.c

new.h
new.c

debug.h
debug.c

main.c
)
add_executable(object_oriented_c ${SOURCE_FILES})