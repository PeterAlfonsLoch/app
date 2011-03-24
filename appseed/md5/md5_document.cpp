#include "StdAfx.h"

namespace md5
{

   document::document(::ca::application * papp) :
      ca(papp),
      m_thread(papp)
   {
   }

   BOOL document::on_new_document()
   {
	   if (!::userbase::document::on_new_document())
		   return FALSE;

      stringa wstra;
      data_get("SongDirectorySet", 0, wstra);



      update_all_views(NULL, 0);

      string str;
      str = "<md5>\n";
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
      str += "</body>\n";
      str += "</md5>\n";

	   return TRUE;
   }

   document::~document()
   {
   }


   //BEGIN_MESSAGE_MAP(document, ::userbase::document)
	   //{{AFX_MSG_MAP(document)
		   // NOTE - the ClassWizard will add and remove mapping macros here.
	   //}}AFX_MSG_MAP
   //END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // document diagnostics

   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context& dc) const
   {
	   ::userbase::document::dump(dc);
   }
   #endif //_DEBUG


   void document::data_on_after_change(gen::signal_object * pobj)
   {
   }

   bool document::on_open_document(var lpszPathName)
   {
      m_strCheckMd5 = Application.file().as_string(lpszPathName);

      m_thread.m_strFile = lpszPathName;

      gen::str::ends_eat_ci(m_thread.m_strFile, ".md5");

      if(!Application.file().exists(m_thread.m_strFile))
         return FALSE;

      m_thread.Begin();

      return TRUE;
   }


   document::thread::thread(::ca::application * papp) :
      ca(papp),
      radix::thread(papp),
      simple_thread(papp)
   {
      m_dProgress = 0.0;
      m_bReady = false;
   }

   int document::thread::run()
   {
      ex1::filesp spfile(get_app());

      if(!spfile->open(m_strFile, ::ex1::file::type_binary | ::ex1::file::mode_read))
         return 0;
      __int64 iLength = spfile->get_length();
      int iBufSize = 1024 * 256;
      unsigned char * buf = new unsigned char[iBufSize];
      MD5_CTX ctx;
      MD5_Init(&ctx);
      int iRead;
      __int64 iReadTotal = 0;
      spfile->seek_to_begin();
      while((iRead = spfile->read(buf, iBufSize)) > 0)
      {
         MD5_Update(&ctx, buf, iRead);
         iReadTotal += iRead;
         m_dProgress = (double) iReadTotal / (double) iLength;
      }
      MD5_Final(buf,&ctx);
      string str;
      string strFormat;
      for(int i = 0; i < 16; i++)
      {
         strFormat.Format("%02x", buf[i]);
         str += strFormat;
      }
      delete [] buf;
      m_strMd5 = str;
      m_bReady = true;
      m_dProgress = 1.0;
      return 0;
   }

} // namespace md5