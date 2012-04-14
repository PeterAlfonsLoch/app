#include "StdAfx.h"


namespace ca4
{

   application::application() :
      OAUTHLIB_CONSUMERKEY_KEY      ("oauth_consumer_key"),
      OAUTHLIB_CALLBACK_KEY         ("oauth_callback"),
      OAUTHLIB_VERSION_KEY          ("oauth_version"),
      OAUTHLIB_SIGNATUREMETHOD_KEY  ("oauth_signature_method"),
      OAUTHLIB_SIGNATURE_KEY        ("oauth_signature"),
      OAUTHLIB_TIMESTAMP_KEY        ("oauth_timestamp"),
      OAUTHLIB_NONCE_KEY            ("oauth_nonce"),
      OAUTHLIB_TOKEN_KEY            ("oauth_token"),
      OAUTHLIB_TOKENSECRET_KEY      ("oauth_token_secret"),
      OAUTHLIB_VERIFIER_KEY         ("oauth_verifier"),
      OAUTHLIB_SCREENNAME_KEY       ("screen_name"),


      OAUTHLIB_TWITTER_REQUEST_TOKEN_URL  ("http://twitter.com/oauth/request_token"),
      OAUTHLIB_TWITTER_AUTHORIZE_URL      ("http://twitter.com/oauth/authorize?oauth_token="),
      OAUTHLIB_TWITTER_ACCESS_TOKEN_URL   ("http://twitter.com/oauth/access_token"),


      /* Constants */
      TWIT_COLON ( ":"),
      TWIT_EOS ( '\0'),

      /* Miscellaneous data used to build twitter URLs*/
      TWIT_SEARCHQUERYSTRING ( "?q("),      
      TWIT_SCREENNAME ( "?screen_name("),
      TWIT_USERID ( "?user_id("),
      TWIT_EXTENSIONFORMAT ( ".xml"),
      TWIT_TARGETSCREENNAME ( "?target_screen_name("),
      TWIT_TARGETUSERID ( "?target_id("),

      /* Search URLs */
      TWIT_SEARCH_URL ( "http://search.twitter.com/search.atom"),

      /* Status URLs */
      TWIT_STATUSUPDATE_URL ( "http://twitter.com/statuses/update.xml"),
      TWIT_STATUSSHOW_URL ( "http://twitter.com/statuses/show/"),
      TWIT_STATUDESTROY_URL ( "http://twitter.com/statuses/destroy/"),

      /* Timeline URLs */
      TWIT_PUBLIC_TIMELINE_URL ( "http://twitter.com/statuses/public_timeline.xml"),
      TWIT_FEATURED_USERS_URL ( "http://twitter.com/statuses/featured.xml"),
      TWIT_FRIENDS_TIMELINE_URL ( "http://twitter.com/statuses/friends_timeline.xml"),
      TWIT_MENTIONS_URL ( "http://twitter.com/statuses/mentions.xml"),
      TWIT_USERTIMELINE_URL ( "http://twitter.com/statuses/user_timeline.xml"),

      /* Users URLs */
      TWIT_SHOWUSERS_URL ( "http://twitter.com/users/show.xml"),
      TWIT_SHOWFRIENDS_URL ( "http://twitter.com/statuses/friends.xml"),
      TWIT_SHOWFOLLOWERS_URL ( "http://twitter.com/statuses/followers.xml"),

      /* Direct messages URLs */
      TWIT_DIRECTMESSAGES_URL ( "http://twitter.com/direct_messages.xml"),
      TWIT_DIRECTMESSAGENEW_URL ( "http://twitter.com/direct_messages/new.xml"),
      TWIT_DIRECTMESSAGESSENT_URL ( "http://twitter.com/direct_messages/sent.xml"),
      TWIT_DIRECTMESSAGEDESTROY_URL ( "http://twitter.com/direct_messages/destroy/"),

