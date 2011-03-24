#include "StdAfx.h"

namespace xml
{

   //========================================================
   // Name   : _tcschrs
   // Desc   : same with strpbrk 
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcschrs( const char * psz, const char * pszchs )
   {
      while( psz && *psz )
      {
         if( strchr( pszchs, *psz ) )
            return (char *)psz;
         psz++;
      }
      return NULL;
   }

   //========================================================
   // Name   : _tcsskip
   // Desc   : skip space
   // Param  : 
   // Return : skiped string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcsskip( const char * psz )
   {
      //while( psz && *psz == ' ' && *psz == 13 && *psz == 10 ) psz++;
      while( psz && isspace(*psz) ) psz++;
         
      return (char *)psz;
   }

   //========================================================
   // Name   : _tcsechr
   // Desc   : similar with strchr with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcsechr( const char * psz, int ch, int escape )
   {
      char * pch = (char *)psz;

      while( pch && *pch )
      {
         if( escape != 0 && *pch == escape )
            pch++;
         else
         if( *pch == ch ) 
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
   CLASS_DECL_ca int _tcselen(int escape, char * srt, char * end) 
   {
      int len = 0;
      char * pch = srt;
      if( end==NULL ) end = (char *)sizeof(long);
      char * prev_escape = NULL;
      while( pch && *pch && pch<end )
      {
         if( escape != 0 && *pch == escape && prev_escape == NULL )
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
   CLASS_DECL_ca void _tcsecpy(char * psz, int escape, char * srt, char * end)
   {
      char * pch = srt;
      if( end==NULL ) end = (char *)sizeof(long);
      char * prev_escape = NULL;
      while( pch && *pch && pch<end )
      {
         if( escape != 0 && *pch == escape && prev_escape == NULL )
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

   //========================================================
   // Name   : _tcsepbrk
   // Desc   : similar with strpbrk with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcsepbrk( const char * psz, const char * chset, int escape )
   {
      char * pch = (char *)psz;
      char * prev_escape = NULL;
      while( pch && *pch )
      {
         if( escape != 0 && *pch == escape && prev_escape == NULL )
            prev_escape = pch;
         else
         {
            prev_escape = NULL;
            if( strchr( chset, *pch ) )
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
   CLASS_DECL_ca int _tcsenicmp( const char * psz, const char * str, int len, int escape )
   {
      char * pch = (char *)psz;
      char * prev_escape = NULL;
      char * des = (char *)str;
      int i = 0;
      
      while( pch && *pch && i < len )
      {
         if( escape != 0 && *pch == escape && prev_escape == NULL )
            prev_escape = pch;
         else
         {
            prev_escape = NULL;
            if( tolower(*pch) != tolower(des[i]) )
               break;
            i++;
         }
         pch ++;
      }
      
      // find
      if( i == len )
         return 0;
      if( psz[i] > des[i] )
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
   CLASS_DECL_ca char * _tcsenistr( const char * psz, const char * str, int len, int escape )
   {
      char * pch = (char *)psz;
      char * prev_escape = NULL;
      //char * des = (char *)str;
      //int i = 0;
      
      while( pch && *pch )
      {
         if( escape != 0 && *pch == escape && prev_escape == NULL )
            prev_escape = pch;
         else
         {
            prev_escape = NULL;
            if( _tcsenicmp( pch, str, len, escape ) == 0 )
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
   CLASS_DECL_ca char * _tcseistr( const char * psz, const char * str, int escape )
   {
      int len = strlen( str );
      return _tcsenistr( psz, str, len, escape );
   }

   //========================================================
   // Name   : _SetString
   // Desc   : put string of (psz~end) on ps string
   // Param  : trim - will be trim?
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca void _SetString(char * psz, char * end, string* ps, bool trim, int escape)
   {
      //trim
      if( trim )
      {
         while( psz && psz < end && _istspace(*psz) ) psz++;
         while( (end-1) && psz < (end-1) && _istspace(*(end-1)) ) end--;
      }
      int len = end - psz;
      if( len <= 0 ) return;
      if( escape )
      {
         len = _tcselen( escape, psz, end );
         char * pss = ps->GetBufferSetLength( len );
         _tcsecpy(pss, escape, psz, end);
         ps->ReleaseBuffer(len);
      }
      else
      {
         char * pss = ps->GetBufferSetLength(len);
         memcpy(pss, psz, len);
         ps->ReleaseBuffer(len);
      }
   }


      






} // namespace xml


