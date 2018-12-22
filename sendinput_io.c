#include "sendinput.h"
#ifdef NO_START_FILES
#include "main.h"
#endif
#define BLOCK_SIZE 4096

char *readStdIn(size_t *size) {
  int c = 0;
  char *buf = malloc(sizeof(char) * BLOCK_SIZE);
  size_t bufSize = BLOCK_SIZE, currSize = 0;
  while ((c = getchar()) != EOF) {
    if (currSize + 1 > bufSize) {
      if (!(buf = realloc(buf, bufSize + BLOCK_SIZE))) {
        return NULL;
      }
      bufSize += BLOCK_SIZE;
    }
    buf[currSize++] = (char) c;
  }
  buf[currSize] = '\0';
  *size = currSize;
  return buf;
}

char *readFile(const char *fileName, size_t *size) {
  /* declare a file pointer */
  FILE *filePtr = fopen(fileName, "rb");
  /* quit if the file does not exist */
  if (filePtr == NULL)
    return NULL;

  /* Get the number of bytes */
  fseek(filePtr, 0, SEEK_END);
  size_t fileSize = (size_t) ftell(filePtr);

  /* reset the file position indicator to
  the beginning of the file */
  fseek(filePtr, 0, SEEK_SET);

  /* grab sufficient memory for the
  buffer to hold the text */
  char *buffer = calloc(fileSize + 1, sizeof(char));

  /* memory error */
  if (buffer == NULL)
    return NULL;

  /* copy all the text into the buffer */
  *size = fread(buffer, sizeof(char), fileSize, filePtr);
  fclose(filePtr);
  buffer[fileSize + 1] = '\0';
  return buffer;
}

void EmitError(const unsigned short errorCode) {
  fputs(ErrorInfo[errorCode], stderr);
}

#define HELP_TEXT "Sendinput utility\n" \
"Usage: sendinput_io [-|<path to file>]\n" \
"Parses sendinput command from stdin or file and exec it."

int main(int argc, char *argv[]) {
  size_t size = 0;
  char *command = NULL;
  if (argc > 1) {
    char *filePath = argv[1];
    if (filePath[0] == '-' && filePath[1] == '\0') {
      command = readStdIn(&size);
    } else {
      command = readFile(filePath, &size);
    }
    if (command) {
      ParseSendKeys(command, size);
      free(command);
      return 0;
    }
  }
  puts(HELP_TEXT);
  return 1;
}