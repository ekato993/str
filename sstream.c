#include "libs/sstream.h"

#include <string.h>
#include <stdio.h>

sstream* sstream_create(char* str) {
    sstream* result = malloc(sizeof(sstream));
    result->length = strlen(str);
    result->capacity = result->length * 2;
    result->buffer = malloc(result->capacity+1);
    memcpy(result->buffer,str,result->length);
    result->buffer[result->length] = '\0';
    return result;
}

void sstream_free(sstream* str) {
    free(str->buffer);
    str->buffer = NULL;
}

char* sstream_get(sstream* str) {
    return str->buffer;
}

unsigned int sstream_lenght(sstream* str) {
    return str->length;
}

unsigned int sstream_capacity(sstream* str) {
    return str->capacity;
}

char sstream_atIndex(sstream* str, int idx) {
    return str->buffer[idx];
}

unsigned int sstream_findChar(sstream* str, char c) {
    return strchr(str->buffer, c) - str->buffer;
}

void sstream_print(sstream* str) {
    printf("%s",sstream_get(str));
}

sstream* sstream_copy(sstream* str) {
    return sstream_create(str->buffer);
}

void sstream_pushFrontChar(sstream* str, char c) {
    if(str->capacity < str->length + 2) { //+1 c, +1 \0
        char* temp = realloc(sstream_get(str),str->capacity*2);
        str->capacity = str->capacity * 2;
        str->buffer = temp;
    }
    memmove(&str->buffer[1],&str->buffer[0],str->length+1);
    str->buffer[0] = c;
    str->length = str->length + 1;
    str->buffer[str->length] = '\0';
}

void sstream_pushFrontStr(sstream* str, sstream* new) {
    if(str->capacity < (str->length + new->length + 1)) { //+1 \0
        char* temp = realloc(sstream_get(str),str->capacity * 2);
        str->capacity = str->capacity * 2;
        str->buffer = temp;
        if(str->capacity < (str->length + new->length + 1)) {
            sstream_pushFrontStr(str,new);
            return;
        }
    }
    memmove(&str->buffer[new->length],&str->buffer[0],str->length);
    memmove(&str->buffer[0],&new->buffer[0],new->length);
    str->length = str->length + new->length;
    str->buffer[str->length] = '\0';
}

void sstream_pushBackChar(sstream* str, char c) {
    if(str->capacity < str->length + 2) { //+1 c, +1 \0
        char* temp = realloc(sstream_get(str),str->capacity*2);
        str->capacity = str->capacity * 2;
        str->buffer = temp;
    }
    str->length = str->length + 1;
    str->buffer[str->length - 1] = c;
    str->buffer[str->length] = '\0';
}

void sstream_pushBackStr(sstream* str, sstream* new) {
    if(str->capacity < (str->length + new->length + 1)) { //+1 \0
        char* temp = realloc(sstream_get(str),str->capacity * 2);
        str->capacity = str->capacity * 2;
        str->buffer = temp;
        if(str->capacity < (str->length + new->length + 1)) {
            sstream_pushBackStr(str,new);
            return;
        }
    }
    memmove(&str->buffer[str->length],new->buffer,new->length);
    str->length = str->length + new->length;
    str->buffer[str->length] = '\0';
}

void sstream_insertStr(sstream* str, unsigned int idx, sstream* new) {
    if(str->capacity < (str->length + new->length + 1)) { //+1 \0
        char* temp = realloc(sstream_get(str),str->capacity * 2);
        str->capacity = str->capacity * 2;
        str->buffer = temp;
        if(str->capacity < (str->length + new->length + 1)) {
            sstream_insertStr(str,idx,new);
            return;
        }
    }
    memmove(str->buffer,str->buffer,idx);
    memmove(&str->buffer[idx + new->length],&str->buffer[idx],str->length - idx);
    str->length = str->length + new->length;
    memmove(&str->buffer[idx],new->buffer,new->length);
    str->buffer[str->length] = '\0';
}

void sstream_popFront(sstream* str) {
    memmove(&str->buffer[0],&str->buffer[1],str->length-1);
    str->length = str->length - 1;
    str->buffer[str->length] = '\0';
}

void sstream_popBack(sstream* str) {
    memmove(&str->buffer[str->length],&str->buffer[str->length+1],str->length - 1);
    str->length = str->length - 1;
    str->buffer[str->length] = '\0';
}

void sstream_erase(sstream* str, unsigned int idx, unsigned int len) {
    memmove(&str->buffer[idx],&str->buffer[idx + len], str->length - idx);
    str->length = str->length - len;
    if(str->capacity > (str->length * 16)) { // if to big
        str->capacity = str->length * 2 + 1;
        str->buffer = realloc(str->buffer,str->capacity);
    }
    str->buffer[str->length] = '\0';
}

void sstream_replace(sstream* str, unsigned int idx, unsigned int len, sstream* new) {
    if(str->capacity < (str->length + new->length + 1)) { //+1 \0
        char* temp = realloc(sstream_get(str),str->capacity * 2);
        str->capacity = str->capacity * 2;
        str->buffer = temp;
        if(str->capacity < (str->length + new->length + 1)) {
            sstream_replace(str,idx,len,new);
            return;
        }
    }
    memmove(str->buffer,str->buffer,idx);
    memmove(&str->buffer[idx],new->buffer,idx + new->length);
    memmove(&str->buffer[idx + new->length], &str->buffer[idx + len], str->length + new->length - len);
    str->length = str->length + new->length - len;
    str->buffer[str->length] = '\0';
}

sstream* sstream_substring(sstream* str, unsigned int idx, unsigned int len) {
    sstream* result = malloc(sizeof(sstream));
    result->length = len;
    result->capacity = result->length * 2;
    result->buffer = malloc(result->capacity + 1);
    memcpy(result->buffer,&str->buffer[idx],result->length);
    result->buffer[result->length] = '\0';
    return result;
}


