#include "framework.h"
//#include <iostream>
//#include <memory>
#undef HMAC_SHA1


namespace hi5
{
/*
100% free public domain implementation of the SHA-1 algorithm
by Dominik Reichl <dominik.reichl@t-online.de>
Web: http://www.dominik-reichl.de/

Version 1.6 - 2005-02-07 (thanks to Howard Kapustein for patches)
- You can set the endianness in your files, no need to modify the
header file of the CSHA1 class any more
- Aligned data support
- Made support/compilation of the utility functions (ReportHash
and HashFile) optional (useful, if bytes count, for example in
embedded environments)

Version 1.5 - 2005-01-01
- 64-bit compiler compatibility added
- Made variable wiping optional (define SHA1_WIPE_VARIABLES)
- Removed unnecessary variable initializations
- ROL32 improvement for the Microsoft compiler (using _rotl)

======== Test Vectors (from FIPS PUB 180-1) ========

SHA1("abc") =
A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D

SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") =
84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1

SHA1(A million repetitions of "a") =
34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
*/

/*#ifndef ___SHA1_HDR___
#define ___SHA1_HDR___

#if !defined(SHA1_UTILITY_FUNCTIONS) && !defined(SHA1_NO_UTILITY_FUNCTIONS)
#define SHA1_UTILITY_FUNCTIONS
#endif

#include <memory.h> // Needed for memset and memcpy


#ifdef SHA1_UTILITY_FUNCTIONS
//#include <string.h> // Needed for strcat and strcpy
#endif

//#ifdef _MSC_VER
//#include <stdlib.h>
//#endif

// You can define the endian mode in your files, without modifying the SHA1
// source files. Just #define SHA1_LITTLE_ENDIAN or #define SHA1_BIG_ENDIAN
// in your files, before including the SHA1.h header file. If you don't
// define anything, the class defaults to little endian.

#if !defined(SHA1_LITTLE_ENDIAN) && !defined(SHA1_BIG_ENDIAN)
#define SHA1_LITTLE_ENDIAN
#endif

// Same here. If you want variable wiping, #define SHA1_WIPE_VARIABLES, if
// not, #define SHA1_NO_WIPE_VARIABLES. If you don't define anything, it
// defaults to wiping.

#if !defined(SHA1_WIPE_VARIABLES) && !defined(SHA1_NO_WIPE_VARIABLES)
#define SHA1_WIPE_VARIABLES
#endif

/////////////////////////////////////////////////////////////////////////////
// Define 8- and 32-bit variables

#ifndef UINT_32

#ifdef _MSC_VER

#define UINT_8  unsigned __int8
#define UINT_32 unsigned __int32

#else

#define UINT_8 unsigned char

#if (ULONG_MAX == 0xFFFFFFFF)
#define UINT_32 unsigned long
#else
#define UINT_32 uint32_t
#endif

#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// Declare SHA1 workspace

typedef union
{
   UINT_8  ca[64];
   UINT_32 l[16];
} SHA1_WORKSPACE_BLOCK;

class CSHA1
{
public:
#ifdef SHA1_UTILITY_FUNCTIONS
   // Two different formats for ReportHash(...)
   enum
   {
      REPORT_HEX = 0,
      REPORT_DIGIT = 1
   };
#endif

   // Constructor and Destructor
   CSHA1();
   ~CSHA1();

   UINT_32 m_state[5];
   UINT_32 m_count[2];
   UINT_32 __reserved1[1];
   UINT_8  m_buffer[64];
   UINT_8  m_digest[20];
   UINT_32 __reserved2[3];

   void Reset();

   // Update the hash value
   void Update(UINT_8 *data, UINT_32 len);
#ifdef SHA1_UTILITY_FUNCTIONS
   bool HashFile(char *szFileName);
#endif

   // Finalize hash and report
   void Final();

   // Report functions: as pre-formatted and raw data
#ifdef SHA1_UTILITY_FUNCTIONS
   void ReportHash(char *szReport, unsigned char uReportType = REPORT_HEX);
#endif
   void GetHash(UINT_8 *puDest);

private:
   // Private SHA-1 transformation
   void Transform(UINT_32 *state, UINT_8 *buffer);

   // Member variables
   UINT_8 m_workspace[64];
   SHA1_WORKSPACE_BLOCK *m_block; // SHA1 pointer to the byte array above
};

#endif


/*
100% free public domain implementation of the HMAC-SHA1 algorithm
by Chien-Chung, Chung (Jim Chung) <jimchung1221@gmail.com>
*/


/*#ifndef __HMAC_SHA1_H__
#define __HMAC_SHA1_H__


typedef unsigned char BYTE ;

*/


/*class oauth_hmac_context :
   public ::crypto::sha1::CContext
{
public:


   BYTE m_ipad[64];
   BYTE m_opad[64];

   enum
   {
      SHA1_DIGEST_LENGTH	= 20,
      SHA1_BLOCK_SIZE		= 64,
      HMAC_BUF_LEN		= 4096
   } ;


   void digest(void * digest, const void * text, int32_t text_len, const void * key, int32_t key_len);

   void digest(void * digest, const string & strMessage, const string & strKey);

};
*/




/*
100% free public domain implementation of the SHA-1 algorithm
by Dominik Reichl <dominik.reichl@t-online.de>
Web: http://www.dominik-reichl.de/

Version 1.6 - 2005-02-07 (thanks to Howard Kapustein for patches)
- You can set the endianness in your files, no need to modify the
header file of the CSHA1 class any more
- Aligned data support
- Made support/compilation of the utility functions (ReportHash
and HashFile) optional (useful, if bytes count, for example in
embedded environments)

Version 1.5 - 2005-01-01
- 64-bit compiler compatibility added
- Made variable wiping optional (define SHA1_WIPE_VARIABLES)
- Removed unnecessary variable initializations
- ROL32 improvement for the Microsoft compiler (using _rotl)

======== Test Vectors (from FIPS PUB 180-1) ========

SHA1("abc") =
A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D

SHA1("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq") =
84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1

SHA1(A million repetitions of "a") =
34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
*/

/*
#ifdef SHA1_UTILITY_FUNCTIONS
#define SHA1_MAX_FILE_BUFFER 8000
#endif

// Rotate x bits to the left
#ifndef ROL32
#ifdef _MSC_VER
#define ROL32(_val32, _nBits) _rotl(_val32, _nBits)
#else
#define ROL32(_val32, _nBits) (((_val32)<<(_nBits))|((_val32)>>(32-(_nBits))))
#endif
#endif

#ifdef SHA1_LITTLE_ENDIAN
#define SHABLK0(i) (m_block->l[i] = \
   (ROL32(m_block->l[i],24) & 0xFF00FF00) | (ROL32(m_block->l[i],8) & 0x00FF00FF))
#else
#define SHABLK0(i) (m_block->l[i])
#endif

#define SHABLK(i) (m_block->l[i&15] = ROL32(m_block->l[(i+13)&15] ^ m_block->l[(i+8)&15] \
   ^ m_block->l[(i+2)&15] ^ m_block->l[i&15],1))

// SHA-1 rounds
#define _R0(v,w,x,y,z,i) { z+=((w&(x^y))^y)+SHABLK0(i)+0x5A827999+ROL32(v,5); w=ROL32(w,30); }
#define _R1(v,w,x,y,z,i) { z+=((w&(x^y))^y)+SHABLK(i)+0x5A827999+ROL32(v,5); w=ROL32(w,30); }
#define _R2(v,w,x,y,z,i) { z+=(w^x^y)+SHABLK(i)+0x6ED9EBA1+ROL32(v,5); w=ROL32(w,30); }
#define _R3(v,w,x,y,z,i) { z+=(((w|x)&y)|(w&x))+SHABLK(i)+0x8F1BBCDC+ROL32(v,5); w=ROL32(w,30); }
#define _R4(v,w,x,y,z,i) { z+=(w^x^y)+SHABLK(i)+0xCA62C1D6+ROL32(v,5); w=ROL32(w,30); }

CSHA1::CSHA1()
{
   m_block = (SHA1_WORKSPACE_BLOCK *)m_workspace;

   Reset();
}

CSHA1::~CSHA1()
{
   Reset();
}

void CSHA1::Reset()
{
   // SHA1 initialization constants
   m_state[0] = 0x67452301;
   m_state[1] = 0xEFCDAB89;
   m_state[2] = 0x98BADCFE;
   m_state[3] = 0x10325476;
   m_state[4] = 0xC3D2E1F0;

   m_count[0] = 0;
   m_count[1] = 0;
}

void CSHA1::Transform(UINT_32 *state, UINT_8 *buffer)
{
   // Copy state[] to working vars
   UINT_32 a = state[0], b = state[1], ca = state[2], d = state[3], e = state[4];

   memcpy(m_block, buffer, 64);

   // 4 rounds of 20 operations each. Loop unrolled.
   _R0(a,b,ca,d,e, 0); _R0(e,a,b,ca,d, 1); _R0(d,e,a,b,ca, 2); _R0(ca,d,e,a,b, 3);
   _R0(b,ca,d,e,a, 4); _R0(a,b,ca,d,e, 5); _R0(e,a,b,ca,d, 6); _R0(d,e,a,b,ca, 7);
   _R0(ca,d,e,a,b, 8); _R0(b,ca,d,e,a, 9); _R0(a,b,ca,d,e,10); _R0(e,a,b,ca,d,11);
   _R0(d,e,a,b,ca,12); _R0(ca,d,e,a,b,13); _R0(b,ca,d,e,a,14); _R0(a,b,ca,d,e,15);
   _R1(e,a,b,ca,d,16); _R1(d,e,a,b,ca,17); _R1(ca,d,e,a,b,18); _R1(b,ca,d,e,a,19);
   _R2(a,b,ca,d,e,20); _R2(e,a,b,ca,d,21); _R2(d,e,a,b,ca,22); _R2(ca,d,e,a,b,23);
   _R2(b,ca,d,e,a,24); _R2(a,b,ca,d,e,25); _R2(e,a,b,ca,d,26); _R2(d,e,a,b,ca,27);
   _R2(ca,d,e,a,b,28); _R2(b,ca,d,e,a,29); _R2(a,b,ca,d,e,30); _R2(e,a,b,ca,d,31);
   _R2(d,e,a,b,ca,32); _R2(ca,d,e,a,b,33); _R2(b,ca,d,e,a,34); _R2(a,b,ca,d,e,35);
   _R2(e,a,b,ca,d,36); _R2(d,e,a,b,ca,37); _R2(ca,d,e,a,b,38); _R2(b,ca,d,e,a,39);
   _R3(a,b,ca,d,e,40); _R3(e,a,b,ca,d,41); _R3(d,e,a,b,ca,42); _R3(ca,d,e,a,b,43);
   _R3(b,ca,d,e,a,44); _R3(a,b,ca,d,e,45); _R3(e,a,b,ca,d,46); _R3(d,e,a,b,ca,47);
   _R3(ca,d,e,a,b,48); _R3(b,ca,d,e,a,49); _R3(a,b,ca,d,e,50); _R3(e,a,b,ca,d,51);
   _R3(d,e,a,b,ca,52); _R3(ca,d,e,a,b,53); _R3(b,ca,d,e,a,54); _R3(a,b,ca,d,e,55);
   _R3(e,a,b,ca,d,56); _R3(d,e,a,b,ca,57); _R3(ca,d,e,a,b,58); _R3(b,ca,d,e,a,59);
   _R4(a,b,ca,d,e,60); _R4(e,a,b,ca,d,61); _R4(d,e,a,b,ca,62); _R4(ca,d,e,a,b,63);
   _R4(b,ca,d,e,a,64); _R4(a,b,ca,d,e,65); _R4(e,a,b,ca,d,66); _R4(d,e,a,b,ca,67);
   _R4(ca,d,e,a,b,68); _R4(b,ca,d,e,a,69); _R4(a,b,ca,d,e,70); _R4(e,a,b,ca,d,71);
   _R4(d,e,a,b,ca,72); _R4(ca,d,e,a,b,73); _R4(b,ca,d,e,a,74); _R4(a,b,ca,d,e,75);
   _R4(e,a,b,ca,d,76); _R4(d,e,a,b,ca,77); _R4(ca,d,e,a,b,78); _R4(b,ca,d,e,a,79);

   // add the working vars back into state
   state[0] += a;
   state[1] += b;
   state[2] += ca;
   state[3] += d;
   state[4] += e;

   // Wipe variables
#ifdef SHA1_WIPE_VARIABLES
   a = b = ca = d = e = 0;
#endif
}

// Use this function to hash in binary data and strings
void CSHA1::Update(UINT_8 *data, UINT_32 len)
{
   UINT_32 i, j;

   j = (m_count[0] >> 3) & 63;

   if((m_count[0] += len << 3) < (len << 3)) m_count[1]++;

   m_count[1] += (len >> 29);

   if((j + len) > 63)
   {
      i = 64 - j;
      memcpy(&m_buffer[j], data, i);
      Transform(m_state, m_buffer);

      for(; i + 63 < len; i += 64) Transform(m_state, &data[i]);

      j = 0;
   }
   else i = 0;

   memcpy(&m_buffer[j], &data[i], len - i);
}

#ifdef SHA1_UTILITY_FUNCTIONS
// Hash in file contents
bool CSHA1::HashFile(char *szFileName)
{
   unsigned long ulFileSize, ulRest, ulBlocks;
   unsigned long i;
   UINT_8 uData[SHA1_MAX_FILE_BUFFER];
   FILE *fIn;

   if(szFileName == NULL) return false;

   fIn = fopen(szFileName, "rb");
   if(fIn == NULL) return false;

   fseek(fIn, 0, SEEK_END);
   ulFileSize = (unsigned long)ftell(fIn);
   fseek(fIn, 0, SEEK_SET);

   if(ulFileSize != 0)
   {
      ulBlocks = ulFileSize / SHA1_MAX_FILE_BUFFER;
      ulRest = ulFileSize % SHA1_MAX_FILE_BUFFER;
   }
   else
   {
      ulBlocks = 0;
      ulRest = 0;
   }

   for(i = 0; i < ulBlocks; i++)
   {
      fread(uData, 1, SHA1_MAX_FILE_BUFFER, fIn);
      Update((UINT_8 *)uData, SHA1_MAX_FILE_BUFFER);
   }

   if(ulRest != 0)
   {
      fread(uData, 1, ulRest, fIn);
      Update((UINT_8 *)uData, ulRest);
   }

   fclose(fIn); fIn = NULL;
   return true;
}
#endif

void CSHA1::Final()
{
   UINT_32 i;
   UINT_8 finalcount[8];

   for(i = 0; i < 8; i++)
      finalcount[i] = (UINT_8)((m_count[((i >= 4) ? 0 : 1)]
   >> ((3 - (i & 3)) * 8) ) & 255); // Endian independent

   Update((UINT_8 *)"\200", 1);

   while ((m_count[0] & 504) != 448)
      Update((UINT_8 *)"\0", 1);

   Update(finalcount, 8); // Cause a SHA1Transform()

   for(i = 0; i < 20; i++)
   {
      m_digest[i] = (UINT_8)((m_state[i >> 2] >> ((3 - (i & 3)) * 8) ) & 255);
   }

   // Wipe variables for security reasons
#ifdef SHA1_WIPE_VARIABLES
   i = 0;
   memset(m_buffer, 0, 64);
   memset(m_state, 0, 20);
   memset(m_count, 0, 8);
   memset(finalcount, 0, 8);
   Transform(m_state, m_buffer);
#endif
}

#ifdef SHA1_UTILITY_FUNCTIONS
// Get the final hash as a pre-formatted string
void CSHA1::ReportHash(char *szReport, unsigned char uReportType)
{
   unsigned char i;
   char szTemp[16];

   if(szReport == NULL) return;

   if(uReportType == REPORT_HEX)
   {
      sprintf(szTemp, "%02X", m_digest[0]);
      strcat(szReport, szTemp);

      for(i = 1; i < 20; i++)
      {
         sprintf(szTemp, " %02X", m_digest[i]);
         strcat(szReport, szTemp);
      }
   }
   else if(uReportType == REPORT_DIGIT)
   {
      sprintf(szTemp, "%u", m_digest[0]);
      strcat(szReport, szTemp);

      for(i = 1; i < 20; i++)
      {
         sprintf(szTemp, " %u", m_digest[i]);
         strcat(szReport, szTemp);
      }
   }
   else strcpy(szReport, "Error: Unknown report type!");
}
#endif

// Get the raw message digest
void CSHA1::GetHash(UINT_8 *puDest)
{
   memcpy(puDest, m_digest, 20);
}



/******************************************************************************
/* HMAC_SHA1.cpp : Implementation of HMAC SHA1 algorithm
/*                 Comfort to RFC 2104
/*
/*******************************************************************************/

//
//void oauth_hmac_context::digest(void * digest, const void * text, int32_t text_len, const void * key, int32_t key_len)
//{
//
//   char szReport[HMAC_BUF_LEN];
//   char SHA1_Key[HMAC_BUF_LEN];
//
//   //memset(SHA1_Key, 0, HMAC_BUF_LEN);
//
//   /* repeated 64 times for values in ipad and opad */
//   memset(m_ipad, 0x36, sizeof(m_ipad));
//   memset(m_opad, 0x5c, sizeof(m_opad));
//
//   /* STEP 1 */
//   if (key_len > SHA1_BLOCK_SIZE)
//   {
//
//      ::crypto::sha1::CContext::Init();
//      ::crypto::sha1::CContext::update(key, key_len);
//      ::crypto::sha1::CContext::Final(SHA1_Key);
//
//   }
//   else
//      memcpy(SHA1_Key, key, key_len);
//
//   /* STEP 2 */
//   for (int32_t i=0; i<sizeof(m_ipad); i++)
//   {
//      m_ipad[i] ^= SHA1_Key[i];
//   }
//
//   /* STEP 5 */
//   for (int32_t j=0; j<sizeof(m_opad); j++)
//   {
//      m_opad[j] ^= SHA1_Key[j];
//   }
//
//   /* STEP 4 */
//   ::crypto::sha1::CContext::Init();
//   ::crypto::sha1::CContext::update(m_ipad, sizeof(m_ipad));
//   ::crypto::sha1::CContext::update(text, text_len);
//   ::crypto::sha1::CContext::Final(szReport);
//
//
//
//   /*STEP 7 */
//   ::crypto::sha1::CContext::Init();
//   ::crypto::sha1::CContext::update(m_opad, sizeof(m_opad));
//   ::crypto::sha1::CContext::update(szReport, SHA1_DIGEST_LENGTH);
//   ::crypto::sha1::CContext::Final(digest);
//
//}
//
//void oauth_hmac_context::digest(void * digest, const string & strMessage, const string & strKey)
//{
//
//   ::oauth_hmac_context::digest(digest, strMessage, strMessage.length(), strKey, strKey.length());
//
//}
//

