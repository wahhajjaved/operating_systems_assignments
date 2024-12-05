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
    char writeChars[10] = "aabbccddee";
    char readChars[10];
    buffSize = 10;

    bytes_written = write(writeEnd, writeChars, buffSize);
    if (bytes_written != buffSize) {
        printf("test1: Expected to write %d bytes but only wrote %d\n",
        buffSize, bytes_written);
    }

    bytes_read = read(readEnd, readChars, buffSize);
    if (bytes_read != buffSize) {
        printf("test1: Expected to read %d bytes but only read %d\n",
        buffSize, bytes_read);
    }

    if (bytes_read == buffSize) {
        int i;
        for(i = 0; i < buffSize; i++) {
            if (writeChars[i] != readChars[i]) {
                printf(
                    "test1: characters at position %d are different. "
                    "writeChars = %s, readChars = %s",
                    i, writeChars, readChars
                );
            }
        }
    }
}


int main(int argc, char* argv[]) {

    readEnd = open("/dev/vfifofum1", O_RDONLY);
    writeEnd = open("/dev/vfifofum0", O_WRONLY);

    if (readEnd == -1)
        errx(1, "could not open /dev/vfifofum1");
    if (writeEnd == -1)
        errx(1, "could not open /dev/vfifofum0");

    test1();

    close(readEnd);
    close(writeEnd);

    return 0;
}