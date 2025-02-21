
/* popen "w" */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUF_SIZ 2048
int main()
{
 FILE *write_fp;
 char buffer[BUF_SIZ + 1];
 sprintf(buffer, "Once uppon a time it was a ...\n");
 write_fp = popen("tr [a-z] [A-Z]", "w");
 if (write_fp != NULL) {
 fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
 pclose(write_fp);
 exit(EXIT_SUCCESS);
 }
 exit(EXIT_FAILURE);
}