      /* Friendships URLs */
      TWIT_FRIENDSHIPSCREATE_URL ( "http://twitter.com/friendships/create.xml"),
      TWIT_FRIENDSHIPSDESTROY_URL ( "http://twitter.com/friendships/destroy.xml"),
      TWIT_FRIENDSHIPSSHOW_URL ( "http://twitter.com/friendships/show.xml"),

      /* Social graphs URLs */
      TWIT_FRIENDSIDS_URL ( "http://twitter.com/friends/ids.xml"),
      TWIT_FOLLOWERSIDS_URL ( "http://twitter.com/followers/ids.xml"),

      /* Account URLs */
      TWIT_ACCOUNTRATELIMIT_URL ( "http://twitter.com/account/rate_limit_status.xml"),

      /* Favorites URLs */
      TWIT_FAVORITESGET_URL ( "http://twitter.com/favorites.xml"),
      TWIT_FAVORITECREATE_URL ( "http://twitter.com/favorites/create/"),
      TWIT_FAVORITEDESTROY_URL ( "http://twitter.com/favorites/destroy/"),

      /* Block URLs */
      TWIT_BLOCKSCREATE_URL ( "http://twitter.com/blocks/create/"),
      TWIT_BLOCKSDESTROY_URL ( "http://twitter.com/blocks/destroy/"),
    
      /* Saved Search URLs */
      TWIT_SAVEDSEARCHGET_URL ( "http://twitter.com/saved_searches.xml"),
      TWIT_SAVEDSEARCHSHOW_URL ( "http://twitter.com/saved_searches/show/"),
      TWIT_SAVEDSEARCHCREATE_URL ( "http://twitter.com/saved_searches/create.xml"),
      TWIT_SAVEDSEARCHDESTROY_URL ( "http://twitter.com/saved_searches/destroy/"),

      /* Trends URLs */
      TWIT_TRENDS_URL ( "http://api.twitter.com/1/trends.json"),
      TWIT_TRENDSDAILY_URL ( "http://api.twitter.com/1/trends/daily.json"),
      TWIT_TRENDSCURRENT_URL ( "http://api.twitter.com/1/trends/current.json"),
      TWIT_TRENDSWEEKLY_URL ( "http://api.twitter.com/1/trends/weekly.json"),
      TWIT_TRENDSAVAILABLE_URL ( "http://api.twitter.com/1/trends/available.json")

   {
      m_signal.connect(this, &::ca4::application::on_application_signal);


   }

   application::~application()
   {
   }

   bool application::base_support()
   {

      if(!ca2::application::base_support())
         return false;

      if(m_strBaseSupportId.is_empty())
      {
         gen::property_set propertyset;
         message_box("err\\developer\\base_support\\support_id_not_specified.xml", propertyset);
         return false;
      }

      return true;

   }

   bool application::initialize()
   {

      m_dwAlive = ::GetTickCount();

      if(!ca2::application::initialize())
         return false;

      if(!colorertake5::application::initialize())
         return false;

      if(is_system())
      {
         



         ::sockets::SSLInitializer ssl_init(m_psystem);




         System.m_spcopydesk.create(this);

         if(!System.m_spcopydesk->initialize())
            return false;

      }

      if(is_system()
         && command_thread().m_varTopicQuery["app"] != "netnode")
      {
         System.http().defer_auto_initialize_proxy_configuration();
      }

      return true;
   }



   void application::on_application_signal(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(signal_object, psignal, pobj);
      /*if(psignal->m_esignal == signal_exit_instance)
      {
         if(m_copydesk.is_set()
         && m_copydesk->IsWindow())
         {
            m_copydesk->DestroyWindow();
         }
      }*/
   }


   int application::exit_instance()
   {
      try
      {
         if(is_system())
         {
            if(System.m_spcopydesk.is_set())
            {
               System.m_spcopydesk->finalize();
               System.m_spcopydesk.destroy();               
            }
            System.m_splicense.detach()->release();
         }
      }
      catch(...)
      {
      }
      try
      {
         ::ca2::application::exit_instance();
      }
      catch(...)
      {
      }
      return 0;
   }

} //namespace ca8