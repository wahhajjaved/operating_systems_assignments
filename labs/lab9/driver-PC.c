/*
 * Wahhaj Javed, muj975, 11135711
 */

/* write end /dev/vfifofum0  */
/* read end  /dev/vfifofum1  */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>

int readEnd;
int writeEnd;

void test1() {
    int buffSize, bytes_written, bytes_read;
    char writeChar = 'a';
    char readChar;
    buffSize = 1;

    bytes_written = write(writeEnd, &writeChar, buffSize);
    if (bytes_written != buffSize) {
        printf("test1: Expected to write %d bytes but only wrote %d\n",
        buffSize, bytes_written);
    }

    bytes_read = read(readEnd, &readChar, buffSize);
    if (bytes_read != buffSize) {
        printf(
            "test1: Expected to read %d bytes but only read %d. "
            "readChars = %c\n",
            buffSize, bytes_read, readChar
        );
    }

    if (bytes_read == buffSize && readChar == writeChar) {
        printf("test1: wrote %c and read %c. test1 passed.\n",
                writeChar, readChar
        );
    }
    else {
        printf(
            "test1: characters different. "
            "writeChar = %c, readChar = %c\n",
            writeChar, readChar
        );
    }
}

void test2() {
    int buffSize, bytes_written, bytes_read;
    char writeChar = '2';
    char readChar;
    buffSize = 1;

    bytes_written = write(writeEnd, &writeChar, buffSize);
    if (bytes_written != buffSize) {
        printf("test2: Expected to write %d bytes but only wrote %d\n",
        buffSize, bytes_written);
    }

    bytes_read = read(readEnd, &readChar, buffSize);
    if (bytes_read != buffSize) {
        printf(
            "test2: Expected to read %d bytes but only read %d. "
            "readChars = %c\n",
            buffSize, bytes_read, readChar
        );
    }

    if (bytes_read == buffSize && readChar == writeChar) {
        printf("test2: wrote %c and read %c. test2 passed.\n",
                writeChar, readChar
        );
    }
    else {
        printf(
            "test2: characters different. "
            "writeChar = %c, readChar = %c\n",
            writeChar, readChar
        );
    }
}


int main(int argc, char* argv[]) {

    readEnd = open("/dev/vfifofum1", O_RDONLY);
    if (readEnd == -1){
        perror("could not open /dev/vfifofum1");
        return 1;
    }
    writeEnd = open("/dev/vfifofum0", O_WRONLY);
    if (writeEnd == -1){
        perror("could not open /dev/vfifofum0");
        return 1;
    }

    test1();
    test2();

    close(readEnd);
    close(writeEnd);

    return 0;
}