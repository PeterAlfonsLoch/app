#include "framework.h"


namespace calculator
{


   plain_edit_view::plain_edit_view(::aura::application * papp):
      object(papp),
      ::user::interaction(papp),
      ::user::plain_edit(papp)
   {
      
      m_pcallback = NULL;

      m_val.m_dR = 0.0;
      m_val.m_dI = 0.0;
 
   }

   plain_edit_view::~plain_edit_view()
   {

   }


   void plain_edit_view::on_update(::user::impact * pSender,LPARAM lHint,object* phint)
   {

      if(lHint == 1984)
      {

         {

            synch_lock sl(m_pcallback == NULL ? NULL : m_pcallback->get_mutex());

            string strExp;

            _001GetText(strExp);


            parser parser(get_app());

            error e;

            e.m_iEnd = -1;
            e.m_iStart = -1;
            e.m_dwTime= ::get_tick_count();

            ::calculator::element * pelement = NULL;

            string strSource;

            if(str::ends_eat_ci(strExp,"FPS"))
            {
               strSource = "Hz";
            }
            else if(str::ends_eat_ci(strExp,"Frames Per Second"))
            {
               strSource = "Hz";
            }
            else if(str::ends_eat_ci(strExp,"SPF"))
            {
               strSource = "s";
            }
            else if(str::ends_eat_ci(strExp,"Seconds per frame"))
            {
               strSource = "s";
            }
            else if(str::ends_eat_ci(strExp,"Hz"))
            {
               strSource = "Hz";
            }
            else if(str::ends_eat_ci(strExp,"minute"))
            {
               strSource = "min";
            }
            else if(str::ends_eat_ci(strExp,"days"))
            {
               strSource = "day";
            }
            else if(str::ends_eat_ci(strExp,"minutes"))
            {
               strSource = "min";
            }
            else if(str::ends_eat_ci(strExp,"hours"))
            {
               strSource = "hour";
            }
            else if(str::ends_eat_ci(strExp,"hour"))
            {
               strSource = "hour";
            }
            else if(str::ends_eat_ci(strExp,"day"))
            {
               strSource = "day";
            }
            else if(str::ends_eat_ci(strExp,"ms"))
            {
               strSource = "ms";
            }
            else if(str::ends_eat_ci(strExp,"s"))
            {
               strSource = "s";
            }
            else
            {
               strSource = m_strFormat;
            }
            string strFormat(m_strFormat);

            if(str::ends_eat_ci(strFormat,"FPS"))
            {
               strFormat = "Hz";
            }
            else if(str::ends_eat_ci(strFormat,"Frames Per Second"))
            {
               strFormat = "Hz";
            }
            else if(str::ends_eat_ci(strFormat,"SPF"))
            {
               strFormat = "s";
            }
            else if(str::ends_eat_ci(strFormat,"Seconds per frame"))
            {
               strFormat = "s";
            }
            else if(str::ends_eat_ci(strFormat,"Hz"))
            {
               strFormat = "Hz";
            }
            else if(str::ends_eat_ci(strFormat,"s"))
            {
               strFormat = "s";
            }
            else
            {
               strFormat = m_strFormat;
            }
            strExp.trim();
            try
            {

               pelement = parser.parse(strExp);
               //throw simple_exception(::get_thread_app(), "now a simple exception here");

            }
            catch(const numeric_parser_exception & exp)
            {

               e.m_strMessage = exp.m_strMessage;
               e.m_iStart = 0;
               e.m_iEnd = strExp.length();

            }
            catch (const simple_exception & exp)
            {


            }

            string str;

            if(pelement != NULL)
            {

               m_val = pelement->get_value();

               str = strExp;

            }

            string strVal;
            bool bConv = true;

            if(e.m_iStart < 0)
            {

               if(strSource.has_char())
               {
                  if(strSource != strFormat)
                  {

                     if(strFormat == "s")
                     {
                        if(strSource == "Hz")
                        {
                           if(m_val.mod() == 0.0)
                           {
                              strVal = "(infinite)";
                           }
                           else
                           {
                              strVal = ::str::from(1.0 / m_val.mod());
                           }
                        }
                     }
                     else if(strFormat == "Hz")
                     {
                        if(m_val.mod() == 0.0)
                        {
                           strVal = "(infinite)";
                        }
                        else if(strSource == "ms")
                        {
                           m_val.m_dR = 1000.0 / m_val.m_dR;
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if(strSource == "s")
                        {
                           m_val.m_dR = 1.0 / m_val.m_dR;
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if(strSource == "min")
                        {
                           m_val.m_dR = 1.0 / (60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();

                        }
                        else if(strSource == "hour")
                        {
                           m_val.m_dR = 1.0 / (60.0 * 60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if(strSource == "day")
                        {
                           m_val.m_dR = 1.0 / (24.0 * 60.0 * 60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else
                        {
                           strVal = m_val.to_string();
                        }
                     }

                  }
               }
               else
               {
                  e.m_strMessage = "(unknown conversion)";
                  bConv = false;
                  strVal = m_val.to_string();
               }
            }
            else
            {
               strVal = m_val.to_string();
            }

            if(!bConv)
            {
               e.m_iStart = (strExp + string(" ")).length();
               e.m_iEnd = e.m_iStart + strSource.length();

            }
            str = strExp + string(" ") + strSource + string(" = ") + strVal;

            if(m_pcallback != NULL)
            {

               if(m_strFormat.has_char())
               {

                  m_pcallback->set_expression(str + " " + m_strFormat);

               }
               else
               {

                  m_pcallback->set_expression(str);

               }

            }

            if(e.m_iStart >= 0)
            {
               m_errora.add(e);
            }
            else
            {
               m_errora.remove_all();
            }


         }

/*         if(m_ptopview != NULL)
         {

            m_ptopview->m_pview->post_message(WM_USER + 1984 + 77 + 2);

         }*/

      }

   }


   void plain_edit_view::_001OnAfterChangeText(::action::context actioncontext)
   {

      if(actioncontext.is_user_source())
      {


         //      if(m_ptopview == NULL || m_ptopview->m_pview == NULL)
           //       return;

         on_update(NULL,1984,NULL);

      }

      plain_edit::_001OnAfterChangeText(actioncontext);
   }


   bool plain_edit_view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }


   int64_t plain_edit_view::add_ref()
   {
      return ::object::add_ref();
   }
   int64_t plain_edit_view::dec_ref()
   {
      return ::object::dec_ref();
   }


   var plain_edit_view::get_ex_value()
   {

      var v;

      v["real"] = m_val.m_dR;
      v["imaginary"] = m_val.m_dI;
      v["text"] = ::user::plain_edit::get_ex_value();

      return v;

   }



} // namespace calculator




