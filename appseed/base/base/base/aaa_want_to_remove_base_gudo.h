#pragma once


namespace base
{

   template < class BASE >
   class gudo:
      virtual public BASE,
      virtual public object
   {
   public:


      string         m_strKey;
      bool           m_bAutoGudoSet;


      gudo(sp(axis::application) papp,const string & strKey,bool bInitialGudoGet = true);
      virtual ~gudo();

      virtual void gudo_get();
      virtual void gudo_set();

   };

   template < class BASE >
   gudo < BASE > ::gudo(sp(axis::application) papp,const string & strKey,bool bInitialGudoGet):
      element(papp)
   {

      m_strKey = strKey;

      m_bAutoGudoSet = true;

      if(bInitialGudoGet)
      {

         gudo_get();

      }

   }

   template < class BASE >
   gudo < BASE > ::~gudo()
   {

      if(m_bAutoGudoSet)
      {

         gudo_set();

      }

   }


} // namespace base