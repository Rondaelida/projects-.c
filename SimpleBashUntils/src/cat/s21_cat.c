#include "option.h"

int main(int ARGC, char *ARGV[]) {
  opt options = {0};

  if ((parser(ARGC, ARGV, &options)) == 1) {
    for (int i = optind; i < ARGC; i++) {
      reader(i, ARGV, &options);
    }
  }
  return 0;
}

int parser(int ARGC, char *ARGV[], opt *options) {
  int opt;
  int option_index;
  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {"number", no_argument, NULL, 'n'},
      {
          NULL,
          0,
          NULL,
          0,
      }};

  while ((opt = getopt_long(ARGC, ARGV, "+benstvTE", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->T = 1;
        break;
      case 'E':
        options->E = 1;
        break;
      default:
        fprintf(stderr, "cat: illegal option --%c\n", opt);
        printf("usage: cat [-benstv] [file ...]\n");
    }
  }
  return (1);
}

void reader(int i, char *ARGV[], opt *options) {
  int buf, ter = 0, flag;
  FILE *fp = fopen(ARGV[i], "r");
  if (fp == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", ARGV[i]);
  } else {
    int rev;
    int count = 1;
    while ((buf = fgetc(fp)) != EOF) {
      flag = 1;
      if (options->s) {
        if (buf == '\n') {
          ter++;
        }
        if (buf != '\n') {
          ter = 0;
        }
      }
      if ((options->s) && (ter > 2)) {
        continue;
      }
      if ((flag == 1) && (options->b)) {
        if ((buf != '\n') && (options->b) && (count == 1)) {
          printf("%6d\t", count++);
        } else if ((buf != '\n') && (options->b) && (rev == '\n')) {
          printf("%6d\t", count++);
        }
        flag++;
      }
      if ((flag == 1) && (options->n)) {
        if ((count == 1) && (options->n)) {
          printf("%6d\t", count++);
        } else if ((rev == '\n') && (options->n)) {
          printf("%6d\t", count++);
        }
        flag++;
      }
      if ((buf == '\t') && ((options->T) || (options->t))) {
        printf("^");
        buf = 'I';
      }
      if ((options->v) && ((options->e) || (options->E))) {
        if (buf == '\n') {
          printf("$");
        }
      }
      if ((options->v) && (buf != '\n') && (buf != '\t')) {
        if (((buf >= 0) && (buf < 9)) || ((buf > 10) && (buf < 32)) ||
            ((buf > 126) && (buf <= 160))) {
          printf("^");
          if (buf > 126) {
            buf = buf - 64;
          } else {
            buf = buf + 64;
          }
        }
      }
      printf("%c", buf);
      rev = buf;
    }
    fclose(fp);
    fp = NULL;
  }
}