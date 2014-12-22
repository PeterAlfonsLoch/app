#include <sys/types.h>
#include <sys/param.h>
#define user user_struct
#include <sys/user.h>
#include <sys/sysctl.h>
#include <stdio.h>
#include <stdlib.h>


extern int strncmp_dup(const char * sz1, const char * sz2, int_ptr iLen);

/************************************************************************
 *
 * Returns the pid of the process name which is given as the function
 * argument.
 * In case no process found with the given name -1 will be returned.
 *
 *************************************************************************/
/*=======================================================================*/
int get_process_pid(const char * csProcessName)
{
/*=======================================================================*/

        struct kinfo_proc *sProcesses = NULL, *sNewProcesses;
        pid_t  iCurrentPid;
        int    aiNames[4];
        size_t iNamesLength;
        int    i, iRetCode, iNumProcs;
        size_t iSize;

        iSize = 0;
        aiNames[0] = CTL_KERN;
        aiNames[1] = KERN_PROC;
        aiNames[2] = KERN_PROC_ALL;
        aiNames[3] = 0;
        iNamesLength = 3;

        iRetCode = sysctl(aiNames, (u_int) iNamesLength, NULL, &iSize, NULL, 0);

        /*
         * Allocate memory and populate info in the  processes structure
         */

        do {
                iSize += iSize / 10;
                sNewProcesses = (struct kinfo_proc *) realloc(sProcesses, iSize);

                if (sNewProcesses == 0) {
                        if (sProcesses)
                                free(sProcesses);
                                throw "could not reallocate memory";
                }
                sProcesses = sNewProcesses;
                iRetCode = sysctl(aiNames, (u_int) iNamesLength, sProcesses, &iSize, NULL, 0);
        } while (iRetCode == -1 && errno == ENOMEM);

        iNumProcs = (int) (iSize / sizeof(struct kinfo_proc));
      /*
         * Search for the given process name and return its pid.
         */

        for (i = 0; i < iNumProcs; i++) {
                iCurrentPid = sProcesses[i].kp_proc.p_pid;
                if( strncmp_dup(csProcessName, sProcesses[i].kp_proc.p_comm, MAXCOMLEN) == 0 ) {
                        free(sProcesses);
                        return iCurrentPid;
                }
        }

        /*
         * Clean up and return -1 because the given proc name was not found
         */

        free(sProcesses);
        return (-1);
} /* end of getProcessId() */


