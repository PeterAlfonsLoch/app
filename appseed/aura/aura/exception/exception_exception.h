#pragma once


namespace exception
{


   class CLASS_DECL_AURA exception :
      virtual public ::object
   {
   public:


      bool        m_bHandled;
      bool        m_bContinue;
      string      m_strMessage;


      exception();
      virtual ~exception();
      virtual void Delete();


      virtual const char * what () const throw ();


   };


   void CLASS_DECL_AURA rethrow(exception * pe);


   class CLASS_DECL_AURA result:
      virtual public exception,
      virtual public spa(exception)
   {
   public:


      result() {}
      result(e_context_switcher_no_exception) {}
      result(e_context_switcher_failed)
      {
         add(canew(exception()));
      }
      result(std::initializer_list < exception * > list);
      ~result() { release(); }


      operator bool() { return get_count() <= 0; }

   };



   class CLASS_DECL_AURA result_sp:
      virtual public sp(result)
   {
   public:


      result_sp() {}
      result_sp(e_context_switcher_no_exception) {}
      result_sp(e_context_switcher_failed efailed)
      {
         m_p = canew(result(efailed));
         if(m_p != NULL)
         {
            m_p->add_ref();
         }
      }
      result_sp(exception * pexception)
      {
         m_p = canew(result({pexception}));
         if(m_p != NULL)
         {
            m_p->add_ref();
         }
      }
      ~result_sp() { release(); }


      operator bool() const { return is_null(); }


   };


} // namespace exception




typedef ::exception::result_sp cres;
