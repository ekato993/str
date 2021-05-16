#pragma once

#include <stdlib.h>

typedef struct sstream sstream;

struct sstream {
    char* buffer;
    unsigned int length;
    unsigned int capacity;
};

sstream* sstream_create(char* str);

void sstream_free(sstream* str);

char* sstream_get(sstream* str);

unsigned int sstream_lenght(sstream* str);

unsigned int sstream_capacity(sstream* str);

char sstream_atIndex(sstream* str, int idx);

unsigned int sstream_findChar(sstream* str, char c);

void sstream_print(sstream* str);

sstream* sstream_copy(sstream* str);

void sstream_pushFrontChar(sstream* str, char c);

void sstream_pushFrontStr(sstream* str, sstream* new);

void sstream_pushBackChar(sstream* str, char c);

void sstream_pushBackStr(sstream* str, sstream* new);

void sstream_insertStr(sstream* str, unsigned int idx, sstream* new);

void sstream_popFront(sstream* str);

void sstream_popBack(sstream* str);

void sstream_erase(sstream* str, unsigned int idx, unsigned int len);

void sstream_replace(sstream* str, unsigned int idx, unsigned int len, sstream* new);

sstream* sstream_substring(sstream* str, unsigned int idx, unsigned int len);


























