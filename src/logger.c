#include "logger.h"

static const char *level_string[] = {"DEBUG", "INFO", "WARN", "ERROR"};

void logger_init(Logger *logger, FILE *output_handle, LogLevel min_level) {
  logger->output_handle = output_handle;
  logger->min_level = min_level;
}

void logger_log(Logger *logger, const char *message, LogLevel level) {
  if (level >= logger->min_level) {
    fprintf(logger->output_handle, "[%s]: %s\n", level_string[level], message);
  }
}
