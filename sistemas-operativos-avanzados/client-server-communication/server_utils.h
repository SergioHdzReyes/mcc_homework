#ifndef MCC_CSC_SERVER_UTILS_H
#define MCC_CSC_SERVER_UTILS_H

#define LIMIT_DATA 3

struct {
  char *pid;
  char *fullname;
  char *type;
} received;

void process_client_info(char *message);

#endif
