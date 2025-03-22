#pragma once

void __ClearAllErrors__();
void __GetAllErrors__(const char *file, long long line);

#define glCall(x)\
    __ClearAllErrors__();\
    x;\
    __GetAllErrors__(__FILE__, __LINE__);
