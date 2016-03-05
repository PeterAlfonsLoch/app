#include "basecore.h"

#include <gtk/gtk.h>

#include <libappindicator-0.1/libappindicator/app-indicator.h>

#include <malloc.h>

#include <time.h>

#include <new>

struct indicator;

GtkWidget * idle_basecore_app_indicator_init(indicator * pind, i_close_quit * pi);

void * basecore_app_indicator_init(indicator * pind, struct i_close_quit * pi);

static void ___close(void * data)
{

   ::i_close_quit * pi = (::i_close_quit *) data;

   pi->__close();

}


static void ___quit(void * data)
{

   ::i_close_quit * pi = (::i_close_quit *) data;

   pi->__quit();

}
extern "C"
{

static void __close(GtkAction * action, gpointer data)
{

   ___close(data);

}


static void __quit(GtkAction * action, gpointer data)
{

   ___quit(data);

}


static gboolean f1(void * data);

} // extern "C"





static GtkActionEntry entries[] =
{

   { "Close" , "application-close" , "_Close" , "<control>C" , "Close the application", G_CALLBACK (__close) },
   { "Quit"  , "application-exit"  , "_Quit"  , "<control>Q" , "Exit the application", G_CALLBACK (__quit) },

};


static guint n_entries = G_N_ELEMENTS (entries);


static const gchar *ui_info =
   "<ui>"
  "  <popup name='IndicatorPopup'>"
  "    <menuitem action='Close' />"
  "    <menuitem action='Quit' />"
  "  </popup>"
  "</ui>";





void basecore_init()
{

   gtk_init_check(0, 0);

   gtk_main();

}



struct basecore_data
{
public:

   const char *         m_pszId;
   const char *         m_pszIcon;
   const char *         m_pszFolder;
   AppIndicator *       m_pindicator;
   i_close_quit *       m_piclosequit;
   indicator *          m_pind;
   bool                 m_bReady;
   bool                 m_bLoop;
   bool                 m_bTerm;
   int                  m_iTry;
   void *               m_pvoidRet;
   GtkWidget *          m_pmenu;
   int                  m_iOpen;
   bool                 m_bQuitGtk;


   basecore_data();
   ~basecore_data()
   {

   }
   virtual void post();
   virtual void * process();
   virtual void * wait();
   gboolean run();

   GtkMenuItem * get_menu_item_close();

};

basecore_data::basecore_data()
{
   m_pszId = NULL;
   m_pszIcon = NULL;
   m_pindicator = NULL;
   m_pind = NULL;
   m_piclosequit = NULL;
   m_bReady = false;
   m_iTry = 0;
   m_pvoidRet = NULL;
   m_pmenu = NULL;
   m_bLoop = false;
   m_bTerm = true;
   m_iOpen = -1;
   m_bQuitGtk = false;
}

struct indicator_new : public basecore_data
{
   indicator_new(const char * pszId, const char *pszIcon, const char * pszFolder)
   {
      m_pszId     = pszId;
      m_pszIcon   = pszIcon;
      m_pszFolder = pszFolder;
   }

};

struct indicator : public basecore_data
{

   indicator(AppIndicator * pindicator)
   {

      m_pind            = this;
      m_pindicator = pindicator;

   }

   void init(i_close_quit * piclosequit, GtkWidget * pmenu)
   {

      m_piclosequit = piclosequit;
      m_pmenu = pmenu;
      m_bLoop = true;
      m_bTerm = false;

   }

};

struct indicator_init : public basecore_data
{
   indicator_init(indicator * pind, i_close_quit * piclosequit)
   {
      m_pind         = pind;
      m_pindicator   = pind->m_pindicator;
      m_piclosequit  = piclosequit;
   }

};



struct indicator_term : public basecore_data
{
   indicator_term(indicator * pind)
   {
      m_pind = pind;
      m_pindicator   = pind->m_pindicator;
   }

};

void basecore_data::post()
{
   g_idle_add(f1,(basecore_data*)this);
}

void * basecore_data::process()
{

   post();

   return wait();
}

void * basecore_data::wait()
{
   timespec req;
   req.tv_sec=0;
   req.tv_nsec = 284*1000*1000;
   timespec rem;
   while(m_iTry < 100 && !m_bReady)
   {
      nanosleep(&req, &rem);
      m_iTry++;
   }
   void * pRet = m_pvoidRet;
   delete this;
   return pRet;
}


