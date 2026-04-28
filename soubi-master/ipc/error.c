#include "cs.h"

// Macintosh or Linux..might need to uncomment
extern int      errno;
//extern const char *const sys_errlist[];

//return string of last system call error code

char * sys_err_str(void)
{
	//char         *ptr;
	//ptr = sys_errlist[errno];
	//return ptr;

	//this is better
	return strerror(errno);
}
