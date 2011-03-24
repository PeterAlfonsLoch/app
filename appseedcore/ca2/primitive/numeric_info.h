#pragma once

namespace numeric_info
{
   template < class T >
   inline T get_maximum_value()
   {
      throw not_implemented_exception();
   }
   template < class T >
   inline T get_minimum_value()
   {
      throw not_implemented_exception();
   }
   template < class T >
   inline T get_null_value()
   {
      return 0;
   }
   template < class T >
   inline T get_unitary_value()
   {
      return 1;
   }

#if core_level_1

   template <int>
   inline int get_maximum_value < int > ()
   {
      return (int) 0x7fffffff;
   }
   template <int>
   inline int get_minimum_value < int > ()
   {
      return (int) 0x80000000;
   }
   template <int>
   inline int get_null_value < int > ()
   {
      return 0;
   }
   template <int>
   inline int get_unitary_value < int >()
   {
      return 1;
   }

   template <float>
   inline float get_maximum_value < float >()
   {
      return 3.4e38f;
   }
   template <float>
   inline float get_minimum_value < float >()
   {
      return -3.4e38f;
   }
   template <float>
   inline float get_null_value < float >()
   {
      return 0.0f;
   }
   template <float>
   inline float get_unitary_value < float >()
   {
      return 1.0f;
   }

   template <double>
   inline double get_maximum_value < double >()
   {
      return 1.7e308;
   }
   template <double>
   inline double get_minimum_value < double >()
   {
      return -1.7e308;
   }
   template <double>
   inline double get_null_value < double >()
   {
      return 0.0;
   }
   template <double>
   inline double get_unitary_value < double >()
   {
      return 1.0;
   }

   template <BYTE>
   inline BYTE get_maximum_value < BYTE > ()
   {
      return (BYTE) 255;
   }
   template <BYTE>
   inline BYTE get_minimum_value < BYTE > ()
   {
      return (BYTE) 0;
   }
   template <BYTE>
   inline BYTE get_null_value < BYTE > ()
   {
      return 0;
   }
   template <BYTE>
   inline BYTE get_unitary_value < BYTE >()
   {
      return 1;
   }

   template <WORD>
   inline WORD get_maximum_value < WORD > ()
   {
      return static_cast < WORD > (0xffff);
   }
   template <WORD>
   inline WORD get_minimum_value < WORD > ()
   {
      return (WORD) 0;
   }
   template <WORD>
   inline WORD get_null_value < WORD > ()
   {
      return 0;
   }
   template <WORD>
   inline WORD get_unitary_value < WORD >()
   {
      return 1;
   }

   template <DWORD>
   inline DWORD get_maximum_value < DWORD > ()
   {
      return static_cast < DWORD > (0xffffffff);
   }
   template <DWORD>
   inline DWORD get_minimum_value < DWORD > ()
   {
      return (DWORD) 0;
   }
   template <DWORD>
   inline DWORD get_null_value < DWORD > ()
   {
      return 0;
   }
   template <DWORD>
   inline DWORD get_unitary_value < DWORD >()
   {
      return 1;
   }

   template <UINT>
   inline UINT get_maximum_value < UINT > ()
   {
      return static_cast < UINT > (0xffffffff);
   }
   template <UINT>
   inline UINT get_minimum_value < UINT > ()
   {
      return (UINT) 0;
   }
   template <UINT>
   inline UINT get_null_value < UINT > ()
   {
      return 0;
   }
   template <UINT>
   inline UINT get_unitary_value < UINT >()
   {
      return 1;
   }

#else // core_level_3

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

   template <>
   inline UINT get_maximum_value < UINT > ()
   {
      return static_cast < UINT > (0xffffffff);
   }
   template <>
   inline UINT get_minimum_value < UINT > ()
   {
      return (UINT) 0;
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


#endif


} // numeric_info
