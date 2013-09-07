#include "framework.h"


namespace ca2
{


   string prepare_basic_authentication(sp(base_application) papp, const char * inParam1, const char * inParam2 );


   namespace oAuthTwitterApiUrls
   {
       /* Twitter OAuth API URLs */
   };

   /* Default values used in twitcurl */
   namespace twit_defaults
   {
   };


   /* Default twitter URLs */
   namespace twitter_defaults
   {


   };


   /*++
   * @method: twit::twit
   *
   * @description: constructor
   *
   * @input: none
   *
   * @output: none
   *
   *--*/
   twit::twit(sp(base_application) papp) :
      element(papp),
      m_oauth(papp)
   {
      m_setHttp["disable_ca2_sessid"] = true;
      m_curlLoginParamsSet = false ;
   }

   /*++
   * @method: twit::~twit
   *
   * @description: destructor
   *
   * @input: none
   *
   * @output: none
   *
   *--*/
   twit::~twit()
   {
   }

   /*++
   * @method: twit::getTwitterUsername
   *
   * @description: method to get stored Twitter username
   *
   * @input: none
   *
   * @output: twitter username
   *
   *--*/
   string & twit::getTwitterUsername()
   {
      return m_twitterUsername;
   }

   /*++
   * @method: twit::getTwitterPassword
   *
   * @description: method to get stored Twitter password
   *
   * @input: none
   *
   * @output: twitter password
   *
   *--*/
   string & twit::getTwitterPassword()
   {
      return m_twitterPassword;
   }

   /*++
   * @method: twit::setTwitterUsername
   *
   * @description: method to set username
   *
   * @input: userName
   *
   * @output: none
   *
   *--*/
   void twit::setTwitterUsername( string & userName )
   {
      if( userName.get_length() )
      {
         m_twitterUsername = userName;
         m_curlLoginParamsSet = false;
      }
   }

   /*++
   * @method: twit::setTwitterPassword
   *
   * @description: method to set password
   *
   * @input: passWord
   *
   * @output: none
   *
   *--*/
   void twit::setTwitterPassword( string & passWord )
   {
      if( passWord.get_length() )
      {
         m_twitterPassword = passWord;
         m_curlLoginParamsSet = false;
      }
   }


   /*++
   * @method: twit::search
   *
   * @description: method to return tweets that match a specified query.
   *
   * @input: query - search query in string format
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::search( string & query )
   {
      bool retVal = false;
      /* Prepare URL */
      string strUrl( "" );
      strUrl = Application.TWIT_SEARCH_URL;
      strUrl.append( Application.TWIT_SEARCHQUERYSTRING );
      strUrl.append( query );

