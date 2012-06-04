#pragma once




namespace numeric_info
{


   template < typename T >
   inline T get_maximum_value()
   {
      throw not_implemented_exception();
   }

   template < typename T >
   inline T get_minimum_value()
   {
      throw not_implemented_exception();
   }
   template < typename T >
   inline T get_null_value()
   {
      return 0;
   }
   template < typename T >
   inline T get_unitary_value()
   {
      return 1;
   }

   template < typename T >
   inline T get_allset_value()
   {
      T t;
      memset(&t, 0xff, sizeof(T));
      return t;
   }

   template <>
   inline int get_maximum_value < int > ()
   {
      return (int) 0x7fffffff;
   }
   template <>
   inline int get_minimum_value < int > ()
   {
      return (int) 0x80000000;
   }
   template <>
   inline int get_null_value < int > ()
   {
      return 0;
   }
   template <>
   inline int get_unitary_value < int >()
   {
      return 1;
   }

   template <>
   inline float get_maximum_value < float >()
   {
      return 3.4e38f;
   }
   template <>
   inline float get_minimum_value < float >()
   {
      return -3.4e38f;
   }
   template <>
   inline float get_null_value < float >()
   {
      return 0.0f;
   }
   template <>
   inline float get_unitary_value < float >()
   {
      return 1.0f;
   }

   template <>
   inline double get_maximum_value < double >()
   {
      return 1.7e308;
   }
   template <>
   inline double get_minimum_value < double >()
   {
      return -1.7e308;
   }
   template <>
   inline double get_null_value < double >()
   {
      return 0.0;
   }
   template <>
   inline double get_unitary_value < double >()
   {
      return 1.0;
   }

   template <>
   inline BYTE get_maximum_value < BYTE > ()
   {
      return (BYTE) 255;
   }
   template <>
   inline BYTE get_minimum_value < BYTE > ()
   {
      return (BYTE) 0;
   }
   template <>
   inline BYTE get_null_value < BYTE > ()
   {
      return 0;
   }
   template <>
   inline BYTE get_unitary_value < BYTE >()
   {
      return 1;
   }

   template <>
   inline WORD get_maximum_value < WORD > ()
   {
      return static_cast < WORD > (0xffff);
   }
   template <>
   inline WORD get_minimum_value < WORD > ()
   {
      return (WORD) 0;
   }
   template <>
   inline WORD get_null_value < WORD > ()
   {
      return 0;
   }
   template <>
   inline WORD get_unitary_value < WORD >()
   {
      return 1;
   }

   #ifdef WINDOWS

   template <>
   inline DWORD get_maximum_value < DWORD > ()
   {
      return static_cast < DWORD > (0xffffffff);
   }
   template <>
   inline DWORD get_minimum_value < DWORD > ()
   {
      return (DWORD) 0;
   }
   template <>
   inline DWORD get_null_value < DWORD > ()
   {
      return 0;
   }
   template <>
   inline DWORD get_unitary_value < DWORD >()
   {
      return 1;
   }

   #endif

   template <>
   inline UINT get_maximum_value < UINT > ()
   {
      return static_cast < UINT > (0xffffffff);
   }




   template <>
   inline uint64_t get_maximum_value < uint64_t > ()
   {
      return static_cast < uint64_t > (0xffffffffffffffff);
   }
   template <>
   inline uint64_t get_allset_value < uint64_t > ()
   {
      return static_cast < uint64_t > (0xffffffffffffffff);
   }
   template <>
   inline uint64_t get_minimum_value < uint64_t > ()
   {
      return static_cast < uint64_t > (0);
   }
   template <>
   inline uint64_t get_unitary_value < uint64_t >()
   {
      return 1;
   }




   template <>
   inline int64_t get_maximum_value < int64_t > ()
   {
      return static_cast < int64_t > (0x7fffffffffffffff);
   }
   template <>
   inline UINT get_minimum_value < UINT > ()
   {
      return (UINT) 0;
   }
   template <>
   inline int64_t get_minimum_value < int64_t > ()
   {
      return static_cast < int64_t > (0x8000000000000000);
   }
   template <>
   inline UINT get_null_value < UINT > ()
   {
      return 0;
   }
   template <>
   inline UINT get_unitary_value < UINT >()
   {
      return 1;
   }


   template < typename T > class offset { public: typedef T TYPE; };

   template < > class CLASS_DECL_ca offset < unsigned char > { public: typedef char TYPE; };
   template < > class CLASS_DECL_ca offset < unsigned short > { public: typedef short TYPE; };
   template < > class CLASS_DECL_ca offset < unsigned int > { public: typedef int TYPE; };
   template < > class CLASS_DECL_ca offset < unsigned long > { public: typedef long TYPE; };
#if defined(WINDOWS)
   template < > class CLASS_DECL_ca offset < uint64_t > { public: typedef int64_t TYPE; };
#endif

} // numeric_info
