#pragma once


namespace xml
{

   
   class CLASS_DECL_BASE entity
   {
   public:

      
      char     m_chEntity;      // entity ( & " ' < > )
      string   m_strRef;      // entity reference ( &amp; &quot; etc )
      int32_t      m_iRefLen;      // entity reference length

      
      entity();
      entity(char chEntity, const char * pszReference);
      entity(const entity & entity);
      entity & operator = (const entity & entity);
      
      
   };

   
   class CLASS_DECL_BASE entities : 
      public array < entity >
   {
   public:
   
      
      entity * get_entity( int32_t entity );
      entity * get_entity(const char * pszEntity);

      int32_t get_entity_count( const char * str );

      int32_t ref_to_entity( const char * estr, char * str, int32_t strlen );
      int32_t entity_to_ref( const char * str, char * estr, int32_t estrlen );

      string ref_to_entity( const char * estr );
      string entity_to_ref( const char * str );   

      void add_entity(char chEntity, const char * pszReference);

      
   };

   
   string XRef2Entity( const char * estr );
   string XEntity2Ref( const char * str );   
   

} // namespace xml




