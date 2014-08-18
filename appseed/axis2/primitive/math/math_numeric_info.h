#pragma once




namespace numeric_info
{


   template < typename T >
   inline T get_maximum_value();

   template < typename T >
   inline T get_minimum_value();

   template < typename T >
   inline T get_null_value();

   template < typename T >
   inline T get_unitary_value();

   template < typename T >
   inline T get_allset_value();

   template < typename T >
   inline bool is_signed();

   template < typename T >
   inline bool is_integer();






   template <>
   inline int32_t get_maximum_value < int32_t > ()
   {
      return (int32_t) 0x7fffffff;
   }
   template <>
   inline int32_t get_minimum_value < int32_t > ()
   {
      return (int32_t) 0x80000000;
   }
   template <>
   inline int32_t get_null_value < int32_t > ()
   {
      return 0;
   }
   template <>
   inline int32_t get_unitary_value < int32_t >()
   {
      return 1;
   }
   template <>
   inline bool is_signed < int32_t >()
   {
      return true;
   }
   template <>
   inline bool is_integer < int32_t >()
   {
      return true;
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
   inline bool is_signed < float >()
   {
      return true;
   }
   template <>
   inline bool is_integer < float >()
   {
      return false;
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
   inline bool is_signed < double >()
   {
      return true;
   }
   template <>
   inline bool is_integer < double >()
   {
      return false;
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
   inline bool is_signed < BYTE >()
   {
      return false;
   }
   template <>
   inline bool is_integer < BYTE >()
   {
      return true;
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
   inline bool is_signed < WORD >()
   {
      return false;
   }
   template <>
   inline bool is_integer < WORD >()
   {
      return true;
   }



   template <>
   inline uint32_t get_maximum_value < uint32_t > ()
   {
      return static_cast < uint32_t > (0xffffffff);
   }
   template <>
   inline uint32_t get_minimum_value < uint32_t > ()
   {
      return (uint32_t) 0;
   }
   template <>
   inline uint32_t get_null_value < uint32_t > ()
   {
      return 0;
   }
   template <>
   inline uint32_t get_unitary_value < uint32_t >()
   {
      return 1;
   }
   template <>
   inline bool is_signed < uint32_t >()
   {
      return false;
   }
   template <>
   inline bool is_integer < uint32_t >()
   {
      return true;
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
   inline bool is_signed < uint64_t >()
   {
      return false;
   }
   template <>
   inline bool is_integer < uint64_t >()
   {
      return true;
   }




   template <>
   inline int64_t get_maximum_value < int64_t > ()
   {
      return static_cast < int64_t > (0x7ffffffffffffffful);
   }
   template <>
   inline int64_t get_minimum_value < int64_t > ()
   {
      return static_cast < int64_t > (0x8000000000000000ul);
   }
   template <>
   inline int64_t get_null_value < int64_t > ()
   {
      return 0;
   }
   template <>
   inline int64_t get_unitary_value < int64_t >()
   {
      return 1;
   }
   template <>
   inline bool is_signed < int64_t >()
   {
      return true;
   }
   template <>
   inline bool is_integer < int64_t >()
   {
      return true;
   }



/*   template <>
   inline bool is_signed < size_t >()
   {
      return false;
   }
   template <>
   inline bool is_integer < size_t >()
   {
      return true;
   }
*/

   template < typename T > class offset { public: typedef T TYPE; };

   template < > class CLASS_DECL_AXIS offset < uchar > { public: typedef char TYPE; };
   template < > class CLASS_DECL_AXIS offset < uint16_t > { public: typedef int16_t TYPE; };
   template < > class CLASS_DECL_AXIS offset < uint32_t > { public: typedef int32_t TYPE; };
   template < > class CLASS_DECL_AXIS offset < uint64_t > { public: typedef int64_t TYPE; };

   template < typename T > class type { public: typedef T TYPE; };


} // numeric_info



