#ifndef MCC_CSC_SERVER_UTILS_H
#define MCC_CSC_SERVER_UTILS_H

#define LIMIT_DATA 3

struct {
  int pid;
  char *fullname;
  int type;
} received;

void process_client_info(char *message);

#endif
