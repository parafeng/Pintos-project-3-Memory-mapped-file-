#include <syscall.h>
#include <string.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
    // Note: Only call msg("begin") once at start
    msg ("begin");

    // Create files
    if (!create ("file1.txt", 512))
        fail ("create first file"); 
    msg ("create first file: ok");

    if (!create ("file2.txt", 512))
        fail ("create second file");
    msg ("create second file: ok");
    
    // Open files
    int fd1 = open ("file1.txt");
    int fd2 = open ("file2.txt");
    if (!(fd1 > 1 && fd2 > 1))
        fail ("open files");
    msg ("open files: ok");

    // Test read access
    char buf[100];
    if (read (fd1, buf, 10) < 0)
        fail ("read from first file");
    msg ("read from first file: ok");
    msg ("read access to file1 recorded");
    
    // Test write access  
    if (write (fd2, "test", 4) != 4)
        fail ("write to second file");
    msg ("write to second file: ok");
    msg ("write access to file2 recorded");

    // Verify read
    seek(fd1, 0);
    char verify_buf[100];
    if (read(fd1, verify_buf, 10) < 0)
        fail ("verify read access");
    msg ("verify read access: ok");
    
    // Verify write
    seek(fd2, 0); 
    char verify_write[5] = {0};
    if (read(fd2, verify_write, 4) < 0 || strcmp(verify_write, "test") != 0)
        fail ("verify written data");
    msg ("verify written data: ok");

    msg ("access verification complete");
    
    // Close files
    close (fd1);
    close (fd2); 
    
    // Note: Only call msg("end") once at end
    msg ("end");
}
