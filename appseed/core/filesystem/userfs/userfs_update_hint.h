#pragma once


namespace userfs
{


   class CLASS_DECL_CORE update_hint :
      virtual public object
   {
   public:


      enum e_type
      {

         type_synchronize_path,
         type_update_list_columns,

      };


      string                     m_strPath;
      e_type                     m_etype;
      ::action::context         m_actioncontext;


      update_hint();
      virtual ~update_hint();


      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);


   };



} // namespace userfs




