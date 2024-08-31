#ifndef OPTION_H
#define OPTION_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int T;
  int E;
} opt;

int parser(int ARGC, char *ARGV[], opt *options);
void reader(int i, char *ARGV[], opt *options);

#endif