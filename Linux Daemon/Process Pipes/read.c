/* popen "r" */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
 FILE *read_fp;
 char buffor[BUFSIZ + 1];
 int no_of_char;
 memset(buffor, '\0', sizeof(buffor));
 read_fp = popen("uname -a", "r");
 if (read_fp != NULL) {
 no_of_char = fread(buffor, sizeof(char), BUFSIZ, read_fp);
 if (no_of_char > 0)
 printf("Result:-\n%s\n", buffor);
 pclose(read_fp);
 exit(EXIT_SUCCESS);
 }
 exit(EXIT_FAILURE);
}

