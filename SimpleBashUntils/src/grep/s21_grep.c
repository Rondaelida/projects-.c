#include "option_grep.h"

int main(int ARGC, char *ARGV[]) {
  char f_peattern[DSIMVOL] = {0};
  struct options flags = {0};
  parser(ARGC, ARGV, &flags, f_peattern);
  // char file[DSIMVOL] = {0};
  // printf("%s", f_peattern);
  if (!flags.f && !flags.e) {
    snprintf(f_peattern, DSIMVOL, "%s", ARGV[optind++]);
  }
  int count_f = ARGC - optind;
  for (int i = optind; i < ARGC; i++) {
    if (ARGV[i - 1][0] == '-' && strchr(ARGV[i - 1], 'f')) {
      continue;
    }
    grep(&flags, f_peattern, ARGV[i], count_f);
  }
  return 0;
}

void read_pt_file(char *name_f, char *f_pattern) {
  FILE *fp;
  fp = fopen(name_f, "r");
  if (fp != NULL) {
    // char current;
    // while ((current = fgetc(fp)) != EOF) {
    //   if (current != '\\' && current != '\n') {
    //     strcat(f_pattern, current);
    //   } else {
    //     strcat(f_pattern, "|");
    //   }
    // }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '|';
      }

      // strcat(f_pattern, "|");
      strcat(f_pattern, line);
    }
    // printf("%s    1235", f_pattern);
    return;
    if (line) free(line);
    fclose(fp);
  }
}

void parser(int argc, char *argv[], struct options *flags, char *f_pattern) {
  int opt = 0;
  const char *flag_options = "e:ivclnhsf:o";
  while ((opt = getopt_long(argc, argv, flag_options, NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        if (flags->e || flags->f) {
          strcat(f_pattern, "|");
          strcat(f_pattern, optarg);
        } else {
          strcat(f_pattern, optarg);
        }
        flags->e = 1;
        // snprintf(f_pattern, DSIMVOL, "%s", optarg);
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        read_pt_file(optarg, f_pattern);
        flags->f = 1;
        // sprintf(f_pattern, "%s", optarg);
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        fprintf(stderr, "grep: illegal option -- %c\n", opt);
        printf("usage: grep [eivclnhsfo] [file ...]\n");
        break;
    }
  }
}

void grep(struct options *flags, char *pattern, char *namef, int count_f) {
  char text[DSIMVOL] = {0};
  regex_t reg;
  FILE *fp;
  fp = fopen(namef, "r");
  if (fp != NULL) {
    if (flags->i) {
      regcomp(&reg, pattern, REG_ICASE | REG_EXTENDED);
    } else {
      regcomp(&reg, pattern, REG_EXTENDED);
    }
    regmatch_t pmatch[1];
    int line = 0, nl = 1;
    while (fgets(text, DSIMVOL - 1, fp) != NULL) {
      int match = 0;
      int success = regexec(&reg, text, 1, pmatch, 0);
      if (strchr(text, '\n') == NULL) {
        strcat(text, "\n");
      }
      if (success == 0 && !flags->v) {
        match = 1;
      }
      if (success == REG_NOMATCH && flags->v) {
        match = 1;
      }
      if (match && !flags->l && !flags->c && count_f > 1 && !flags->h) {
        printf("%s:", namef);
      }
      if (match && !flags->l && !flags->c && flags->n) {
        printf("%d:", nl);
      }
      if (match && !flags->l && !flags->c && !flags->o) {
        printf("%s", text);
      }
      if (match && flags->o && !flags->h && !flags->c) {
        int rez = 0;
        char *new_arr_string = text;
        int output_num = 0;
        while (pmatch[0].rm_so != -1) {
          output_num = (int)(pmatch[0].rm_eo - pmatch[0].rm_so);
          printf("%.*s\n", output_num, &new_arr_string[pmatch[0].rm_so]);
          new_arr_string = &new_arr_string[pmatch[0].rm_eo];
          if (0 != (rez = regexec(&reg, new_arr_string, 1, pmatch, 0))) {
            pmatch[0].rm_so = -1;
          }
        }  // rm_eo -  cмещение конца подстроки в строке
        // rm_so - cмещение начала подстроки в строке
        // for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
        //   printf("%c", text[i]);
        // }
        // printf("\n");
      }
      line += match;
      nl++;
    }
    if (flags->l && flags->c) {
      printf("%s:1\n", namef);
    }
    if (flags->l && line > 0) {
      printf("%s\n", namef);
    }
    if (flags->c && !flags->l) {
      if (count_f > 1) {
        printf("%s:", namef);
      }
      printf("%d\n", line);
    }

    regfree(&reg);
    fclose(fp);
  }
}