 namespace oAuthLibDefaults
   {
       /* Constants */
       const int32_t OAUTHLIB_BUFFSIZE = 1024;
//       const int32_t OAUTHLIB_BUFFSIZE_LARGE = 1024;


   };


   string char2hex( char dec )
   {
      char dig1 = (dec&0xF0)>>4;
      char dig2 = (dec&0x0F);
      if ( 0<= dig1 && dig1<= 9) dig1+=48;    //0,48 in ascii
      if (10<= dig1 && dig1<=15) dig1+=65-10; //A,65 in ascii
      if ( 0<= dig2 && dig2<= 9) dig2+=48;
      if (10<= dig2 && dig2<=15) dig2+=65-10;

      string r;
      r.append( &dig1, 1);
      r.append( &dig2, 1);
      return r;
   }

   string urlencode( const string &ca )
   {

      string escaped;
      ::count max = ca.get_length();
      for(int32_t i=0; i<max; i++)
      {
         if ( (48 <= ca[i] && ca[i] <= 57) ||//0-9
            (65 <= ca[i] && ca[i] <= 90) ||//ABC...XYZ
            (97 <= ca[i] && ca[i] <= 122) || //abc...xyz
            (ca[i]=='~' || ca[i]=='-' || ca[i]=='_' || ca[i]=='.')
            )
         {
            escaped += ca[i];
         }
         else
         {
            escaped.append("%");
            escaped.append( char2hex(ca[i]) );//converts char 255 to string "FF"
         }
      }
      return escaped;
   }
   /*++
   * @method: oauth::oauth
   *
   * @description: constructor
   *
   * @input: none
   *
   * @output: none
   *
   *--*/
   oauth::oauth(sp(::base::application) papp) :
   element(papp),
   OAUTHLIB_CONSUMERKEY_KEY("oauth_consumer_key"),
   OAUTHLIB_CALLBACK_KEY("oauth_callback"),
   OAUTHLIB_VERSION_KEY("oauth_version"),
   OAUTHLIB_SIGNATUREMETHOD_KEY("oauth_signature_method"),
   OAUTHLIB_SIGNATURE_KEY("oauth_signature"),
   OAUTHLIB_TIMESTAMP_KEY("oauth_timestamp"),
   OAUTHLIB_NONCE_KEY("oauth_nonce"),
   OAUTHLIB_TOKEN_KEY("oauth_token"),
   OAUTHLIB_TOKENSECRET_KEY("oauth_token_secret"),
   OAUTHLIB_VERIFIER_KEY("oauth_verifier"),
   OAUTHLIB_SCREENNAME_KEY("screen_name"),


