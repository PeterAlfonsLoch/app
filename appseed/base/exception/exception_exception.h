#pragma once


namespace exception
{


   class CLASS_DECL_c exception :
      virtual public object
   {
   public:


      string m_strMessage;


      virtual ~exception();
      virtual void Delete();


      virtual const char * what () const throw ();


   };


   void CLASS_DECL_c rethrow(exception * pe);


} // namespace exception


