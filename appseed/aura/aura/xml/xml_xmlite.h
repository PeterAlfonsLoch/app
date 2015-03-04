#pragma once

namespace xml
{

   class document;

   //========================================================
   // Name   : _tcschrs
   // Desc   : same with strpbrk
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA char * _tcschrs( const char * psz, const char * pszchs );

   //========================================================
   // Name   : _tcsskip
   // Desc   : skip space
   // Param  :
   // Return : skiped string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA char * _tcsskip( const char * psz );

   //========================================================
   // Name   : _tcsechr
   // Desc   : similar with strchr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA char * _tcsechr( const char * psz, int32_t ch, int32_t escape );

   //========================================================
   // Name   : _tcselen
   // Desc   : similar with strlen with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA int32_t _tcselen( int32_t escape, char * srt, char * end = NULL ) ;

   //========================================================
   // Name   : _tcsecpy
   // Desc   : similar with _tcscpy with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA void _tcsecpy(char * psz, int32_t escape, char * srt, char * end = NULL);
   CLASS_DECL_AURA void _tcsecpy2(char * psz,char escape,char * srt,char * * end = NULL);

   //========================================================
   // Name   : _tcsepbrk
   // Desc   : similar with strpbrk with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA char * _tcsepbrk( const char * psz, const char * chset, int32_t escape );

   //========================================================
   // Name   : _tcsenicmp
   // Desc   : similar with strnicmp with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA int32_t _tcsenicmp( const char * psz, const char * str, strsize len, int32_t escape );

   //========================================================
   // Name   : _tcsenistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA char * _tcsenistr( const char * psz, const char * str, strsize len, int32_t escape );

   //========================================================
   // Name   : _tcseistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AURA char * _tcseistr( const char * psz, const char * str, int32_t escape );

   //========================================================
   // Name   : _SetString
   // Desc   : put string of (psz~end) on ps string
   // Param  : trim - will be trim?
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   inline void _SetString( char * psz, char * end, string* ps, bool trim, int32_t escape);
   inline void _SetString(char * psz,char * end,string* ps,bool trim); // no escape
   inline void _SetString(char * psz,char * end,string* ps); // no trim, no escape




} // namespace xml



namespace xml
{


   //========================================================
   // Name   : _SetString
   // Desc   : put string of (psz~end) on ps string
   // Param  : trim - will be trim?
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   inline void _SetString(char * psz,char * end,string* ps,bool trim,int32_t escape)
   {

      if(trim)
      {

         while(psz < end && isspace(*psz))
         {

            psz++;

         }

         while((end - 1) && psz < (end - 1) && isspace(*(end - 1)))
         {

            end--;

         }

      }

      if(psz >= end)
      {

         return;

      }

      if(escape)
      {

         char * pss = ps->GetBufferSetLength(end - psz);

         _tcsecpy2(pss,escape,psz,&end);

         ps->ReleaseBuffer(end - pss);

      }
      else
      {
         
         ps->assign(psz,end - psz);

      }

   }


   inline void _SetString(char * psz,char * end,string* ps,bool trim)
   {

      if(trim)
      {

         while(psz < end && isspace(*psz))
         {

            psz++;

         }

         while((end - 1) && psz < (end - 1) && isspace(*(end - 1)))
         {

            end--;

         }

      }

      ps->assign(psz,end - psz);

   }


   inline void _SetString(char * psz,char * end,string* ps)
   {

      ps->assign(psz,end - psz);

   }


} // namespace xml







namespace xml
{

   inline int32_t ch_isspace_dup(uchar uch)
   {
      return uch == ' ' || uch == '\t' || uch == '\r' || uch == '\n';
   }


   //========================================================
   // Name   : _tcschrs
   // Desc   : same with strpbrk
   // Param  :
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   inline char * _tcschrs(const char * psz,const char * pszchs)
   {
      while(*psz)
      {
         if(strchr(pszchs,*psz))
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
   inline char * _tcsskip(const char * psz)
   {

      while(ch_isspace_dup((uchar)*psz)) psz++;

      return (char *)psz;

   }

} // namespace xml



namespace xml
{

   // strpbrk(xml," />\t\r\n");

   inline bool is_end_open_tag_name_char(uchar ch)
   {
      return ch == ' ' || ch == '/' || ch == '>' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\0';
   }

   inline char * end_open_tag_name(char * psz)
   {
      while(!is_end_open_tag_name_char(*psz))
      {
         psz++;
      }
      return psz;
   }


} // namespace xml