   OAUTHLIB_TWITTER_REQUEST_TOKEN_URL("http://twitter.com/oauth/request_token"),
   OAUTHLIB_TWITTER_AUTHORIZE_URL("http://twitter.com/oauth/authorize?oauth_token="),
   OAUTHLIB_TWITTER_ACCESS_TOKEN_URL("https://twitter.com/oauth/access_token"),

   m_consumerKey(""),
      m_consumerSecret( "" ),
      m_oAuthTokenKey( "" ),
      m_oAuthTokenSecret( "" ),
      m_oAuthPin( "" ),
      m_nonce( "" ),
      m_timeStamp( "" ),
      m_oAuthScreenName( "" )
   {
   }

   /*++
   * @method: oauth::~oauth
   *
   * @description: destructor
   *
   * @input: none
   *
   * @output: none
   *
   *--*/
   oauth::~oauth()
   {
   }

   /*++
   * @method: oauth::getConsumerKey
   *
   * @description: this method gives consumer key that is being used currently
   *
   * @input: none
   *
   * @output: consumer key
   *
   *--*/
   void oauth::getConsumerKey(string & consumerKey )
   {
      consumerKey = m_consumerKey;
   }

   /*++
   * @method: oauth::setConsumerKey
   *
   * @description: this method saves consumer key that should be used
   *
   * @input: consumer key
   *
   * @output: none
   *
   *--*/
   void oauth::setConsumerKey(const string & consumerKey )
   {
      m_consumerKey = consumerKey;
   }

