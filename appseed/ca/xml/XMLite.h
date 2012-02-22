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
   CLASS_DECL_ca char * _tcschrs( const char * psz, const char * pszchs );

   //========================================================
   // Name   : _tcsskip
   // Desc   : skip space
   // Param  : 
   // Return : skiped string
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcsskip( const char * psz );

   //========================================================
   // Name   : _tcsechr
   // Desc   : similar with strchr with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcsechr( const char * psz, int ch, int escape );

   //========================================================
   // Name   : _tcselen
   // Desc   : similar with strlen with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca int _tcselen( int escape, char * srt, char * end = NULL ) ;

   //========================================================
   // Name   : _tcsecpy
   // Desc   : similar with _tcscpy with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca void _tcsecpy( char * psz, int escape, char * srt, char * end = NULL );

   //========================================================
   // Name   : _tcsepbrk
   // Desc   : similar with strpbrk with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcsepbrk( const char * psz, const char * chset, int escape );

   //========================================================
   // Name   : _tcsenicmp
   // Desc   : similar with strnicmp with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca int _tcsenicmp( const char * psz, const char * str, strsize len, int escape );

   //========================================================
   // Name   : _tcsenistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcsenistr( const char * psz, const char * str, strsize len, int escape );

   //========================================================
   // Name   : _tcseistr
   // Desc   : similar with _tcsistr with escape process
   // Param  : escape - will be escape character
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca char * _tcseistr( const char * psz, const char * str, int escape );

   //========================================================
   // Name   : _SetString
   // Desc   : put string of (psz~end) on ps string
   // Param  : trim - will be trim?
   // Return : 
   //--------------------------------------------------------
   // Coder    Date                      Desc
   // bro      2002-10-29
   //========================================================
   CLASS_DECL_ca void _SetString( char * psz, char * end, string* ps, bool trim = FALSE, int escape = 0 );




} // namespace xml