#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint32_t;
#include "idna.h"

int main()
{
    printf("Hello world!\n");

    {

    const char * psz = "veriwell";
     char * p = NULL;

      Idna_rc rc = (Idna_rc) idna_to_ascii_8z(psz, &p, 0);

      if (rc == IDNA_SUCCESS)
      {
      printf("%s", p);
      }
      else
      {
         const char * pszError = idna_strerror(rc);
         printf(pszError);
      }


      }

    const char * psz = "www.ca2.cc";

    psz = "xn--v097e3a2b65bbb";

     const char * p = NULL;

      Idna_rc rc = (Idna_rc)idna_to_unicode_8z8z(psz, &p, IDNA_ALLOW_UNASSIGNED);

      if (rc == IDNA_SUCCESS)
      {

        printf("%s", p);

      }
      else
      {
         const char * pszError = idna_strerror(rc);
         printf(pszError);
      }

    getchar();
    return 0;
}
