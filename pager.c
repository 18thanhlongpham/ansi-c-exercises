#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LINESPERPAGE 10
#define TRUE           1
#define FALSE          0

void printFile(char *fn) {
    FILE *f;
    int pageNum = 1, line, c, newPage = TRUE;

    if ((f = fopen(fn, "r")) != NULL) {
        while ((c = fgetc(f)) != EOF) {
            if (newPage) {
                printf("[%s] START PAGE %d\n", fn, pageNum);
                newPage = FALSE;
                line = 1;
            }

            putchar(c);

            if (c == '\n' && ++line > LINESPERPAGE) {
                printf("[%s] END PAGE %d\n", fn, pageNum);

                putchar('\n');
                newPage = TRUE;
                pageNum++;
            }
        }

        if (!newPage) {
            printf("[%s] END PAGE %d\n", fn, pageNum);
        }

        putchar('\n');
        fclose(f);
    } else {
        fprintf(stderr, "error: can't open %s\n", fn);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int i;

    if (argc < 2) {
        fputs("error: must provide files as arguments\n", stderr);
        exit(1);
    }

    for (i = 1; i < argc; i++)
        printFile(argv[i]);

    exit(0);
}
