#pragma once

namespace ihtml
{
   class document;
   class document_container;
   class signal : public gen::signal_object
   {
   public:
      signal(gen::signal * psignal);
      document_container * m_pdoccontainer;
      gen::signal_object * m_psignal;
   };

} // namespace ihtml