   /*++
   * @method: oauth::getConsumerSecret
   *
   * @description: this method gives consumer secret that is being used currently
   *
   * @input: none
   *
   * @output: consumer secret
   *
   *--*/
   void oauth::getConsumerSecret(string & consumerSecret )
   {
      consumerSecret = m_consumerSecret;
   }

   /*++
   * @method: oauth::setConsumerSecret
   *
   * @description: this method saves consumer secret that should be used
   *
   * @input: consumer secret
   *
   * @output: none
   *
   *--*/
   void oauth::setConsumerSecret(const string & consumerSecret )
   {
      m_consumerSecret = consumerSecret;
   }

   /*++
   * @method: oauth::getOAuthTokenKey
   *
   * @description: this method gives OAuth token (also called access token) that is being used currently
   *
   * @input: none
   *
   * @output: OAuth token
   *
   *--*/
   void oauth::getOAuthTokenKey(string & oAuthTokenKey )
   {
      oAuthTokenKey = m_oAuthTokenKey;
   }

   /*++
   * @method: oauth::setOAuthTokenKey
   *
   * @description: this method saves OAuth token that should be used
   *
   * @input: OAuth token
   *
   * @output: none
   *
   *--*/
   void oauth::setOAuthTokenKey(const string & oAuthTokenKey )
   {
      m_oAuthTokenKey = oAuthTokenKey;
   }

