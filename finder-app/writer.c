/*
    Assignment 2: writer.c
    Ref: https://www.coursera.org/learn/linux-system-programming-introduction-to-buildroot/supplement/U1Beh/assignment-2-instructions
    Author: Jitesh Patel

    Description:
    - small application that takes the path of the file and the string that has to be written to the file.
    - as per requriement
        - assume that the directory will be created by the caller, so app will not create any directories
        - error handling via syslog with LOG_ERR level and LOG_USER facility
        - LOG_DEBUG to log the success message "Writing <<string>> to <<file>>"

*/

// Include necessary header files
#include <stdio.h>
#include <fcntl.h>      // for constant flags like O_CREAT used in open function 
#include <sys/stat.h>   // for constant flags like S_IRWXU used in open function
#include <unistd.h>     // for using the write function as per LSP2 Chapter 2
#include <string.h>     // for using strlen function
#include <syslog.h>

// TODO: Abstract logging interface?
// TODO: Doxygen comments?

// main entry point of the application with variable number of arguments
int main(int argc, char *argv[])
{
    // declare variables - we could optimize them if requried
    int file_desc;
    char *file_path;
    char *string_data;
    ssize_t num_bytes;

    // Initialize the logging session first - as per man pages default session will use the argv[0] and user facility
    openlog(NULL, LOG_PID | LOG_CONS, LOG_USER);

    // check number of argumetns - we need only 3 including the default program name
    if (argc != 3)
    {
        syslog(LOG_ERR, "Error: Not enough arguments  - required two arguments, passed %d arguments.\n Usage: writer <file_path> <string_data> \n", argc);
        printf("Error: Not enough arguments  - required two arguments, passed %d arguments.\n Usage: writer <file_path> <string_data> \n", argc);
        closelog();
        return 1;
    }

    // extract arguments to variable
    file_path = argv[1];
    string_data = argv[2];

    // open file to write the data as per LSP2 Chapter 2
    // create file if don't exists, log errors if any
    file_desc = open(file_path, (O_CREAT | O_RDWR), (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    if (file_desc == -1)
    {
        syslog(LOG_ERR, "Error: can not open file %s\n", file_path);
        printf("Error: can not open file %s\n", file_path);
        closelog();
        return 1;       
    }
    printf("File %s opned successfully.\n", file_path);

    // write the string data to the opned file
    num_bytes = write(file_desc, string_data, strlen(string_data));
    if (num_bytes == -1)
    {
        syslog(LOG_ERR, "Error: can not write %s to file %s\n", string_data, file_path);
        printf("Error: can not write %s to file %s\n", string_data, file_path);
        closelog();
        return 1;       
    }
    printf("Data %s written to file %s successfully.\n", string_data, file_path);

    // close the file and log debug message
    if (close(file_desc) == -1)
    {
        syslog(LOG_ERR, "Error: can not close file %s\n", file_path);
        printf("Error: can not close file %s\n", file_path);
        closelog();
        return 1;           
    }
    printf("File %s closed successfully.\n", file_path);

    syslog(LOG_DEBUG, "Writing %s to %s \n", string_data, file_path);
    closelog();
    return 0;

}