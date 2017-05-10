#pragma once


namespace windows
{


   template < typename TYPE >
   class comptr
   {
   public:

      TYPE * m_p;

      comptr()
      {
         m_p = NULL;

      }

      comptr(const comptr & ptr)
      {
         if (ptr.m_p != NULL)
         {
            ptr.m_p->AddRef();
         }
         m_p = ptr.m_p;

      }

      comptr(TYPE * p)
      {
         if (p != NULL)
         {
            p->AddRef();
         }
         m_p = p;
      }






         ~comptr()
         {

            Release();

         }

      HRESULT CoCreateInstance(REFCLSID rclsid,LPUNKNOWN pUnkOuter = NULL,DWORD dwClsContext = CLSCTX_ALL)
      {

         Release();

         return ::CoCreateInstance(rclsid,pUnkOuter,dwClsContext,__uuidof(TYPE),(void **)&m_p);

      }

      template < class IFACE >
      HRESULT As(comptr < IFACE > & iface)
      {

         if (m_p == NULL)
         {

            return E_FAIL;

         }

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

      operator void ** ()
      {

         Release();

         return (void **) &(TYPE * &)m_p;

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

      comptr & operator = (TYPE * p)
      {

         if (m_p != p)
         {

            if (p != NULL)
            {

               p->AddRef();


            }

            if (m_p != NULL)
            {

               m_p->Release();

            }

            m_p = p;

         }

         return *this;

      }


      comptr & operator = (const comptr & ptr)
      {

         if (&ptr != this)
         {

            if (ptr.m_p != NULL)
            {

               ptr.m_p->AddRef();


            }

            if (m_p != NULL)
            {

               m_p->Release();

            }

            m_p = ptr.m_p;

         }

         return *this;

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


} // namespace windows





