#pragma once

#define SQS_GLOBAL_TOP            "gt"
#define SQS_WEEK_TOP               "wt"
#define SQS_24HOUR_TOP            "24ht"
#define SQS_LAST_MONTH_TOP         "mont"
#define SQS_LAST_3_MONTH_TOP      "3mont"
#define SQS_LAST_6_MONTH_TOP      "6mont"
#define SQS_LAST_YEAR_TOP         "1yrt"
#define SQS_PER_WEEK_TOP         "pwt"
#define SQS_PER_MONTH_TOP         "pmt"
#define SQS_PER_YEAR_TOP         "pyt"
#define SQS_LAST_INSERTIONS        "li"
#define SQS_LAST_ACCESSES           "la"
#define SQS_FUN                    "fun"

#define CLICK_KARAOKE             0
#define CLICK_KARAOKE_DOWNLOAD       100
#define CLICK_KARAOKE_OPEN          110

#define CLICK_CHORD             2

#define CLICK_LYRICS             1
#define CLICK_LYRICS_KARFILE       1001
#define CLICK_LYRICS_OTHER          1015

#define CLICK_KARAOKE_TOTAL       500
#define CLICK_LYRICS_TOTAL          501
#define CLICK_CHORD_TOTAL          502



/*   // List ids
   #define LISTID_PERFORMER_CLASS "pc"
   #define LISTID_CLASS_PERFORMER "cp"
   #define LISTID_CLASS_PERFORMER_SONG "cps"
   #define LISTID_PERFORMER_SONG "ps"
   #define LISTID_SONG "s"
   #define LISTID_PERFORMER "p"

   // Songs query style
   #define SQS_GLOBAL_TOP "gt"
   #define SQS_WEEK_TOP "wt"
   #define SQS_24HOUR_TOP "24ht"
   #define SQS_LAST_INSERTIONS "li"

   // Language id
   #define LANGID_JAPANESE "ja"
   #define LANGID_ENGLISH "en"
   #define LANGID_BRAZILIAN_PORTUGUESE "pt-br"
   #define LANGID_ITALIAN "it"
   #define LANGID_FRENCH "fr"
   #define LANGID_SPANISH "es"
   #define LANGID_PORTUGUESE "pt"

   // Style id
   #define STYLEID_JAPANESE "ja"
   #define STYLEID_ENGLISH "en"
   #define STYLEID_BRAZILIAN_PORTUGUESE "pt-br"
   #define STYLEID_ITALIAN "it"
   #define STYLEID_FRENCH "fr"
   #define STYLEID_SPANISH "es"
   #define STYLEID_PORTUGUESE "pt"
   
   // SORT
   #define ORDERBY_NAME "name"
   #define ORDERBY_CLICK "click"
*/

   // List ids
   #define LISTID_PERFORMER_CLASS "slpc"  // simple list performer class
   #define LISTID_CLASS_PERFORMER "slcp" 
   #define LISTID_CLASS_PERFORMER_SONG "slcps" 
   #define LISTID_PERFORMER_SONG "slps" 
   #define LISTID_SONG "sls" 
   #define LISTID_PERFORMER "slp" 
   #define LISTID_CHORD_PERFORMER_CLASS "slchpc"  // simple list performer class
   #define LISTID_CHORD_CLASS_PERFORMER "slchcp"  // simple list performer class
   #define LISTID_CHORD_CLASS_PERFORMER_SONG "slchcps"  // simple list performer class

   // Music Song Info
   #define INFOVIEWID_SONG_GENERAL "sisi"  // simple info song info
   #define INFOVIEWID_SONG_CHORDS "sisc" 
   #define INFOVIEWID_SONG_LYRICS "sisl" 

   // Music Action
   #define PLAYVIEWID_SONG_STL1 "pls1" 

   // Songs query style
   #define SQS_GLOBAL_TOP "gt" 
   #define SQS_WEEK_TOP "wt" 
   #define SQS_24HOUR_TOP "24ht" 
   #define SQS_LAST_MONTH_TOP "mont" 
   #define SQS_LAST_3_MONTH_TOP "3mont" 
   #define SQS_LAST_6_MONTH_TOP "6mont" 
   #define SQS_LAST_YEAR_TOP "1yrt" 
   #define SQS_PER_WEEK_TOP "pwt" 
   #define SQS_PER_MONTH_TOP "pmt" 
   #define SQS_PER_YEAR_TOP "pyt" 
   #define SQS_LAST_INSERTIONS "li" 
   #define SQS_LAST_ACCESSES "la" 
   #define SQS_FUN "fun" 

   
   // SORT
   #define ORDERBY_SONGNAME "songname" 
   #define ORDERBY_PERFORMERNAME "perfsname" 
   #define ORDERBY_CLICK "click" 
   #define ORDERBY_GLOBALCLICK "gclk" 
   
   // time Outs
   #define TIMEOUT_STRTOTIME_REGISTER_SONG_CLICK_FULL_UPDATE "+11 minute" 
   
   #define SONG_CLICK_COMPILED "+111 minute" 
   
   #define CLICK_KARAOKE 0 
   #define CLICK_KARAOKE_DOWNLOAD 100 
   #define CLICK_KARAOKE_OPEN 110 

   #define CLICK_CHORD 2 
   
   #define CLICK_LYRICS 1 
   #define CLICK_LYRICS_KARFILE 1001 
   #define CLICK_LYRICS_OTHER 1015 

   #define CLICK_KARAOKE_TOTAL 500 
   #define CLICK_LYRICS_TOTAL 501 
   #define CLICK_CHORD_TOTAL 502 

