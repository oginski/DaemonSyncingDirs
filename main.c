/* some changes here*/
/* some changes */
/* 
 * File:   main.c
 * Author: GrzegorzOginski at gmail dot com
 *
 * Created on October 23, 2014, 9:57 PM
 */

/*
 * This example daemonizes a process, writes a few log messages,
 * sleeps some seconds and terminates afterwards.
 */

/*
    Daemon Process Design
Create a normal process (Parent process)
Create a child process from within the above parent process
The process hierarchy at this stage looks like :  TERMINAL -> PARENT PROCESS -> CHILD PROCESS
Terminate the the parent process.
The child process now becomes orphan and is taken over by the init process.
Call setsid() function to run the process in new session and have a new group.
After the above step we can say that now this process becomes a daemon process without having a controlling terminal.
Change the working directory of the daemon process to root and close stdin, stdout and stderr file descriptors.
Let the main logic of daemon process run. 
 */

/*
    Features
Detect moved and renamed files and folders
Copy locked files (Volume Shadow Copy Service)
Detect conflicts and propagate deletions
Binary file comparison
Configure handling of Symbolic Links
Automate sync as a batch job
Process multiple folder pairs
Comprehensive and detailed error reporting
Copy NTFS extended attributes (compressed, encrypted, sparse)
Copy NTFS security permissions
Support long file paths with more than 260 characters
Fail-safe file copy
Cross-platform: Windows, Linux, Mac OS X
Expand environment variables like %UserProfile%
Access variable drive letters by volume name (USB sticks)
Native 64-bit support
Keep versions of deleted/updated files
Prevent disc space bottlenecks via optimal sync sequence
Full Unicode support
Highly optimized runtime performance
Include/exclude files via filter
FreeFileSync portable and local installation available
Handle daylight saving time changes on FAT/FAT32
Use macros %time%, %date%, et al. for recurring backups
Case-sensitive synchronization
Built-in locking: serialize multiple jobs running against the same network share
 */

/*      ALGORITHM STEPS TODO:
 * 1) Get dir names from argv and store in variables
 * 2) ...
 * 3)
 * 4)
 
 
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

/* test*/
static void skeleton_daemon() {
    pid_t pid = 0; // PID for future daemon process (orphaned and taken by init process)
    pid_t sid = 0; // Session ID for daemon process

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0) exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0) exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    sid = setsid();
    if (sid < 0) exit(EXIT_FAILURE);

    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
        exit(EXIT_FAILURE);

    /* Success: Let the parent terminate */
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x = 0;
    for (x = sysconf(_SC_OPEN_MAX); x > 0; x--) {
        close(x);
    }

    /* Open the log file */
    openlog("DaemonSyncingDirsLog", LOG_PID, LOG_DAEMON);
}

void daemon_logic() {




}

int main(int argc, char*argv[]) //main function, arg counter and arg vector
{
    char *pathOne = argv[1], *pathTwo = argv[2]; //stores paths from command line

    printf("argv[0], %s\n", argv[0]); //name of program
    printf("FIRST PATH: %s\n", argv[1]); //first dir path
    printf("SECOND PATH: %s\n", argv[2]); //second dir path
    printf("argc: %d\n", argc);

    skeleton_daemon(); // let's the daemon begin

    while (1) //infinity loop
    {
        //TODO: Insert daemon code here. Logic,
        daemon_logic();

        syslog(LOG_NOTICE, "First daemon started.");
        sleep(2);

        break; //infinity loop ends
    }

    syslog(LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}