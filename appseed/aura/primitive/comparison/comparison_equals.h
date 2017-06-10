#pragma once


namespace comparison
{

   class equals
   {
   public:

      template < typename TYPE >
      static inline bool run(TYPE element1, TYPE element2)
      {

         return element1 == element2;

      }

   };




} // namespace comparison


namespace comparisontest
{

   class equals
   {
   public:

      template < typename TYPE >
      static inline bool run(TYPE element1, TYPE element2)
      {

         return element1 == element2;

      }

   };




} // namespace comparison




namespace comparisonok
{

   class equals
   {
   public:

      template < typename TYPE >
      static inline bool run(TYPE element1, TYPE element2)
      {

         return element1 == element2;

      }

   };




} // namespace comparison