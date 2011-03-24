#pragma once

namespace mediaplay
{

   class data;
   class view;

   class CLASS_DECL_ca document :
      virtual public ::userbase::document
   {
   public:
      
      
      data *   m_pdata;
      view *   m_pview;
      bool     m_bWriting;


      document(::ca::application * papp);
      virtual ~document();

      data *   get_data();
      view *       GetMediaView();

      bool on_open_document(var varFile);
      virtual void delete_contents(); // delete doc items etc

   };

} // namespace mediaplay

