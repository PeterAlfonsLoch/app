#include "StdAfx.h"


namespace webserver
{


namespace kar
{

      page_song::page_song()
      {
         /*global $param_locale;
         global $param_style;
         global $musicdb;
         global $gtable;
         global $langstr;
         global $param_root;
         global $g_html_meta_description;*/

         m_pnavYear = NULL;
         m_pnavSemester = NULL;
         m_pnavMonth = NULL;
         m_pnavWeek = NULL;
         m_pcurNav = NULL;



         /*$params                  = &m_params;*/
         m_params                   =  geta();
         m_params["limitcount"]    = gprop("gtable")["limitcount"];

         var param_querystyle = get("slsttyp");
         if(strlen(get("funuid")) > 0)
         {
            param_querystyle = "fun";
         }

         initialize_per_per_top(m_params);

      //   print_r($params)");

         m_plist = new music::in2_list_song(
            gprop("param_query"),
            gprop("param_songid"),
            gprop("param_lyrics"),
            get("slsttyp"),
            get("order"),
            get("page"),
            m_params["limitcount"],
            get("cid"),
            get("aid"),
            get("target"),
            get("funuid"),
            m_params,
            this_url());

         string slsttyp = get("slsttyp");
         if(slsttyp == SQS_PER_YEAR_TOP
            || slsttyp == SQS_PER_MONTH_TOP
              || slsttyp == SQS_PER_WEEK_TOP
            || slsttyp == SQS_24HOUR_TOP
            || slsttyp == SQS_WEEK_TOP
            || slsttyp == SQS_LAST_MONTH_TOP
            || slsttyp == SQS_LAST_3_MONTH_TOP
            || slsttyp == SQS_LAST_6_MONTH_TOP
            || slsttyp == SQS_LAST_YEAR_TOP)
         {
            m_plist->m_bAsc = true;
         }


//         var title1       = m_title1;
//         var pagetitle1    = &m_pagetitle1;

/*         if($param_root == 'letras")
         {
            $title1 = $langstr['SongList:Letras'];
         }
         else if($param_root == 'cifras")
         {
            $title1 = $langstr['SongList:Cifras'];
         }
         else
         {
            $title1 = $langstr['SongList:Songs'];
         }*/

//         $title1 = music_getRootShortTitle();
         //$title1 = '';

         if(strlen(m_plist->m_styletitle) > 0)
         {
            m_title1 = gen::str::has_char(m_title1, "", ": ") + m_plist->m_styletitle;
         }
         if(has_param("aid"))
         {
            m_title1 = gen::str::has_char(m_title1, "", ": ") + m_plist->m_performername;
         }
         if(has_param("cid"))
         {
            m_title1 = gen::str::has_char(m_title1, "", ": ") + m_plist->m_classname;
         }
         if(m_perpertop)
         {
            if(slsttyp == SQS_PER_YEAR_TOP)
            {
               m_title1 = gen::str::has_char(m_title1, "", ": ") + m_ppt_year;
            /*            string datetime_get_month_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL);
               string datetime_get_month_short_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL);
               string datetime_get_weekday_short_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL);
               string datetime_get_weekday_str(int idx, const char * pszLocale = NULL, const char * pszStyle = NULL);*/
            }
            else if(slsttyp == SQS_PER_MONTH_TOP)
            {
               m_title1 = gen::str::has_char(m_title1, "", ": ") + m_ppt_year +  "-" + datetime_get_month_str(m_ppt_month);
            }
            else if(slsttyp == SQS_PER_WEEK_TOP)
            {
               m_title1 = gen::str::has_char(m_title1, "", ": ") + m_ppt_year + "-" + datetime_get_month_str(m_ppt_month) + '-' + m_pcurNav->m_strTitle;
            }
         }

         m_pagetitle1 == m_title1 + " - " + music().get_root_short_title();

         gprop("g_html_meta_description") = m_pagetitle1;

         AlphaSelectPerformerLinkMaker3 * plm = new AlphaSelectPerformerLinkMaker3();
         plm->m_strLang       = gprop("g_base_locale");
         plm->m_strStyle      = gprop("g_base_style");
         m_plm                = plm;

         m_pasp                = new AlphaSelectPerformer(get("target"));
         m_pasp->m_plinkmaker = m_plm;
         m_pasp->m_iaClassId.add(gen::str::atoi64(get("cid").get_string()));


/*         if(m_hasParam("aid"))
         {
            if(m_hasParam("cid"))
            {
               $templ = langstr("html:description:pagesong:aid-cid");
            }
            else
            {
               $templ = langstr("html:description:pagesong:aid");
            }
         }
         else
         {
            $templ = langstr("html:description:pagesong:aid");
         }
         $g_html_meta_description = eval("return \"$templ\";");;
         if(m_perpertop)
         {
            if(slsttyp == SQS_PER_YEAR_TOP)
            {
               $templ = langstr("html:description:pagesong:add_per_year_top");
            }
            else if(slsttyp == SQS_PER_MONTH_TOP)
            {
               $templ = langstr("html:description:pagesong:add_per_month_top");
            }
            else if(slsttyp == SQS_PER_WEEK_TOP)
            {
               $templ = langstr("html:description:pagesong:add_per_week_top");
            }
            $g_html_meta_description .= eval("return \"$templ\";");;
           }*/
      }


