#include "framework.h" // from "aura/net/net_sockets.h"
#include "aura/net/net_sockets.h"


namespace http
{


   response::response(::aura::application * papp, const string & version) :
   ::object(papp),
   transaction(papp),
   m_memfileBody(papp ),
   m_ostream(&m_memfileBody)
   {

      UNREFERENCED_PARAMETER(version);

   }


   response::response(const response& src) :
   ::object(((response &)src).get_app()),
   transaction(src)
   , m_memfileBody(((response &)src).get_app() ),
   m_ostream(&m_memfileBody)
   {

      m_memfileBody = src.m_memfileBody;

   }


   response::~response()
   {

   }


   // --------------------------------------------------------------------------------------
   response& response::operator=(const response& src)
   {
      m_memfileBody        = src.m_memfileBody;

      transaction::operator=(src);

      return *this;
   }

   // --------------------------------------------------------------------------------------
   /*void response::SetFile( const string & path )
   {
      m_file = smart_pointer<IFile>(new File);
      m_file -> fopen( path, "rb" );
   }*/

   // --------------------------------------------------------------------------------------
   void response::clear()
   {
      transaction::clear();
      file().set_length(0);
   //   m_file = smart_pointer<IFile>(new MemFile);
   }

} // namespace http 


