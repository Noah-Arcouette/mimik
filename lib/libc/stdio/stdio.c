#include "stdio.h"
#include <unistd.h>

#ifdef BUFSIZ
static char _stdin_buff[BUFSIZ];
static FILE _stdin_file = {
    .fildes = STDIN_FILENO,
    .flags  = _FILE_FLAG_OP_READ | _FILE_FLAG_FILDES | _FILE_FLAG_BUFFERED | _FILE_FLAG_NO_CLOSE,
    .seek   = 0,

    .buffuse = 0,
    .buffsz  = sizeof(_stdin_buff),
    .buff    = _stdin_buff
};
FILE *stdin = &_stdin_file;
#else
static FILE _stdin_file = {
    .fildes = STDIN_FILENO,
    .flags  = _FILE_FLAG_OP_READ | _FILE_FLAG_FILDES | _FILE_FLAG_NO_CLOSE,
    .seek   = 0,

    .buffuse = 0,
    .buffsz  = 0,
    .buff    = (char*)NULL
};
FILE *stdin = &_stdin_file;
#endif

#ifdef BUFSIZ
static char _stdout_buff[BUFSIZ];
static FILE _stdout_file = {
    .fildes = STDOUT_FILENO,
    .flags  = _FILE_FLAG_OP_WRITE | _FILE_FLAG_FILDES | _FILE_FLAG_BUFFERED | _FILE_FLAG_NO_CLOSE,
    .seek   = 0,

    .buffuse = 0,
    .buffsz  = sizeof(_stdout_buff),
    .buff    = _stdout_buff
};
FILE *stdout = &_stdout_file;
#else
static FILE _stdout_file = {
    .fildes = STDOUT_FILENO,
    .flags  = _FILE_FLAG_OP_WRITE | _FILE_FLAG_FILDES | _FILE_FLAG_NO_CLOSE,
    .seek   = 0,

    .buffuse = 0,
    .buffsz  = 0,
    .buff    = (char*)NULL
};
FILE *stdout = &_stdout_file;
#endif

#ifdef BUFSIZ
static char _stderr_buff[BUFSIZ];
static FILE _stderr_file = {
    .fildes = STDERR_FILENO,
    .flags  = _FILE_FLAG_OP_WRITE | _FILE_FLAG_FILDES | _FILE_FLAG_BUFFERED | _FILE_FLAG_NO_CLOSE,
    .seek   = 0,

    .buffuse = 0,
    .buffsz  = sizeof(_stderr_buff),
    .buff    = _stderr_buff
};
FILE *stderr = &_stderr_file;
#else
static FILE _stderr_file = {
    .fildes = STDERR_FILENO,
    .flags  = _FILE_FLAG_OP_WRITE | _FILE_FLAG_FILDES | _FILE_FLAG_NO_CLOSE,
    .seek   = 0,

    .buffuse = 0,
    .buffsz  = 0,
    .buff    = (char*)NULL
};
FILE *stderr = &_stderr_file;
#endif
