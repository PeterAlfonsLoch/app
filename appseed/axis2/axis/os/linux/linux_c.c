#include "framework_c.h"


off_t tell64(int fd)
{

   return lseek64(fd, 0, SEEK_CUR);

}
