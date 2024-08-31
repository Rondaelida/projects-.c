#ifndef OPTION_GREP_H
#define OPTION_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DSIMVOL 4096

struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

void parser(int ARGC, char *ARGV[], struct options *flags, char *f_pattern);
void grep(struct options *flags, char *pattern, char *namef, int count_f);
void read_pt_file(char *name_f, char *f_pattern);

#endif