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
   CLASS_DECL_AXIS char * _tcschrs( const char * psz, const char * pszchs );

   //========================================================
   // Name   : _tcsskip
   // Desc   : skip space
   // Param  :
   // Return : skiped string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS char * _tcsskip( const char * psz );

   //========================================================
   // Name   : _tcsechr
   // Desc   : similar with strchr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS char * _tcsechr( const char * psz, int32_t ch, int32_t escape );

   //========================================================
   // Name   : _tcselen
   // Desc   : similar with strlen with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS int32_t _tcselen( int32_t escape, char * srt, char * end = NULL ) ;

   //========================================================
   // Name   : _tcsecpy
   // Desc   : similar with _tcscpy with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS void _tcsecpy( char * psz, int32_t escape, char * srt, char * end = NULL );

   //========================================================
   // Name   : _tcsepbrk
   // Desc   : similar with strpbrk with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS char * _tcsepbrk( const char * psz, const char * chset, int32_t escape );

   //========================================================
   // Name   : _tcsenicmp
   // Desc   : similar with strnicmp with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS int32_t _tcsenicmp( const char * psz, const char * str, strsize len, int32_t escape );

   //========================================================
   // Name   : _tcsenistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS char * _tcsenistr( const char * psz, const char * str, strsize len, int32_t escape );

   //========================================================
   // Name   : _tcseistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS char * _tcseistr( const char * psz, const char * str, int32_t escape );

   //========================================================
   // Name   : _SetString
   // Desc   : put string of (psz~end) on ps string
   // Param  : trim - will be trim?
   // Return :
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_AXIS void _SetString( char * psz, char * end, string* ps, bool trim = FALSE, int32_t escape = 0 );




} // namespace xml
