#pragma once


namespace str
{


   // operations.hpp -- string operations for use with strings and character arrays
   // author: Guenter Berner
   //
   // $Log: operations.hpp,v $
   // Revision 1.22  2011/11/21 10:54:32  jgo
   // find_ignore_case
   //
   // Revision 1.21  2011/06/02 15:07:19  jgo
   // *** empty log message ***
   //
   // Revision 1.20  2010/04/27 13:23:44  jgo
   // x64 configuration
   //
   // Revision 1.19  2009/08/24 15:55:35  tna
   // LINUX: Added cast for "isspace".
   //
   // Revision 1.18  2008/05/21 13:42:17  alsdorf\jgo
   // BR080522150941- The parameter domain don�t work
   //
   // Revision 1.17  2008/01/25 19:13:19  alsdorf\jgo
   // BR080125110525 - Text to Speech is not working on Satellite Nodes
   //
   // Revision 1.16  2006/09/01 10:53:58  GBE
   // same string object can be used for in- and output-string as replace argument
   //
   // Revision 1.15  2006/04/24 11:40:24  GB
   // quoteForRegex -> neutralizeRegex
   // +wildcardToRegex
   //
   // Revision 1.14  2006/04/13 15:07:36  GB
   // +quoteForRegex
   //
   // Revision 1.13  2006/02/16 12:11:33  GB
   // fixed warning
   //
   // Revision 1.12  2005/12/15 10:23:50  GB
   // *** empty log message ***
   //
   // Revision 1.11  2005/11/23 09:11:18  GB
   // commented out #pragma comment(exestr,...) because it is no longer supported by VC8
   //
   // Revision 1.10  2005/11/21 13:27:29  GB
   // support for vc8
   // +multiString support
   //
   // Revision 1.9  2005/11/15 10:48:07  GB
   // removed formatted_output_conversion*() functions
   //
   // Revision 1.8  2005/08/18 10:28:46  dvl
   // Fixed return value of vsnprintf because it changed with glibc 2.1
   //
   // Revision 1.7  2005/07/05 13:10:57  GB
   // *** empty log message ***
   //
   // Revision 1.6  2005/07/05 12:13:11  GB
   // added function ::str::strprintf
   //
   // Revision 1.5  2005/06/30 09:15:25  GB
   // + copy
   // + snprintf, vsnprintf
   //
   // Revision 1.4  2005/06/24 13:06:26  THH
   // linux
   //
   // Revision 1.3  2005/06/24 12:50:28  mbo
   // Adapted
   //
   // Revision 1.2  2005/06/24 11:45:09  mbo
   // Added functions formatted_output_conversion(_va)
   //

   //////////////////////////////////////////////////////////////////////////
   //
   // comparing
   //

   // Although the compare_ignore_case functions will be sufficient in most cases,
   // see less_string_ci and equal_string_ci functors for a more sophisticated
   // version which will also handle locales/facets

   inline int32_t compare_ignore_case( const string & left, const string & right, size_t len=0 )
   {
	   if ( len ) {
   #if defined(WIN32) || defined(WIN64)
		   return _strnicmp(left.c_str(),right.c_str(),len);
   #elif defined(LINUX)
         return strnicmp_dup(left.c_str(), right.c_str(), len);
   #else
		   return strncasecmp(left.c_str(),right.c_str(),len);
   #endif
	   }
	   else {
   #if defined(WIN32) || defined(WIN64)
		   return _stricmp(left.c_str(),right.c_str());
   #elif defined(LINUX)
         return stricmp_dup(left.c_str(), right.c_str());
   #else
		   return strcasecmp(left.c_str(),right.c_str());
   #endif
	   }
   }

   inline bool equal_ignore_case( const string & left, const string & right, size_t len=0 )
   { return compare_ignore_case(left,right,len) == 0; }


   inline int32_t compare_ignore_case( const char * left, const string & right, size_t len=0 )
   {
	   if ( len ) {
   #if defined(WIN32) || defined(WIN64)
		   return _strnicmp(left,right.c_str(),len);
   #elif defined(LINUX)
         return strnicmp_dup(left, right.c_str(), len);
   #else
		   return strncasecmp(left,right.c_str(),len);
   #endif
	   }
	   else {
   #if defined(WIN32) || defined(WIN64)
		   return _stricmp(left,right.c_str());
   #elif defined(LINUX)
         return stricmp_dup(left, right.c_str());
   #else
		   return strcasecmp(left,right.c_str());
   #endif
	   }
   }

