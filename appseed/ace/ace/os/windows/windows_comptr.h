#pragma once


namespace windows
{


   class CLASS_DECL_ACE comptr_base
   {
   public:


      IUnknown * m_p;


      comptr_base()
      {

         m_p = NULL;

      }


      ~comptr_base()
      {

         Release();

      }


      ULONG Release()
      {

         ULONG ul = 0;

         try
         {

            if (m_p != NULL)
            {

               ul = m_p->Release();

            }

         }
         catch (...)
         {


         }

         m_p = NULL;


         return ul;

      }


      bool is_null()
      {

         return m_p == NULL;

      }


      bool is_set()
      {

         return !is_null();

      }

   };


   template < class TYPE >
   class comptr:
      public comptr_base
   {
   public:


      comptr()
      {

      }


      HRESULT CoCreateInstance(REFCLSID rclsid,LPUNKNOWN pUnkOuter = NULL,DWORD dwClsContext = CLSCTX_ALL)
      {

         return ::CoCreateInstance(rclsid,pUnkOuter,dwClsContext,__uuidof(TYPE),(void **)&m_p);

      }

      template < class IFACE >
      HRESULT As(comptr < IFACE > & iface)
      {

         return m_p->QueryInterface< IFACE >(&iface);

      }


      TYPE * operator ->()
      {
         
         return (TYPE *)m_p;

      }


      TYPE * detach()
      {
      
         TYPE * p = operator ->();
         
         m_p = NULL;
         
         return p;

      }


      TYPE ** operator & ()
      {

         Release();

         return &(TYPE * &)m_p;

      }


      operator TYPE * ()
      {

         return (TYPE *)m_p;

      }


   };


} // namespace windows