   /*++
   * @method: oauth::getOAuthTokenSecret
   *
   * @description: this method gives OAuth token secret that is being used currently
   *
   * @input: none
   *
   * @output: OAuth token secret
   *
   *--*/
   void oauth::getOAuthTokenSecret(string & oAuthTokenSecret )
   {
      oAuthTokenSecret = m_oAuthTokenSecret;
   }

   /*++
   * @method: oauth::setOAuthTokenSecret
   *
   * @description: this method saves OAuth token that should be used
   *
   * @input: OAuth token secret
   *
   * @output: none
   *
   *--*/
   void oauth::setOAuthTokenSecret(const string & oAuthTokenSecret )
   {
      m_oAuthTokenSecret = oAuthTokenSecret;
   }

   /*++
   * @method: oauth::getOAuthScreenName
   *
   * @description: this method gives authorized user's screenname
   *
   * @input: none
   *
   * @output: screen name
   *
   *--*/
   void oauth::getOAuthScreenName(string & oAuthScreenName )
   {
      oAuthScreenName = m_oAuthScreenName;
   }

   /*++
   * @method: oauth::setOAuthScreenName
   *
   * @description: this method sets authorized user's screenname
   *
   * @input: screen name
   *
   * @output: none
   *
   *--*/
   void oauth::setOAuthScreenName(const string & oAuthScreenName )
   {
      m_oAuthScreenName = oAuthScreenName;
   }