      //////////////////////////////////////////////////////////////////////////
      //
      //  initializePerPerTop
      //
      //////////////////////////////////////////////////////////////////////////
      void page_song::initialize_per_per_top(gen::property_set & params)
      {
         string slsttyp = get("slsttyp");
         if(slsttyp == SQS_PER_YEAR_TOP
            || slsttyp == SQS_PER_MONTH_TOP
              || slsttyp == SQS_PER_WEEK_TOP)
           {
            m_perpertop = true;
           }
           else
           {
            m_perpertop = false;
           }

         if(m_perpertop)
         {
            if(isset(get("year")))
            {
               m_ppt_year = get("year");
               if(isset(get("month")))
               {
                  m_ppt_month = get("month");
                  if(isset(get("week")))
                  {
                     m_ppt_week = get("week");
                  }
                  else
                  {
                     if(m_ppt_month == 1)
                     {
                        m_ppt_week = 1;
                     }
                     else
                     {
                        m_ppt_week = strftime("%V", System.datetime().mktime(0, 0, 0, m_ppt_month, 1, m_ppt_year));
                     }
                  }
               }
               else
               {
                  m_ppt_month = 1;
                  if(isset(get("week")))
                  {
                     m_ppt_week = get("week");
                  }
                  else
                  {
                     m_ppt_week = strftime("%V", strtotime("last monday", System.datetime().mktime(0, 0, 0, 1, 2, m_ppt_year)));
                  }
               }
            }
            else
         {
            m_ppt_year = strftime("%Y");
            if(isset(get("month")))
            {
               m_ppt_month = get("month");
               if(isset(get("week")))
               {
                  m_ppt_week = get("week");
               }
               else
               {
                  m_ppt_week = strftime("%V", strtotime("last monday, + {m_ppt_month} month", System.datetime().mktime(0, 0, 0, 1, 2, m_ppt_year)));
               }
            }
            else
            {
               m_ppt_month = strftime("%m");
               if(isset(get("week")))
               {
                  m_ppt_week = get("week");
               }
               else
               {
                  //m_ppt_week = strftime("%V"); // PHP ISO-8601:1988 week number of the given year, starting with the first week of the year with at least 4 weekdays, with Monday being the start of the week
                  m_ppt_week = strftime("%W"); // A numeric representation of the week of the year, starting with the first Monday as the first week
               }
            }
         }
         time_t ts_newyearsday = System.datetime().mktime(0, 0, 0, 1, 2, m_ppt_year);
         dprint("ts_newyearsday=$ts_newyearsday");
         time_t ts_firstmonday = strtotime("last monday", ts_newyearsday);
         dprint("ts_firstmonday=$ts_firstmonday");
         dprint("ppt_week=$ppt_week");
         var montha = musicdb().perpertop_getMonths(m_ppt_year);
   //                                                         print_r($weeka)");
         if(!montha.array_contains(m_ppt_month))
         {
            if(m_ppt_month >= 7)
            {
               dprint("m_ppt_month >= 7");
               m_ppt_month = montha[0];
               for(int i = 0; i < montha.get_count(); i++)
               {
                  int month = montha.at(i).get_integer();
                  if(month >= 7)
                  {
                     m_ppt_month = month;
                     break;
                  }
               }
            }
            else
            {
               m_ppt_month = montha[0];
            }
         }

         if(slsttyp == SQS_PER_WEEK_TOP)
            goto week_top;
         else if(slsttyp == SQS_PER_MONTH_TOP)
            goto month_top;
         else if(slsttyp == SQS_PER_MONTH_TOP)
            goto year_top;
week_top:
         {
               m_pnavWeek = new ui_nav();

               dprint("year=$ppt_year");
               dprint("month=$ppt_month");
               var weeka = musicdb().perpertop_getWeeks(m_ppt_year, m_ppt_month);
   //                                                         print_r($weeka)");
               int navcount = weeka.array_get_count();
               if(!weeka.array_contains(m_ppt_week))
               {
                  m_ppt_week = weeka[0];
               }


               for(int inav = 0; inav < navcount; inav++)
               {
                  var week = weeka[inav];
                  dprint("week=$week");
                  var link = "/songs?slsttyp="+slsttyp+"&year="+m_ppt_year+"&month="+m_ppt_month+"&week=" + week;
                  time_t ts_monday = strtotime("+ " + week + " weeks", ts_firstmonday);
                  time_t ts_sunday = strtotime("this sunday", ts_monday);
                  if(ts_sunday > time(NULL))
                  {
                     ts_sunday = time(NULL);
                  }
                  string monday = strftime("%d/%m", ts_monday);
                  string sunday = strftime("%d/%m", ts_sunday);
                  string title = monday + " - " + sunday;

                  ui_nav_item * pnavitem = new ui_nav_item;
                  pnavitem->m_bCurrent = week == m_ppt_week;
                  pnavitem->m_bEnable = true;
                  pnavitem->m_strLink = link;
                  pnavitem->m_strTitle = title;
                  m_pnavWeek->add(pnavitem);
                  if(pnavitem->m_bCurrent)
                  {
                     m_pcurNav = pnavitem;
                  }
               }
               }

month_top:
               {
               bool semestre1 = false;
               bool semestre2 = false;

               m_pnavMonth = new ui_nav;

               dprint("PER_MONTH year={m_ppt_year}<br>");
               dprint("PER_MONTH month={m_ppt_month}<br>");
   //                                                         print_r($weeka)");
               int navcount = montha.get_count();


               for(int inav = 0; inav < navcount; inav++)
               {
                  var month = montha.at(inav);
                  if((int) month <= 6)
                  {
                     semestre1 = true;
                  }
                  else
                  {
                     semestre2 = true;
                  }
                  if(m_ppt_month <= 6)
                  {
                     if(month > 6)
                     {
                        continue;
                     }
                  }
                  else
                  {
                     if(month <= 6)
                     {
                        continue;
                     }
                  }
                  dprint("month=$month");
                  var link = "/songs?slsttyp="+slsttyp+"&year="+m_ppt_year+"&month="+month;
                  var title = langstr("Month:" + month);

                  ui_nav_item * pnavitem = new ui_nav_item();
                  pnavitem->m_bCurrent = month == m_ppt_month;
                  pnavitem->m_bEnable = true;
                  pnavitem->m_strLink = link;
                  pnavitem->m_strTitle = title;
                  m_pnavMonth->add(pnavitem);
               }

               m_pnavSemester = new ui_nav;
               if(semestre1)
               {
                  ui_nav_item * pnavitem = new ui_nav_item();
                  var link = "/songs?slsttyp="+slsttyp+"&year="+m_ppt_year+"&month=1";
                  pnavitem->m_bCurrent = m_ppt_month <= 6;
                  pnavitem->m_bEnable = true;
                  pnavitem->m_strLink = link;
                  pnavitem->m_strTitle = langstr("TopSongs:Semester:1");
                  m_pnavSemester->add(pnavitem);
               }
               if(semestre2)
               {
                  ui_nav_item * pnavitem = new ui_nav_item();
                  var link = "/songs?slsttyp="+slsttyp+"&year="+m_ppt_year+"&month=7";
                  pnavitem->m_bCurrent = m_ppt_month >= 7;
                  pnavitem->m_bEnable = true;
                  pnavitem->m_strLink = link;
                  pnavitem->m_strTitle = langstr("TopSongs:Semester:2");
                  m_pnavSemester->add(pnavitem);
               }
               }

year_top:
               {
               m_pnavYear = new ui_nav();

               dprint("year=$ppt_year");
               dprint("month=$ppt_month");
               var yeara = musicdb().perpertop_getYears();
   //                                                         print_r($weeka)");
               int navcount = yeara.get_count();

               for(int inav = 0; inav < navcount; inav++)
               {
                  var year = yeara[inav];
                  dprint("year=$year");
                  var link = "/songs?slsttyp="+slsttyp+"&year="+year;
                  var title = year;

                  ui_nav_item * pnavitem = new ui_nav_item();
                  pnavitem->m_bCurrent = year == m_ppt_year;
                  pnavitem->m_bEnable = true;
                  pnavitem->m_strLink = link;
                  pnavitem->m_strTitle = title;
                  m_pnavYear->add(pnavitem);
               }
            }
         }
      params["year"]    = m_ppt_year;
      params["month"]    = m_ppt_month;
      params["week"]    = m_ppt_week;
   }

