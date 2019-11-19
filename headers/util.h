#ifndef UTIL_H
#define UTIL_H

#define CHECK_MALLOC(PTR){\
   if (!(PTR)){\
      perror(NULL);\
      exit(EXIT_FAILURE);\
   }\
}

#define PIPE_AND_CHECK(FD){\
   if (pipe(fd) == -1){\
      perror(NULL);\
      exit(EXIT_FAILURE);\
   }\
}

#define TRIM_NEWLINE(STR, POS){\
   if ((POS = strchr(buf, '\n')) != NULL){\
      *POS = '\0';\
   }\
   else{\
      perror(NULL);\
      exit(EXIT_FAILURE);\
   }\
}\

#endif
