#pragma once

namespace html
{

   class CLASS_DECL_ca file :
      virtual public ::radix::object
   {
   public:

      string                     m_strOptions;
      string                     m_strStyle;
      ::user::str_context *      m_puistrcontext;

      file();

      virtual ::user::str_context *  str_context();

      virtual void print(const char * lpcsz);
      virtual void printf(const char * lpcsz, ...);
      virtual void printstr(const char * lpcsz, ...);


      virtual void dprint(const char * lpcsz);

   };

} // namespace ca4