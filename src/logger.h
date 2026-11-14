#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>

typedef enum LogLevel { DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3 } LogLevel;

typedef struct Logger {
  FILE *output_handle;
  LogLevel min_level;
} Logger;

void logger_init(Logger *logger, FILE *output_handle, LogLevel min_level);

void logger_log(Logger *logger, const char *message, LogLevel level);

#endif
