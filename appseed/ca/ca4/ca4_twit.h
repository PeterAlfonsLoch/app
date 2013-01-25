#pragma once


namespace ca4
{

   /* twitCurl class */
   class CLASS_DECL_ca twit :
      virtual public radix::object
   {
   public:


         public:
       /* cURL data */
       string m_strError;
       string m_strResponse;

       /* cURL flags */
       bool m_curlLoginParamsSet;
       gen::property_set m_setHttp;


       /* Twitter data */
       string m_twitterUsername;
       string m_twitterPassword;

       /* OAuth data */
       oauth m_oauth;

       twit(::ca::application * papp);
       virtual ~twit();

       /* Twitter OAuth authorization methods */
       oauth& get_oauth();
       bool oAuthRequestToken( string & authorizeUrl /* out */ );
       bool oAuthAccessToken();

       /* Twitter login APIs, set once and forget */
       string & getTwitterUsername();
       string & getTwitterPassword();
       void setTwitterUsername( string & userName /* in */ );
       void setTwitterPassword( string & passWord /* in */ );

       /* Twitter search APIs */
       bool search( string & query /* in */ );

       /* Twitter status APIs */
       bool statusUpdate( string & newStatus /* in */ );
       bool statusShowById( string & statusId /* in */ );
       bool statusDestroyById( string & statusId /* in */ );

       /* Twitter timeline APIs */
       bool timelinePublicGet();
       bool timelineFriendsGet();
       bool timelineUserGet( string userInfo = "" /* in */, bool isUserId = false /* in */ );
       bool featuredUsersGet();
       bool mentionsGet();

       /* Twitter user APIs */
       bool userGet( string & userInfo /* in */, bool isUserId = false /* in */ );
       bool friendsGet( string userInfo = "" /* in */, bool isUserId = false /* in */ );
       bool followersGet( string userInfo = "" /* in */, bool isUserId = false /* in */ );

       /* Twitter direct message APIs */
       bool directMessageGet();
       bool directMessageSend( string & userInfo /* in */, string & dMsg /* in */, bool isUserId = false /* in */ );
       bool directMessageGetSent();
       bool directMessageDestroyById( string & dMsgId /* in */ );

       /* Twitter friendships APIs */
       bool friendshipCreate( string & userInfo /* in */, bool isUserId = false /* in */ );
       bool friendshipDestroy( string & userInfo /* in */, bool isUserId = false /* in */ );
       bool friendshipShow( string & userInfo /* in */, bool isUserId = false /* in */ );

       /* Twitter social graphs APIs */
       bool friendsIdsGet( string & userInfo /* in */, bool isUserId = false /* in */ );
       bool followersIdsGet( string & userInfo /* in */, bool isUserId = false /* in */ );

       /* Twitter account APIs */
       bool accountRateLimitGet();

       /* Twitter favorites APIs */
       bool favoriteGet();
       bool favoriteCreate( string & statusId /* in */ );
       bool favoriteDestroy( string & statusId /* in */ );

       /* Twitter block APIs */
       bool blockCreate( string & userInfo /* in */ );
       bool blockDestroy( string & userInfo /* in */ );

       /* Twitter search APIs */
       bool savedSearchGet();
       bool savedSearchCreate( string & query /* in */ );
       bool savedSearchShow( string & searchId /* in */ );
       bool savedSearchDestroy( string & searchId /* in */ );

       /* Twitter trends APIs (JSON) */
       bool trendsGet();
       bool trendsDailyGet();
       bool trendsWeeklyGet();
       bool trendsCurrentGet();
       bool trendsAvailableGet();
    
       string get_response();

       /* Internal cURL related methods */
       int32_t saveLastWebResponse( char*& data, size_t size );



       /* Private methods */
       void prepareCurlUserPass();
       void prepareStandardParams();
       bool performGet( const string & getUrl );
       bool performGet( const string & getUrl, gen::property_set & headers );
       bool performDelete( const string & deleteUrl );
       bool performPost( const string & postUrl, gen::property_set & post );
       bool performPost( const string & postUrl, gen::property_set & headers, gen::property_set & post );

       string build_url(const char * baseUrl, const char * userInfo, bool isUserId );
   };


   /* Private functions */
   string prepare_basic_authentication(const char * inParam1, const char * inParam2 );
   


} // namespace ca4