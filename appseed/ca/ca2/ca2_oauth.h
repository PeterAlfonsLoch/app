#pragma once


namespace ca4
{

   CLASS_DECL_ca string char2hex( char dec );
   CLASS_DECL_ca string urlencode( const string &c );
  

   typedef enum _eOAuthHttpRequestType
   {
       eOAuthHttpInvalid = 0,
       eOAuthHttpGet,
       eOAuthHttpPost,
       eOAuthHttpDelete
   } eOAuthHttpRequestType;

   typedef stringa oAuthKeyValueList;
   typedef gen::property_set oAuthKeyValuePairs;

   class CLASS_DECL_ca oauth :
      virtual public ::gen::object
   {
   public:
       oauth(::ca::application * papp);
       virtual ~oauth();

       /* OAuth public methods used by twitCurl */
       void getConsumerKey( string& consumerKey /* out */ );
       void setConsumerKey( const string& consumerKey /* in */ );

       void getConsumerSecret( string& consumerSecret /* out */ );
       void setConsumerSecret( const string& consumerSecret /* in */ );

       void getOAuthTokenKey( string& oAuthTokenKey /* out */ );
       void setOAuthTokenKey( const string& oAuthTokenKey /* in */ );

       void getOAuthTokenSecret( string& oAuthTokenSecret /* out */ );
       void setOAuthTokenSecret( const string& oAuthTokenSecret /* in */ );

       void getOAuthScreenName( string& oAuthScreenName /* out */ );
       void setOAuthScreenName( const string& oAuthScreenName /* in */ );

       void getOAuthPin( string& oAuthPin /* out */ );
       void setOAuthPin( const string& oAuthPin /* in */ );

       bool getOAuthHeader(const eOAuthHttpRequestType eType, /* in */
                           const string& rawUrl, /* in */
                           gen::property_set & rawData, /* in */
                           gen::property_set & headers, /* out */
                           const bool includeOAuthVerifierPin = false /* in */ );

       bool extractOAuthTokenKeySecret( const string& requestTokenResponse /* in */ );

   private:

       /* OAuth data */
       string m_consumerKey;
       string m_consumerSecret;
       string m_oAuthTokenKey;
       string m_oAuthTokenSecret;
       string m_oAuthPin;
       string m_nonce;
       string m_timeStamp;
       string m_oAuthScreenName;

       /* OAuth twitter related utility methods */
       bool buildOAuthTokenKeyValuePairs( const bool includeOAuthVerifierPin, /* in */
                                          oAuthKeyValuePairs & rawData, /* in */
                                          const string& oauthSignature, /* in */
                                          oAuthKeyValuePairs& keyValueMap /* out */ );

       bool getStringFromOAuthKeyValuePairs( const oAuthKeyValuePairs& rawParamMap, /* in */
                                             string& rawParams, /* out */
                                             const char * pszSeparator /* in */ );

       bool getSignature( const eOAuthHttpRequestType eType, /* in */
                          const string& rawUrl, /* in */
                          const oAuthKeyValuePairs& rawKeyValuePairs, /* in */
                          string& oAuthSignature /* out */ );

       void generateNonceTimeStamp();
   };

} // namespace ca4