   /*++
   * @method: oauth::getOAuthPin
   *
   * @description: this method gives OAuth verifier PIN
   *
   * @input: none
   *
   * @output: OAuth verifier PIN
   *
   *--*/
   void oauth::getOAuthPin(string & oAuthPin )
   {
      oAuthPin = m_oAuthPin;
   }

   /*++
   * @method: oauth::setOAuthPin
   *
   * @description: this method sets OAuth verifier PIN
   *
   * @input: OAuth verifier PIN
   *
   * @output: none
   *
   *--*/
   void oauth::setOAuthPin(const string & oAuthPin )
   {
      m_oAuthPin = oAuthPin;
   }

   /*++
   * @method: oauth::generateNonceTimeStamp
   *
   * @description: this method generates nonce and timestamp for OAuth header
   *
   * @input: none
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   void oauth::generateNonceTimeStamp()
   {

      if (m_nonce.has_char() && m_timeStamp.has_char())
         return;

      char szTime[oAuthLibDefaults::OAUTHLIB_BUFFSIZE];
      char szRand[oAuthLibDefaults::OAUTHLIB_BUFFSIZE];
      memset( szTime, 0, oAuthLibDefaults::OAUTHLIB_BUFFSIZE );
      memset( szRand, 0, oAuthLibDefaults::OAUTHLIB_BUFFSIZE );
      srand((UINT) time( NULL ) );
      sprintf( szRand, "%x", rand()%1000 );
#ifdef WINDOWS
      sprintf( szTime, "%ld", (int32_t) time( NULL ) );
#elif defined __LP64
      sprintf( szTime, "%ld", (int64_t) time( NULL ) );
#else
      sprintf( szTime, "%d", (int32_t) time( NULL ) );
#endif

      m_nonce = szTime;
      m_nonce += szRand;
      m_timeStamp = szTime;
   }

   /*++
   * @method: oauth::buildOAuthTokenKeyValuePairs
   *
   * @description: this method prepares key-value pairs required for OAuth header
   *               and signature generation.
   *
   * @input: includeOAuthVerifierPin - flag to indicate whether oauth_verifer key-value
   *                                   pair needs to be included. oauth_verifer is only
   *                                   used during exchanging request token with access token.
   *         rawData - url encoded data. this is used during signature generation.
   *         oauthSignature - base64 and url encoded OAuth signature.
   *
   * @output: keyValueMap - map in which key-value pairs are populated
   *
   * @remarks: internal method
   *
   *--*/
   bool oauth::buildOAuthTokenKeyValuePairs( const bool includeOAuthVerifierPin,
      oAuthKeyValuePairs & rawData,
      const string & oauthSignature,
      oAuthKeyValuePairs& keyValueMap )
   {
      UNREFERENCED_PARAMETER(rawData);
      /* Generate nonce and timestamp if required */
      generateNonceTimeStamp();

      /* Nonce key and its value */
      keyValueMap[OAUTHLIB_NONCE_KEY] = m_nonce;

      /* Signature method, only HMAC-SHA1 as of now */
      keyValueMap[OAUTHLIB_SIGNATUREMETHOD_KEY] = string( "HMAC-SHA1" );

      /* Timestamp */
      keyValueMap[OAUTHLIB_TIMESTAMP_KEY] = m_timeStamp;

      /* Consumer key and its value */
      keyValueMap[OAUTHLIB_CONSUMERKEY_KEY] = m_consumerKey;

      /* Signature if supplied */
      if( oauthSignature.get_length() > 0 )
      {
         keyValueMap[OAUTHLIB_SIGNATURE_KEY] = oauthSignature;
      }

      /* Token */
      if( m_oAuthTokenKey.get_length() > 0 )
      {
         keyValueMap[OAUTHLIB_TOKEN_KEY] = m_oAuthTokenKey;
      }

      /* Verifier */
      if( includeOAuthVerifierPin && ( m_oAuthPin.get_length() > 0 ) )
      {
         keyValueMap[OAUTHLIB_VERIFIER_KEY] = m_oAuthPin;
      }

      /* Version */
      keyValueMap[OAUTHLIB_VERSION_KEY] = string( "1.0" );

      //keyValueMap |= rawData;

      return ( keyValueMap.get_count() > 0 ) ? true : false;
   }