      /* Perform GET */
      retVal = performGet( strUrl );
      return retVal;
   }

   /*++
   * @method: twit::statusUpdate
   *
   * @description: method to update new status message in twitter profile
   *
   * @input: newStatus
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::statusUpdate( string & newStatus )
   {
      bool retVal = false;
      if( true && newStatus.has_char() )
      {
         /* Prepare new status message */
         property_set post(get_app());
         post["status"] = newStatus;

         /* Perform POST */
         retVal = performPost( "https://api.twitter.com/1.1/statuses/update.json", post );
      }
      return retVal;
   }

   /*++
   * @method: twit::statusShowById
   *
   * @description: method to get a status message by its id
   *
   * @input: statusId - a number in string format
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::statusShowById( string & statusId )
   {
      bool retVal = false;
      if( true && statusId.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_STATUSSHOW_URL;
         strUrl.append( statusId );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::statusDestroyById
   *
   * @description: method to delete a status message by its id
   *
   * @input: statusId - a number in string format
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::statusDestroyById( string & statusId )
   {
      bool retVal = false;
      if( true && statusId.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_STATUDESTROY_URL;
         strUrl.append( statusId );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::timelinePublicGet
   *
   * @description: method to get public timeline
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::timelinePublicGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_PUBLIC_TIMELINE_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::featuredUsersGet
   *
   * @description: method to get featured users
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::featuredUsersGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_FEATURED_USERS_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::timelineFriendsGet
   *
   * @description: method to get friends timeline
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::timelineFriendsGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_FRIENDS_TIMELINE_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::mentionsGet
   *
   * @description: method to get mentions
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::mentionsGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_MENTIONS_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::timelineUserGet
   *
   * @description: method to get mentions
   *
   * @input: userInfo - screen name or user id in string format,
   *         isUserId - true if userInfo contains an id
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::timelineUserGet( string userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_USERTIMELINE_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::userGet
   *
   * @description: method to get a user's profile
   *
   * @input: userInfo - screen name or user id in string format,
   *         isUserId - true if userInfo contains an id
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::userGet( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true && userInfo.get_length() )
      {
         /* set URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_SHOWUSERS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendsGet
   *
   * @description: method to get a user's friends
   *
   * @input: userInfo - screen name or user id in string format,
   *         isUserId - true if userInfo contains an id
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendsGet( string userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* set URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_SHOWFRIENDS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::followersGet
   *
   * @description: method to get a user's followers
   *
   * @input: userInfo - screen name or user id in string format,
   *         isUserId - true if userInfo contains an id
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::followersGet( string userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_SHOWFOLLOWERS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::directMessageGet
   *
   * @description: method to get direct messages
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::directMessageGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_DIRECTMESSAGES_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::directMessageSend
   *
   * @description: method to send direct message to a user
   *
   * @input: userInfo - screen name or user id of a user to whom message needs to be sent,
   *         dMsg - message
   *         isUserId - true if userInfo contains target user's id
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::directMessageSend( string & userInfo, string & dMsg, bool isUserId )
   {
      bool retVal = false;
      if( true && userInfo.get_length() && dMsg.get_length() )
      {
         /* Prepare new direct message */
         property_set post(get_app());
         post["text"] = dMsg;

         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_DIRECTMESSAGENEW_URL, userInfo, isUserId );

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }

   /*++
   * @method: twit::directMessageGetSent
   *
   * @description: method to get sent direct messages
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::directMessageGetSent()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_DIRECTMESSAGESSENT_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::directMessageDestroyById
   *
   * @description: method to delete direct messages by its id
   *
   * @input: dMsgId - id of direct message in string format
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::directMessageDestroyById( string & dMsgId )
   {
      bool retVal = false;
      if( true && dMsgId.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_DIRECTMESSAGEDESTROY_URL;
         strUrl.append( dMsgId );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendshipCreate
   *
   * @description: method to add a twitter user as friend (follow a user)
   *
   * @input: userInfo - user id or screen name of a user
   *         isUserId - true if userInfo contains a user id instead of screen name
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendshipCreate( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true && userInfo.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_FRIENDSHIPSCREATE_URL, userInfo, isUserId );

         /* Send some dummy data in POST */
         property_set post(get_app());
         post["text"] = "dummy";

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendshipDestroy
   *
   * @description: method to delete a twitter user from friend list (unfollow a user)
   *
   * @input: userInfo - user id or screen name of a user
   *         isUserId - true if userInfo contains a user id instead of screen name
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendshipDestroy( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true && userInfo.get_length() )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_FRIENDSHIPSDESTROY_URL, userInfo, isUserId );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendshipShow
   *
   * @description: method to show all friends
   *
   * @input: userInfo - user id or screen name of a user of whom friends need to be shown
   *         isUserId - true if userInfo contains a user id instead of screen name
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendshipShow( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_FRIENDSHIPSSHOW_URL;
         if( userInfo.get_length() )
         {
            /* Append username to the URL */
            if( isUserId )
            {
               strUrl.append( Application.TWIT_TARGETUSERID );
            }
            else
            {
               strUrl.append( Application.TWIT_TARGETSCREENNAME );
            }
            strUrl.append( userInfo );
         }

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::friendsIdsGet
   *
   * @description: method to show IDs of all friends of a twitter user
   *
   * @input: userInfo - user id or screen name of a user
   *         isUserId - true if userInfo contains a user id instead of screen name
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::friendsIdsGet( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_FRIENDSIDS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::followersIdsGet
   *
   * @description: method to show IDs of all followers of a twitter user
   *
   * @input: userInfo - user id or screen name of a user
   *         isUserId - true if userInfo contains a user id instead of screen name
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::followersIdsGet( string & userInfo, bool isUserId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = build_url(Application.TWIT_FOLLOWERSIDS_URL, userInfo, isUserId );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::accountRateLimitGet
   *
   * @description: method to get API rate limit of current user
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::accountRateLimitGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_ACCOUNTRATELIMIT_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::favoriteGet
   *
   * @description: method to get favorite users' statuses
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::favoriteGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_FAVORITESGET_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::favoriteCreate
   *
   * @description: method to favorite a status message
   *
   * @input: statusId - id in string format of the status to be favorited
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::favoriteCreate( string & statusId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_FAVORITECREATE_URL;
         strUrl.append( statusId );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Send some dummy data in POST */
         property_set post(get_app());
         post["text"] = "dummy";

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }

   /*++
   * @method: twit::favoriteDestroy
   *
   * @description: method to delete a favorited the status
   *
   * @input: statusId - id in string format of the favorite status to be deleted
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::favoriteDestroy( string & statusId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_FAVORITEDESTROY_URL;
         strUrl.append( statusId );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::blockCreate
   *
   * @description: method to block a user
   *
   * @input: userInfo - user id or screen name
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::blockCreate( string & userInfo )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_BLOCKSCREATE_URL;
         strUrl.append( userInfo );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Send some dummy data in POST */
         property_set post(get_app());
         post["text"] = "dummy";

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }

   /*++
   * @method: twit::blockDestroy
   *
   * @description: method to unblock a user
   *
   * @input: userInfo - user id or screen name
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::blockDestroy( string & userInfo )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_BLOCKSDESTROY_URL;
         strUrl.append( userInfo );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::savedSearchGet
   *
   * @description: gets authenticated user's saved search queries.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::savedSearchGet( )
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_SAVEDSEARCHGET_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::savedSearchShow
   *
   * @description: method to retrieve the data for a saved search owned by the authenticating user
   *               specified by the given id.
   *
   * @input: searchId - id in string format of the search to be displayed
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::savedSearchShow( string & searchId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_SAVEDSEARCHSHOW_URL;
         strUrl.append( searchId );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Perform GET */
         retVal = performGet( strUrl );
      }
      return retVal;
   }

   /*++
   * @method: twit::savedSearchCreate
   *
   * @description: creates a saved search for the authenticated user
   *
   * @input: query - the query of the search the user would like to save
   *
   * @output: true if POST is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::savedSearchCreate( string & query )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_SAVEDSEARCHCREATE_URL;

         /* Send some dummy data in POST */
         property_set post(get_app());
         post["query"] = query;

         /* Perform POST */
         retVal = performPost( strUrl, post );
      }
      return retVal;
   }


   /*++
   * @method: twit::savedSearchDestroy
   *
   * @description: method to destroy a saved search for the authenticated user. The search specified
   *               by id must be owned by the authenticating user.
   *
   * @input: searchId - search id of item to be deleted
   *
   * @output: true if DELETE is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::savedSearchDestroy( string & searchId )
   {
      bool retVal = false;
      if( true )
      {
         /* Prepare URL */
         string strUrl( "" );
         strUrl = Application.TWIT_SAVEDSEARCHDESTROY_URL;
         strUrl.append( searchId );
         strUrl.append( Application.TWIT_EXTENSIONFORMAT );

         /* Perform DELETE */
         retVal = performDelete( strUrl );
      }
      return retVal;
   }


   /*++
   * @method: twit::trendsGet()
   *
   * @description: gets trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_TRENDS_URL );
      }
      return retVal;
   }


   /*++
   * @method: twit::trendsDailyGet()
   *
   * @description: gets daily trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsDailyGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_TRENDSDAILY_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::trendsWeeklyGet()
   *
   * @description: gets weekly trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsWeeklyGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_TRENDSWEEKLY_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::trendsCurrentGet()
   *
   * @description: gets current trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsCurrentGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_TRENDSCURRENT_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::trendsAvailableGet()
   *
   * @description: gets available trends.
   *
   * @input: none
   *
   * @output: true if GET is success, otherwise false. This does not check http
   *          response by twitter. Use get_response() for that.
   *
   *--*/
   bool twit::trendsAvailableGet()
   {
      bool retVal = false;
      if( true )
      {
         /* Perform GET */
         retVal = performGet( Application.TWIT_TRENDSAVAILABLE_URL );
      }
      return retVal;
   }

   /*++
   * @method: twit::get_response
   *
   * @description: method to get http response for the most recent request sent.
   *               twitcurl users need to call this method and parse the XML
   *               data returned by twitter to see what has happened.
   *
   * @input: outWebResp - string in which twitter's response is supplied back to caller
   *
   * @output: none
   *
   *--*/
   string twit::get_response()
   {
      return m_strResponse;
   }



   /*++
   * @method: twit::prepareCurlUserPass
   *
   * @description: method to set twitter credentials into cURL. this is an internal method.
   *               twitcurl users should not use this method, instead use setTwitterXxx
   *               methods to set twitter username and password.
   *
   * @input: none
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   void twit::prepareCurlUserPass()
   {
      if( !m_curlLoginParamsSet )
      {
         /* set username and password */
         m_setHttp["basic_authentication"] = prepare_basic_authentication(get_app(), getTwitterUsername(), getTwitterPassword());

         /* set the flag to true indicating that twitter credentials are set in cURL */
         m_curlLoginParamsSet = true;
      }
   }

   /*++
   * @method: twit::prepareStandardParams
   *
   * @description: method to set standard params into cURL. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: none
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   void twit::prepareStandardParams()
   {
      /* Restore any custom request we may have */
      //       curl_easy_setopt( m_curlHandle, CURLOPT_CUSTOMREQUEST, NULL );


      /* Prepare username and password for twitter */
      prepareCurlUserPass();
   }

   /*++
   * @method: twit::performGet
   *
   * @description: method to send http GET request. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: getUrl - url
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   bool twit::performGet( const string & getUrl )
   {
      property_set headers;
      property_set post;
      property_set set(get_app());

      /* set OAuth header */
      m_oauth.getOAuthHeader(eOAuthHttpGet, getUrl, set, headers);

      /* Send http request */
      return Application.http().get(getUrl, m_strResponse, post, headers, m_setHttp);
   }


   /*++
   * @method: twit::performGet
   *
   * @description: method to send http GET request. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: const string & getUrl, const string & oAuthHttpHeader
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   bool twit::performGet( const string & getUrl, property_set & headers)
   {
      string dataStrDummy( "" );
      property_set post;

      /* Send http request */
      return Application.http().get(getUrl, m_strResponse, post, headers, m_setHttp);

   }

   bool twit::performPost( const string & getUrl, property_set & headers, property_set & post)
   {

      string dataStrDummy( "" );

      property_set set;
      set = m_setHttp;

      set["http_request"] = "POST";

      /* Send http request */
      return Application.http().get(getUrl, m_strResponse, post, headers, set);

   }

   /*++
   * @method: twit::performDelete
   *
   * @description: method to send http DELETE request. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: deleteUrl - url
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   bool twit::performDelete( const string & deleteUrl )
   {
      property_set headers;
      property_set post;
      property_set set(get_app());

      /* set OAuth header */
      m_oauth.getOAuthHeader( eOAuthHttpDelete, deleteUrl, set, headers);

      /* Send http request */
      return Application.http().request("DELETE", deleteUrl, m_strResponse, post, headers, m_setHttp);
   }

   /*++
   * @method: twit::performPost
   *
   * @description: method to send http POST request. this is an internal method.
   *               twitcurl users should not use this method.
   *
   * @input: postUrl - url,
   *         dataStr - data to be posted
   *
   * @output: none
   *
   * @remarks: internal method
   *
   *--*/
   bool twit::performPost( const string & postUrl, property_set & post )
   {
      property_set headers(get_app());

      /* set OAuth header */
      m_oauth.getOAuthHeader( eOAuthHttpPost, postUrl, post, headers );

      return Application.http().get(postUrl, m_strResponse, post, headers, m_setHttp);
   }

   /*++
   * @method: utilMakeCurlParams
   *
   * @description: utility function to build parameter strings in the format
   *               required by cURL ("param1:param2"). twitcurl users should
   *               not use this function.
   *
   * @input: inParam1 - first parameter,
   *         inParam2 - second parameter
   *
   * @output: outStr - built parameter
   *
   * @remarks: internal method
   *
   *--*/
   string prepare_basic_authentication(sp(base_application) papp, const char * inParam1, const char * inParam2 )
   {
      string outStr = inParam1;
      outStr += App(papp).TWIT_COLON;
      outStr += inParam2;
      return outStr;
   }

   /*++
   * @method: utilMakeUrlForUser
   *
   * @description: utility function to build url compatible to twitter. twitcurl
   *               users should not use this function.
   *
   * @input: baseUrl - base twitter url,
   *         userInfo - user name,
   *         isUserId - indicates if userInfo contains a user id or scree name
   *
   * @output: outUrl - built url
   *
   * @remarks: internal method
   *
   *--*/
   string twit::build_url( const char * baseUrl, const char * userInfo, bool isUserId )
   {
      /* Copy base URL */
      string outUrl = baseUrl;

      if(userInfo != NULL && strlen(userInfo)  > 0)
      {
         /* Append username to the URL */
         if( isUserId )
         {
            outUrl +=  Application.TWIT_USERID ;
         }
         else
         {
            outUrl +=  Application.TWIT_SCREENNAME ;
         }
         outUrl +=  userInfo ;
      }
      return outUrl;
   }

   /*++
   * @method: twit::getOAuth
   *
   * @description: method to get a reference to oAuth object.
   *
   * @input: none
   *
   * @output: reference to oAuth object
   *
   *--*/
   oauth & twit::get_oauth()
   {
      return m_oauth;
   }

   /*++
   * @method: twit::oAuthRequestToken
   *
   * @description: method to get a request token key and secret. this token
   *               will be used to get authorize user and get PIN from twitter
   *
   * @input: authorizeUrl is an output parameter. this method will set the url
   *         in this string. user should visit this link and get PIN from that page.
   *
   * @output: true if everything went sucessfully, otherwise false
   *
   *--*/
   bool twit::oAuthRequestToken( string & authorizeUrl /* out */ )
   {
      bool retVal = false;

      authorizeUrl = "" ;

      if( true )
      {
         /* Get OAuth header for request token */
         property_set headers;
         property_set post;
         property_set set(get_app());
         int64_t iTime = ::time(NULL);
         if( m_oauth.getOAuthHeader( eOAuthHttpPost,"https://twitter.com/oauth/request_token", set, headers ) )
         {
            if( performPost( "https://twitter.com/oauth/request_token", headers, post ) )
            {
               string strAuth = headers["Authorization"];
               string strDate = headers["date"];
               ::datetime::time time(iTime);
               string strDateHere = System.datetime().international().get_gmt_date_time(time);
               /* Tell OAuth object to save access token and secret from web response */
               m_oauth.extractOAuthTokenKeySecret(get_response());

               /* Get access token and secret from OAuth object */
               string oAuthTokenKey("");
               m_oauth.getOAuthTokenKey( oAuthTokenKey );

               /* Build authorize url so that user can visit in browser and get PIN */
               authorizeUrl = Application.OAUTHLIB_TWITTER_AUTHORIZE_URL;
               authorizeUrl += oAuthTokenKey;

               retVal = true;
            }
         }
      }
      return retVal;
   }

   /*++
   * @method: twit::oAuthAccessToken
   *
   * @description: method to exchange request token with access token
   *
   * @input: none
   *
   * @output: true if everything went sucessfully, otherwise false
   *
   *--*/
   bool twit::oAuthAccessToken()
   {
      bool retVal = false;

      if( true )
      {
         /* Get OAuth header for access token */
         property_set headers;
         property_set set(get_app());
         if( m_oauth.getOAuthHeader( eOAuthHttpGet, Application.OAUTHLIB_TWITTER_ACCESS_TOKEN_URL, set, headers, true ) )
         {
            if( performGet( Application.OAUTHLIB_TWITTER_ACCESS_TOKEN_URL, headers ) )
            {
               /* Tell OAuth object to save access token and secret from web response */
               string twitterResp( "" );
               twitterResp = get_response();
               m_oauth.extractOAuthTokenKeySecret( twitterResp );

               retVal = true;
            }
         }
      }
      return retVal;
   }


} // namespace ca2

