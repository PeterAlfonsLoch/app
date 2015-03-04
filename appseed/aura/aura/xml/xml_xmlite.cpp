//#include "framework.h"

namespace xml
{



   //========================================================
   // Name   : _tcsechr
   // Desc   : similar with strchr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * _tcsechr(const char * psz,int32_t ch,int32_t escape)
   {
      char * pch = (char *)psz;

      while(pch && *pch)
      {
         if(escape != 0 && *pch == escape)
            pch++;
         else
            if(*pch == ch)
               return (char *)pch;
         pch++;
      }
      return pch;
   }

   //========================================================
   // Name   : _tcselen
   // Desc   : similar with strlen with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   int32_t _tcselen(int32_t escape,char * srt,char * end)
   {
      int32_t len = 0;
      char * pch = srt;
      if(end == NULL) end = (char *)sizeof(long);
      char * prev_escape = NULL;
      while(pch && *pch && pch < end)
      {
         if(escape != 0 && *pch == escape && prev_escape == NULL)
            prev_escape = pch;
         else
         {
            prev_escape = NULL;
            len++;
         }
         pch++;
      }
      return len;
   }

   //========================================================
   // Name   : _tcsecpy
   // Desc   : similar with _tcscpy with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   void _tcsecpy(char * psz,int32_t escape,char * srt,char * end)
   {
      char * pch = srt;
      if(end == NULL) end = (char *)sizeof(long);
      char * prev_escape = NULL;
      while(pch && *pch && pch < end)
      {
         if(escape != 0 && *pch == escape && prev_escape == NULL)
            prev_escape = pch;
         else
         {
            prev_escape = NULL;
            *psz++ = *pch;
         }

         pch++;
      }

      *psz = '\0';

   }


   void _tcsecpy2(char * psz,char escape,char * srt,char * * end)
   {
      
      char * pch = srt;
      
      bool bEscaping = false;

      while(pch < *end)
      {

         if(bEscaping)
         {

            bEscaping = false;

            *psz++ = *pch;

         }
         else if(*pch == escape)
         {

            bEscaping = true;

         }
         else
         {
            
            *psz++ = *pch;

         }

         pch++;

      }

      *psz = '\0';

      *end = psz;

   }


   //========================================================
   // Name   : _tcsepbrk
   // Desc   : similar with strpbrk with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * _tcsepbrk(const char * psz,const char * chset,int32_t escape)
   {
      char * pch = (char *)psz;
      char * prev_escape = NULL;
      while(pch && *pch)
      {
         if(escape != 0 && *pch == escape && prev_escape == NULL)
            prev_escape = pch;
         else
         {
            prev_escape = NULL;
            if(strchr(chset,*pch))
               return (char *)pch;
         }
         pch++;
      }
      return pch;
   }

   //========================================================
   // Name   : _tcsenicmp
   // Desc   : similar with strnicmp with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   int32_t _tcsenicmp(const char * psz,const char * str,strsize len,int32_t escape)
   {
      char * pch = (char *)psz;
      char * prev_escape = NULL;
      char * des = (char *)str;
      int32_t i = 0;

      while(pch && *pch && i < len)
      {
         if(escape != 0 && *pch == escape && prev_escape == NULL)
            prev_escape = pch;
         else
         {
            prev_escape = NULL;
            if(tolower(*pch) != tolower(des[i]))
               break;
            i++;
         }
         pch ++;
      }

      // find
      if(i == len)
         return 0;
      if(psz[i] > des[i])
         return 1;
      return -1;
   }

   //========================================================
   // Name   : _tcsenistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * _tcsenistr(const char * psz,const char * str,strsize len,int32_t escape)
   {
      char * pch = (char *)psz;
      char * prev_escape = NULL;
      //char * des = (char *)str;
      //int32_t i = 0;

      while(pch && *pch)
      {
         if(escape != 0 && *pch == escape && prev_escape == NULL)
            prev_escape = pch;
         else
         {
            prev_escape = NULL;
            if(_tcsenicmp(pch,str,len,escape) == 0)
               return (char *)pch;
         }
         pch++;
      }
      return pch;
   }

   //========================================================
   // Name   : _tcseistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   char * _tcseistr(const char * psz,const char * str,int32_t escape)
   {
      strsize len = strlen(str);
      return _tcsenistr(psz,str,len,escape);
   }

   








} // namespace xml