   inline bool equal_ignore_case( const char * left, const string & right, size_t len=0 )
   { return compare_ignore_case(left,right,len) == 0; }


   inline int32_t compare_ignore_case( const string & left, const char * right, size_t len=0 )
   {
	   if ( len ) {
   #if defined(WIN32) || defined(WIN64)
		   return _strnicmp(left.c_str(),right,len);
   #elif defined(LINUX)
         return strnicmp_dup(left.c_str(), right, len);
   #else
		   return strncasecmp(left.c_str(),right,len);
   #endif
	   }
	   else {
   #if defined(WIN32) || defined(WIN64)
		   return _stricmp(left.c_str(),right);
   #elif defined(LINUX)
         return stricmp_dup(left.c_str(), right);
   #else
		   return strcasecmp(left.c_str(),right);
   #endif
	   }
   }

   inline bool equal_ignore_case( const string & left, const char * right, size_t len=0 )
   { return compare_ignore_case(left,right,len) == 0; }


   inline int32_t compare_ignore_case( const char * left, const char * right, size_t len=0 )
   {
	   if ( len ) {
   #if defined(WIN32) || defined(WIN64)
		   return _strnicmp(left,right,len);
   #elif defined(LINUX)
         return strnicmp_dup(left, right, len);
   #else
		   return strncasecmp(left,right,len);
   #endif
	   }
	   else {
   #if defined(WIN32) || defined(WIN64)
		   return _stricmp(left,right);
   #elif defined(LINUX)
         return stricmp_dup(left, right);
   #else
		   return strcasecmp(left,right);
   #endif
	   }
   }

   inline bool equal_ignore_case( const char * left, const char * right, size_t len=0 )
   { return compare_ignore_case(left,right,len) == 0; }


   inline CLASS_DECL_AXIS  string  from(char ca)
   {
      string str;
      from(str, ca);
      return str;
   }

   inline CLASS_DECL_AXIS  string  from(uchar uch)
   {
      string str;
      from(str, uch);
      return str;
   }

   inline CLASS_DECL_AXIS  string  from(int16_t i)
   {
      string str;
      from(str, i);
      return str;
   }

   inline CLASS_DECL_AXIS  string  from(uint16_t ui)
   {
      string str;
      from(str, ui);
      return str;
   }

   inline CLASS_DECL_AXIS  string  from(int32_t i)
   {
      string str;
      from(str, i);
      return str;
   }

   inline CLASS_DECL_AXIS  string  from(uint32_t ui)
   {
      string str;
      from(str, ui);
      return str;
   }

   inline CLASS_DECL_AXIS  string  from(int64_t i)
   {
      string str;
      from(str, i);
      return str;
   }

   inline CLASS_DECL_AXIS  string  from(uint64_t ui)
   {
      string str;
      from(str, ui);
      return str;
   }

   inline CLASS_DECL_AXIS string from(float f)
   {
      string str;
      from(str, f);
      return str;
   }

   inline CLASS_DECL_AXIS string from(double d)
   {
      string str;
      from(str, d);
      return str;
   }

   inline CLASS_DECL_AXIS bool     trimmed_is_empty(const char * psz)
   {

      string str(psz);

      str.trim();

      return str.is_empty();

   }


} // namespace str






CLASS_DECL_AXIS const char * utf8_inc(const char * psz);
CLASS_DECL_AXIS int32_t uni_index(const char * pszUtf8);
CLASS_DECL_AXIS int32_t uni_to_utf8(char * psz, int32_t w);;
CLASS_DECL_AXIS ::count utf16_len(const char * psz);
CLASS_DECL_AXIS void utf8_to_utf16(wchar_t * pwsz, const char * psz);
CLASS_DECL_AXIS int32_t utf8_len(const wchar_t * pwsz);
CLASS_DECL_AXIS void utf16_to_utf8(char * psz, const wchar_t * pwsz);

