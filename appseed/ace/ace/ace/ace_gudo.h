#pragma once


namespace ace
{

   template < class AXIS >
   class gudo:
      virtual public AXIS,
      virtual public object
   {
   public:


      string         m_strKey;
      bool           m_bAutoGudoSet;


      gudo(sp(ace::application) papp,const string & strKey,bool bInitialGudoGet = true);
      virtual ~gudo();

      virtual void gudo_get();
      virtual void gudo_set();

   };

   template < class AXIS >
   gudo < AXIS > ::gudo(sp(ace::application) papp,const string & strKey,bool bInitialGudoGet):
      object(papp)
   {

      m_strKey = strKey;

      m_bAutoGudoSet = true;

      if(bInitialGudoGet)
      {

         gudo_get();

      }

   }

   template < class AXIS >
   gudo < AXIS > ::~gudo()
   {

      if(m_bAutoGudoSet)
      {

         gudo_set();

      }

   }


} // namespace ace