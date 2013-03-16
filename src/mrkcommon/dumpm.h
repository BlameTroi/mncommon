#ifndef DUMPM_H
#define DUMPM_H

#ifdef MRKCOMMON_LDUMPM_H
#error "Please use eigher this file or mrkcommon/ldumpm.h, or #include logging_private.h AFTER this file."
#endif

#ifdef MRKCOMMON_LOGGING_H
#error "Please use either this file or mrkcommon/logging.h, or #include mrkcommon/logging.h AFTER this file."
#endif

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#define DUMPM_INDENT_SIZE 4

#ifdef USE_SYSLOG
# define TRACEN(s, ...)     (syslog(LOG_DEBUG,    "[T]%s:%d:%s() " s       __FILE__, __LINE__, __func__, ##__VA_ARGS__))
# define TRACE(s, ...)      (syslog(LOG_DEBUG,    "[T]%s:%d:%s() " s "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__))
# define DEBUG(s, ...)      (syslog(LOG_DEBUG,    "[D]%s:%d:%s() " s "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__))
# define INFO(s, ...)       (syslog(LOG_INFO,     "[I]%s:%d:%s() " s "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__))
# define WARNING(s, ...)    (syslog(LOG_WARNING,  "[W]%s:%d:%s() " s "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__))
# define ERROR(s, ...)      (syslog(LOG_ERR,      "[E]%s:%d:%s() " s "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__))
#else
# define TRACEN(s, ...) (fprintf(stderr, "[%5d] %s:%d:%s() " s getpid(), __FILE__, __LINE__, __func__, ##__VA_ARGS__))
# define TRACE(s, ...) (fprintf(stderr, "[%5d] %s:%d:%s() " s "\n", getpid(), __FILE__, __LINE__, __func__, ##__VA_ARGS__))
# define DEBUG   TRACE
# define INFO    TRACE
# define WARNING TRACE
# define ERROR   TRACE
# define LTRACE(lvl, s, ...) fprintf(stderr, "%*c" s "\n", DUMPM_INDENT_SIZE * (lvl), ' ', ##__VA_ARGS__)

#endif

#ifdef TRRET_DEBUG
#   define TRRET(n) do { if (errno && 0) {perror("TRRET");} TRACE("%s", diag_str((n))); return (n); } while (0)
#   define TRRETNULL(n) do { if (errno && 0) {perror("TRRETNULL");} TRACE("%s", diag_str((n))); return (NULL); } while (0)
#else
#   define TRRET(n) return (n)
#   define TRRETNULL(n) return (NULL)
#endif
void dumpm(const void * m, size_t n, size_t l);
#define D8(m, n) dumpm(m, n, 8)
#define D16(m, n) dumpm(m, n, 16)
#define D32(m, n) dumpm(m, n, 32)
#define D64(m, n) dumpm(m, n, 64)

#define FCOLOR(b, c, s) "\033[0" b ";3" c "m" s "\033[00m"
#define FRED(s)     FCOLOR("0", "1", s)
#define FGREEN(s)   FCOLOR("0", "2", s)
#define FYELLOW(s)  FCOLOR("0", "3", s)
#define FBLUE(s)    FCOLOR("0", "4", s)
#define FBRED(s)    FCOLOR("1", "1", s)
#define FBGREEN(s)  FCOLOR("1", "2", s)
#define FBYELLOW(s) FCOLOR("1", "3", s)
#define FBBLUE(s)   FCOLOR("1", "4", s)
#define FBWHITE(s)  FCOLOR("1", "0", s)

#endif /* DUMPM_H */