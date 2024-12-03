/*
 * NAKHBA MUBASHIR, EPL482, 11317060
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

static char *arr[4] ={
	"/dev/fifo0",
	"/dev/fifo2",
	"/dev/fifo4",
	"/dev/fifo6"
}
static char *arr2[4] ={
    "/dev/fifo1",
    "/dev/fifo3",
    "/dev/fifo5",
    "/dev/fifo7"
}

int main(void){
    int id, fd, status, i, num=0, size-write,size-read;
    char buf[], read_buf[10];
    setbuf(stdout, NULL);

    id=fork();

    if (id>0){
        buf= "prod start";
        for (i=0; i<12; i++){
            sleep(rand()%7);
            fd =open(arr[num],O_WRONLY);
            if (fd <0){
                printf("producer failed to open \n");
                exit(1);
            }
            buf[4] = i+ 'a';
            size-write = write(fd, buf, strlen(buf));
		    printf("buffer: %s, buffer arr %s, byte %d of %ld\n",
				buf,arr[num], size-writte,strlen(buf));
		    if (size_written == 0)i--;
            close(fd);
            num ++;
		    if(num > 7)num = 0;
        }
        waitpid(id,&status,0);
    }else if (id ==0){
        for (i=0; i<12; i++){
            fd =open(arr2[num],O_RDONLY);
            size-read= EOF;
            if (fd <0){
                printf("consumer failed to open \n");
                exit(1);
            }
            memset(read_buf, '\0\', 10);
            while (size_read == EOF)size_read = read(fd, read_buf, 10);
            printf("buffer read: %s, buffer arr %s, byte %d of %ld\n",
                read_buf,arr2[num], size-read,strlen(read_buf));
            close(fd);
            num ++;
            if(num > 7)num = 0;
            sleep(rand()%4;
        }
    }else{
        printf("fork failed\n");
    }
    return 0;
}
