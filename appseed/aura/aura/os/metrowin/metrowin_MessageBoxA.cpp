#include "framework.h"

#undef new

using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

public ref class message_box_a sealed
{
public:

   MessageDialog^ msg;

   message_box_a();

   void do_modal(String ^ text, String ^ caption, unsigned int uiFlags);
   void on_command(Windows::UI::Popups::IUICommand^ command);

   void create_a_button(String ^ id,String ^ text);
};

message_box_a::message_box_a()
{
 
}

void message_box_a::create_a_button(String ^ id,String ^ text)
{
   msg->Commands->Append(ref new UICommand(text,ref new UICommandInvokedHandler(this,&message_box_a::on_command),id);
}

void message_box_a::do_modal(String ^ text,String ^ caption,unsigned int uiFlags)
{

   MessageDialog^ msg = ref new MessageDialog(text, caption);

   switch(uiType)
   {
   case MB_OKCANCEL:
      create_a_button("ok","OK");
      create_a_button("cancel","Cancel");
      break;
   case MB_ABORTRETRYIGNORE:
      create_a_button("abort","Abort");
      create_a_button("retry","Retry");
      create_a_button("ignore","Ignore");
      break;
   case MB_YESNOCANCEL:
      create_a_button("yes","Yes");
      create_a_button("no","No");
      create_a_button("cancel","Cancel");
      break;
   case MB_YESNO:
      create_a_button("yes","Yes");
      create_a_button("no","No");
      break;
   case MB_RETRYCANCEL:
      create_a_button("retry","Retry");
      create_a_button("cancel","Cancel");
      break;
   case MB_CANCELTRYCONTINUE:
      create_a_button("cancel","Cancel");
      create_a_button("try","Try");
      create_a_button("continue","Continue");
      break;
   default:
      create_a_button("ok","OK");
      break;
   }


   // Set the command that will be invoked by default 
   msg->DefaultCommandIndex = 0;

   // Set the command to be invoked when escape is pressed 
   msg->CancelCommandIndex = 1;

   // Show the message dialog 
   msg->ShowAsync();
}

/// <summary> 
/// Callback function for the invocation of the dialog commands. 
/// </summary> 
/// <param name="command">The command that was invoked.</param> 
void CancelCommand::CommandInvokedHandler(Windows::UI::Popups::IUICommand^ command)
{

   if(stricmp_dup(pszId,"ok") == 0)
   {

      m_iResult = IDOK;

      EndModalLoop(IDOK);

      return true;

   }
   else if(stricmp_dup(pszId,"yes") == 0)
   {

      m_iResult = IDYES;

      EndModalLoop(IDOK);

      return true;

   }
   else if(stricmp_dup(pszId,"no") == 0)
   {

      m_iResult = IDNO;

      EndModalLoop(IDOK);

      return true;

   }
   else if(stricmp_dup(pszId,"cancel") == 0)
   {

      m_iResult = IDCANCEL;

      EndModalLoop(IDOK);

      return true;

   }
   else if(stricmp_dup(pszId,"abort") == 0)
   {

      m_iResult = IDABORT;

      EndModalLoop(IDOK);

      return true;

   }
   else if(stricmp_dup(pszId,"retry") == 0)
   {

      m_iResult = IDRETRY;

      EndModalLoop(IDOK);

      return true;

   }
   else if(stricmp_dup(pszId,"ignore") == 0)
   {

      m_iResult = IDIGNORE;

      EndModalLoop(IDOK);

      return true;

   }
   else if(stricmp_dup(pszId,"try") == 0)
   {

      m_iResult = IDTRYAGAIN;

      EndModalLoop(IDOK);

      return true;

   }
   else if(stricmp_dup(pszId,"continue") == 0)
   {

      m_iResult = IDCONTINUE;

      EndModalLoop(IDOK);

      return true;

   }


   return false;

   // Display message 
   rootPage->NotifyUser("The '" + command->Label + "' command has been selected.",NotifyType::StatusMessage);
}





::rect rectDesktop;

stringa stra;

stra.add("\r");

stra.add("\n");

stra.add("\r\n");

m_stra.add_smallest_tokens(m_strMessage,stra);

Session.get_main_monitor(rectDesktop);

SetWindowText(m_strTitle);

rect rectFontopus;

int stdw = 800;

int stdh = 184 + 23 + 184;

int w = stdw;

int h = stdh;

if(w > rectDesktop.width())
{

   w = rectDesktop.width();

}

if(h > rectDesktop.height())
{

   h = rectDesktop.height();

}

rectFontopus.left = rectDesktop.left + (width(rectDesktop) - w) / 2;

rectFontopus.top = rectDesktop.top + (height(rectDesktop) - h) / 3;

rectFontopus.right = rectFontopus.left + w;

rectFontopus.bottom = rectFontopus.top + h;

if(!create_window_ex(0,NULL,NULL,0,rectFontopus,NULL,"fontopus"))
throw simple_exception(get_app(),"not excepted! Failing Message box!!");

uint32_t uiType = m_uiFlags & MB_TYPEMASK;


SetWindowPos(ZORDER_TOP,rectFontopus,SWP_SHOWWINDOW);

layout();

SetForegroundWindow();

BringWindowToTop();

BringToTop(SW_NORMAL);

RunModalLoop();

return m_iResult;

   }


   void message_box::_001OnDraw(::draw2d::graphics * pdc)
   {

      rect rectClient;

      GetClientRect(rectClient);

      pdc->FillSolidRect(rectClient,ARGB(255,0xcc,0xcc,0xc5));

      sp(::draw2d::font) font(allocer());

      font->create_point_font("Arial",12);

      pdc->selectFont(font);

      ::draw2d::text_metric tm;

      pdc->get_text_metrics(&tm);

      int iHeight = tm.tmHeight;

      int y = 10;

      for(int i = 0; i < m_stra.get_size(); i++)
      {

         pdc->TextOut(10,y,m_stra[i]);

         y+= iHeight;

      }


   }


   void message_box::layout()
   {

      rect rectClient;

      GetClientRect(rectClient);

      // DESKTOP sizing
      int cx = (84 + 77) * 2 / 3;
      int cy = 49 / 2;
      int margin = 10;
      int x = rectClient.left + margin;
      int y = rectClient.bottom - cy - margin;


      for(index i = 0; i < m_tapaA.get_count(); i++)
      {

         sp(tap) ptap = m_tapaA(i);

         ptap->SetWindowPos(ZORDER_TOP,x,y,cx,cy,SWP_SHOWWINDOW);

         x += cx + margin;

      }

      x = rectClient.right - margin - cx;

      for(index i = m_tapaB.get_upper_bound(); i >= 0; i--)
      {

         sp(tap) ptap = m_tapaB(i);

         ptap->SetWindowPos(ZORDER_TOP,x,y,cx,cy,SWP_SHOWWINDOW);

         x -= cx + margin;

      }


   }


   bool message_box::on_action(const char * pszId)
   {


   }


   void message_box::pre_translate_message(signal_details * pobj)
   {

      simple_ui::interaction::pre_translate_message(pobj);

   }


} // namespace simple_ui




int32_t MessageBoxA(oswindow interaction_impl,const char * lpText,const char * lpCaption,uint32_t uiFlags)
{

   UNREFERENCED_PARAMETER(interaction_impl);

   message_box_a ^ a = ref new message_box_a();

   return a->do_modal(string(lpText),string(lpCaption),uiFlags);


}