   /*++
   * @method: oauth::getSignature
   *
   * @description: this method calculates HMAC-SHA1 signature of OAuth header
   *
   * @input: eType - HTTP request type
   *         rawUrl - raw url of the HTTP request
   *         rawKeyValuePairs - key-value pairs containing OAuth headers and HTTP data
   *
   * @output: oAuthSignature - base64 and url encoded signature
   *
   * @remarks: internal method
   *
   *--*/
   bool oauth::getSignature( const eOAuthHttpRequestType eType,
      const string & rawUrl,
      const oAuthKeyValuePairs& rawKeyValuePairs,
      string & oAuthSignature )
   {
      string rawParams( "" );
      string paramsSeperator( "" );
      string sigBase( "" );

      /* Initially empty signature */
      oAuthSignature = "";

      /* Build a string using key-value pairs */
      paramsSeperator = "&";
      getStringFromOAuthKeyValuePairs( rawKeyValuePairs, rawParams, paramsSeperator );

      /* Start constructing base signature string. Refer http://dev.twitter.com/auth#intro */
      switch( eType )
      {
      case eOAuthHttpGet:
         {
            sigBase = "GET&" ;
         }
         break;

      case eOAuthHttpPost:
         {
            sigBase = "POST&" ;
         }
         break;

      case eOAuthHttpDelete:
         {
            sigBase = "DELETE&" ;
         }
         break;

      default:
         {
            return false;
         }
         break;
      }
      sigBase.append(urlencode( rawUrl ) );
      sigBase.append( "&" );
      sigBase.append(urlencode( rawParams ));

      /* Now, hash the signature base string using HMAC_SHA1 class */
      string secretSigningKey;

      /* Signing key is composed of consumer_secret&token_secret */
      secretSigningKey = m_consumerSecret;
      secretSigningKey += "&" ;
      if( m_oAuthTokenSecret.has_char())
      {
         secretSigningKey += m_oAuthTokenSecret;
      }

      //secretSigningKey ="MCD8BKwGdgPHvAuvgvz4EQpqDAtx89grbuNMRd7Eh98&J6zix3FfA9LofH0awS24M3HcBYXO5nI1iYe8EfBA";

      /* SHA 1 digest is 160 bits */
      ::primitive::memory memKey;
      memKey.from_hex(secretSigningKey);



      ::primitive::memory memHmac;
      memHmac.allocate(1024 * 16);

      //hmac_context context;
      System.crypto().hmac(memHmac, sigBase, secretSigningKey);
      //context.digest(memHmac.get_data(), sigBase, secretSigningKey);


      //string strHmac;
      //System.memory_to_hex(strHmac, memHmac);

      /* Do a base64 encode of signature */
      string base64Str = System.base64().encode(memHmac.get_data(), 20);

      /* Do an url encode */
      oAuthSignature = urlencode( base64Str );

      return ( oAuthSignature.get_length() > 0 ) ? true : false;
   }

   /*++
   * @method: oauth::getOAuthHeader
   *
   * @description: this method builds OAuth header that should be used in HTTP requests to twitter
   *
   * @input: eType - HTTP request type
   *         rawUrl - raw url of the HTTP request
   *         rawData - HTTP data
   *         includeOAuthVerifierPin - flag to indicate whether or not oauth_verifier needs to included
   *                                   in OAuth header
   *
   * @output: oAuthHttpHeader - OAuth header
   *
   *--*/
   bool oauth::getOAuthHeader(const eOAuthHttpRequestType eType, const string & rawUrl, property_set & set, const bool includeOAuthVerifierPin)
   {
      property_set setHeader;
      property_set setSignature;
      string rawParams( "" );
      string oauthSignature( "" );
      string paramsSeperator( "" );
      string pureUrl;
      property_set post;

      m_nonce.Empty();
      m_timeStamp.Empty();

      if (set.has_property("post") || eType == eOAuthHttpPost)
      {
         post = set["post"].propset();
      }

      /* If URL itself contains ?key=value, then extract and put them in map */

      index nPos = rawUrl.find( "?" );
      if(nPos >= 0)
      {
         /* Get only URL */
         pureUrl = rawUrl.Mid( 0, nPos );

         /* Get only key=value data part */
         string dataPart = rawUrl.Mid( nPos + 1 );

         property_set setUrl(get_app());
         setUrl.parse_url_query(dataPart);

         setSignature.merge(setUrl);

      }
      else
      {
         pureUrl = rawUrl;
      }

      /* Build key-value pairs needed for OAuth request token, without signature */
      buildOAuthTokenKeyValuePairs(includeOAuthVerifierPin, post, string( "" ), setSignature);


      setSignature.merge(post);

      /* Get url encoded base64 signature using request type, url and parameters */
      getSignature(eType, pureUrl, setSignature, oauthSignature);

      ::hi5::oAuthKeyValuePairs pairs(get_app());
      /* Now, again build key-value pairs with signature this time */
      buildOAuthTokenKeyValuePairs(includeOAuthVerifierPin, pairs, oauthSignature, setHeader);

      /* Get OAuth header in string format */
      paramsSeperator = ", ";
      getStringFromOAuthKeyValuePairs(setHeader, rawParams, paramsSeperator);

      //const string OAUTHLIB_AUTHHEADER_STRING = "Authorization: OAuth ";
      /* Build authorization header */
      set["headers"]["Authorization"] = "OAuth " + rawParams;


      return set["headers"].propset().m_propertya.get_count() > 0 ? true : false;
   }