gboolean f1(gpointer p)
{

   basecore_data * data = (basecore_data *) p;

   return data->run();

}


void * basecore_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, i_close_quit * pi)
{

   indicator_new * data = new indicator_new(pszId, pszIcon, pszFolder);

   indicator * pind = (indicator *) data->process();

   if(pind == NULL)
   {

      return NULL;

   }

   if(!basecore_app_indicator_init(pind,pi))
   {

      basecore_app_indicator_term(pind);

      return NULL;

   }

   return pind;

}



void * basecore_app_indicator_init(indicator * pind, i_close_quit * pi)
{

   indicator_init * data = new indicator_init(pind, pi);

   return data->process();

}


void basecore_app_indicator_term(void * pvoidInd)
{

   indicator * pind = (indicator *) pvoidInd;

   indicator_term * data = new indicator_term(pind);

   data->process();

   pind->wait();

}


GtkWidget * idle_basecore_app_indicator_init(indicator * pind, i_close_quit * pi)
{

   AppIndicator * m_pappindicator = (AppIndicator *) pind->m_pindicator;

   GError *error = NULL;

   GtkActionGroup * action_group = gtk_action_group_new ("AppActions");

   if(action_group == NULL)
   {

      return NULL;

   }

   gtk_action_group_add_actions (action_group, entries, n_entries, pi);

   GtkUIManager * uim = gtk_ui_manager_new ();

   if(uim == NULL)
   {

      return NULL;

   }

   gtk_ui_manager_insert_action_group (uim, action_group, 0);

   if (!gtk_ui_manager_add_ui_from_string (uim, ui_info, -1, &error))
   {

      g_message ("Failed to build menus: %s\n", error->message);

      g_error_free (error);

      error = NULL;

      return NULL;

   }

   GtkWidget *  indicator_menu = gtk_ui_manager_get_widget (uim, "/ui/IndicatorPopup");

   app_indicator_set_menu(m_pappindicator, GTK_MENU (indicator_menu));

   app_indicator_set_status(m_pappindicator, APP_INDICATOR_STATUS_ACTIVE);

   return indicator_menu;

}


void basecore_term()
{

   basecore_data * data = new basecore_data();

   data->m_bQuitGtk = true;

   data->process();

}


GtkMenuItem * basecore_data::get_menu_item_close()
{

   GtkMenuItem * pmenuitemClose = NULL;

   GList * l = gtk_container_get_children(GTK_CONTAINER(m_pmenu));

   GtkWidget * pwidget = (GtkWidget *)l->data;

   g_list_free1(l);

   pmenuitemClose = GTK_MENU_ITEM(pwidget);

   return pmenuitemClose;

}

gboolean basecore_data::run()
{

   if(m_pszId != NULL && m_pszIcon != NULL)
   {

      AppIndicator * pindicator = app_indicator_new_with_path(m_pszId, m_pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, m_pszFolder);

      if(pindicator == NULL)
      {

         m_pvoidRet = NULL;

      }
      else
      {

         ::indicator * pind = new indicator(pindicator);

         m_pvoidRet = pind;

      }



   }
   else if(m_pind != NULL)
   {

      if(m_piclosequit != NULL)
      {

         if(m_pmenu)
         {


            if(m_piclosequit->__close_is_closed())
            {

               if(m_iOpen != 0)
               {

                  gtk_menu_item_set_label(get_menu_item_close(), "Open");

                  m_iOpen = 0;

               }

            }
            else
            {

               if(m_iOpen != 1)
               {

                  gtk_menu_item_set_label(get_menu_item_close(), "Close");

                  m_iOpen = 1;

               }

            }

            if(m_bTerm)
            {

               m_bLoop = false;

            }

         }
         else
         {

            GtkWidget * pmenu = idle_basecore_app_indicator_init(m_pind, m_piclosequit);

            m_pind->init(m_piclosequit, pmenu);

            m_pind->post();

            m_pvoidRet = m_pind;

         }

      }
      else
      {

         app_indicator_set_status(m_pindicator, APP_INDICATOR_STATUS_PASSIVE);

         m_pind->m_bTerm = true;

      }
   }
   else if(m_bQuitGtk)
   {

      gtk_main_quit();

   }

   if(!m_bLoop)
   {

      m_bReady = true;

   }

   return m_bLoop;

}
