#pragma once
#include "stdio.h"
#include <errno.h>


typedef enum {
    NoErrors = 0,               // без ошибок
    MemoryError,                // Ошибка выделения памяти
    LoopError,                  // Была создана петля
    WeightOutOfRangeError,      // Вес вне допустимых границах
    VertexNotExistsError,       // Несуществующая вершина
    InvalidArg,
    UnknownError = 15           // для других ошибок
} error_t;


int error_catcher(error_t err);