   /*++
   * @method: oauth::getStringFromOAuthKeyValuePairs
   *
   * @description: this method builds a sorted string from key-value pairs
   *
   * @input: rawParamMap - key-value pairs map
   *         paramsSeperator - sepearator, either & or ,
   *
   * @output: rawParams - sorted string of OAuth parameters
   *
   * @remarks: internal method
   *
   *--*/
   bool oauth::getStringFromOAuthKeyValuePairs( const oAuthKeyValuePairs& rawParamMap,
      string & rawParams,
      const char * pszSeparator )
   {
      string strSeparator(pszSeparator);
      rawParams =  "";
      if( rawParamMap.get_count() )
      {
         oAuthKeyValueList keyValueList;
         string str( "" );

         /* Push key-value pairs to a list of strings */
         keyValueList.remove_all();

         for(int32_t i=0 ; i < rawParamMap.get_count() ;i++ )
         {
            string key = rawParamMap.m_propertya[i].name();
            string value = rawParamMap.m_propertya[i].get_value();
            str = key ;
            str +=  "=" ;
            if( strSeparator == ", " )
            {
               str+= "\"" ;
            }
            str +=  value;
            if( strSeparator == ", " )
            {
               str += "\"" ;
            }
            keyValueList.add( str );
         }

         /* Sort key-value pairs based on key name */
         if( strSeparator == "&" )
         {
            keyValueList.quick_sort();

            for(int32_t i = 0; i < keyValueList.get_count(); i++)
            {
               index iFind = keyValueList[i].find("=");
               if(iFind >= 0)
               {
                  str = urlencode(keyValueList[i].Left(iFind)) + "=" + urlencode(keyValueList[i].Mid(iFind+ 1));
                  keyValueList[i] = str;
               }

            }
         }

         /* Now, form a string */
         rawParams =  keyValueList.implode(pszSeparator);
      }
      return ( rawParams.get_length() > 0 ) ? true : false;
   }

   /*++
   * @method: oauth::extractOAuthTokenKeySecret
   *
   * @description: this method extracts oauth token key and secret from
   *               twitter's HTTP response
   *
   * @input: requestTokenResponse - response from twitter
   *
   * @output: none
   *
   *--*/
   bool oauth::extractOAuthTokenKeySecret(const string & requestTokenResponse )
   {
      if( requestTokenResponse.get_length() > 0 )
      {
         index nPos = -1;
         string strDummy( "" );

         /* Get oauth_token key */
         nPos = requestTokenResponse.find(OAUTHLIB_TOKEN_KEY);
         if(nPos >=0)
         {
            nPos = nPos + OAUTHLIB_TOKEN_KEY.get_length() + strlen( "=" );
            strDummy = requestTokenResponse.Mid( nPos );
            nPos = strDummy.find( "&" );
            if( nPos >= 0)
            {
               m_oAuthTokenKey = strDummy.Mid( 0, nPos );
            }
         }

         /* Get oauth_token_secret */
         nPos = requestTokenResponse.find(OAUTHLIB_TOKENSECRET_KEY );
         if( nPos >= 0 )
         {
            nPos = nPos + OAUTHLIB_TOKENSECRET_KEY.get_length() + strlen( "=" );
            strDummy = requestTokenResponse.Mid( nPos );
            nPos = strDummy.find( "&" );
            if( nPos >= 0 )
            {
               m_oAuthTokenSecret = strDummy.Mid( 0, nPos );
            }
         }

         /* Get screen_name */
         nPos = requestTokenResponse.find(OAUTHLIB_SCREENNAME_KEY );
         if( nPos >= 0 )
         {
            nPos = nPos + OAUTHLIB_SCREENNAME_KEY.get_length() + strlen( "=" );
            strDummy = requestTokenResponse.Mid( nPos );
            m_oAuthScreenName = strDummy;
         }
      }
      return true;

   }


} // namespace core