   //////////////////////////////////////////////////////////////////////////
   //
   //  printHead
   //
   //////////////////////////////////////////////////////////////////////////

   void page_song::print_head()
   {
//      veriwell_print("cssinclude()");
   //   m_list->print("CssInclude()");
      //m_list->print("_jsInclude()");

   }
   //////////////////////////////////////////////////////////////////////////
   //
   //  printBody
   //
   //////////////////////////////////////////////////////////////////////////

   void page_song::print_body()
   {
      //global $music;
      if(m_perpertop)
      {
         print(" <div style=\"display:block; height:0.2em;\"></div>");
         if(m_pnavYear != NULL)
         {
            user().karaoke_printOutTabNav70(m_pnavYear);
            print(" <div style=\"display:block; height:0.2em;\"></div>");
         }
         if(m_pnavMonth != NULL)
         {
            user().karaoke_printOutTabNav70(m_pnavSemester);
            print(" <div style=\"display:block; height:0.2em;\"></div>");
            user().karaoke_printOutTabNav70(m_pnavMonth);
            print(" <div style=\"display:block; height:0.2em;\"></div>");
         }
         if(m_pnavWeek != NULL)
         {
            user().karaoke_printOutTabNav70(m_pnavWeek);
            print(" <div style=\"display:block; height:0.2em;\"></div>");
         }
      }
      else
      {
print("\r\n\
            <div class=\"karaoke_asp_box\">\r\n\
              <span class=\"karaoke_asp\">" + langstr("karaoke_asp") +"&nbsp</span>\r\n\
         \r\n\
         ");
         if(m_pasp != NULL)
            m_pasp->out(3);
         print("</div> \r\n");
      }

      if(strlen(m_plist->m_cid) > 0)
      {
         music().printListClassInclude(m_plist->m_cid);
      }

      if(strlen(m_plist->m_aid) > 0)
      {
         music().printListArtistInclude(m_plist->m_aid);
      }

      m_plist->print_slist_preamble();
      m_plist->print_list();
      m_plist->print_slist_closure();
   }

} // namespace kar


} // namespace webserver
