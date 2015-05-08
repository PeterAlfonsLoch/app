
namespace user
{

   application_as_proxy_document::application_as_proxy_document(::aura::application * papp):
      object(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {
   }


   application_as_proxy_document::~application_as_proxy_document()
   {
   }


   bool application_as_proxy_document::on_open_document(var varFile)
   {
      
      return Application.on_open_document(this,varFile);

   }

   
   bool application_as_proxy_document::on_save_document(var varFile)
   {

      return Application.on_save_document(this,varFile);

   }



} // namespace user