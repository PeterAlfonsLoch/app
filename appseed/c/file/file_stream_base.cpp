#include "framework.h"


namespace file
{

   
   stream_base::stream_base()
   {
      
      m_iostate = goodbit;

   }

   stream_base::~stream_base()
   {
   }


   string stream_base::GetFilePath() const
   {

      return m_spbuffer->GetFilePath();

   }


} // namespace file





