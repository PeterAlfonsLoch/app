#include "StdAfx.h"
#include "syllomatter_document.h"



syllomatter_document::syllomatter_document(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   ::html_document(papp),
   form_document(papp)
{
}

BOOL syllomatter_document::on_new_document()
{
   if (!document::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);

   string str;
   str = "<syllomatter>\n";
   str += "<head>\n";
   str += "</head>\n";
   str += "<body>\n";
   // tag fixer tabjs!!
   str += "<span>Curitiba, 10 de abril de 2008</span>\n";
   str += "<h1>Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!</h1>";
   str += "<h2>Assinado Camilo Sasuke Tsumanuma.</h2>\n";
   str += "<span>htmlapp dedicado ao Carlos Gustavo Cecyn Lundgren!!</span>";
   str += "<br />";
   str += "<span>Você conhece o ca2?</span>";
   str += "<br />";
   str += "<span>Se positivo, entre com seu nome abaixo e clique em enviar!</span>";
   str += "<br />";
   str += "<input type=\"text\" />";
   str += "<input type=\"text\" />";
   str += "</body>\n";
   str += "</syllomatter>\n";
   return TRUE;
}

syllomatter_document::~syllomatter_document()
{
}


 // BEGIN_MESSAGE_MAP(syllomatter_document, document)
   //{{AFX_MSG_MAP(syllomatter_document)
      // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// syllomatter_document diagnostics

#ifdef _DEBUG
void syllomatter_document::assert_valid() const
{
   document::assert_valid();
}

void syllomatter_document::dump(dump_context & dumpcontext) const
{
   document::dump(dumpcontext);
}
#endif //_DEBUG

void syllomatter_document::data_on_after_change(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

bool syllomatter_document::on_open_document(var varFile)
{
   return form_document::on_open_document(varFile);
}

bool syllomatter_document::open_commit_message()
{
   string strTime;
   strTime = System.file().time_square();
   string strContents;
   string strMessages;
   gen::property_set headers;
   gen::property_set post;
   gen::property_set set;
   Application.http().get("https://fontopus.com/ca2api/i2com/commit_message", 
      strMessages, 
      post, headers,  set,
      NULL, &ApplicationUser);
   xml::node node(get_app());
   node.load(strMessages);
   strContents = "<html><head></head><body style=\"background-color:#FFFFFF;\">";
   for(int i = 0; i < node.get_children_count(); i++)
   {
      
      xml::node * lpnode = node.child_at(i);
      string strId;
      strId.Format("messagetext_%s", lpnode->attr("id").get_string());
      strContents += "<span id=\"" + strId +"\">";
      strContents += System.url().url_decode(lpnode->attr("value")).Left(255);
      TRACE(strContents);
      strContents += "</span>";
      strContents += "<br />";
      strId.Format("message_%s", lpnode->attr("id").get_string());
      strContents += "<input type=\"button\" id=\"" +strId + "\" value=\"Select\" />";
      strContents += "<br />";
      strContents += "<br />";
      TRACE(strContents);
   }
   strContents += "<br />";
   strContents += "</body>";
   strContents += "</html>";
   TRACE(strContents);
   Application.file().put_contents(strTime, strContents);
   return open_document(strTime);
}

