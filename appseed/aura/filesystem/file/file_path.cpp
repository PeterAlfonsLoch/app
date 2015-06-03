
namespace path
{

   
   ::file::path app_install()
   {

      return ::dir::app_install() / "app.install.exe";

   }

   ::file::path a_spa()
   {

      return ::dir::a_spa() / "a_spa.exe";

   }


   ::file::path a_spaadmin()
   {

      return ::dir::a_spa() / "a_spaadmin.exe";

   }



} // namespace path