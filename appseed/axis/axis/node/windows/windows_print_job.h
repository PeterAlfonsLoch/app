#pragma once


namespace windows
{


	class CLASS_DECL_AXIS print_job :
	   virtual public ::user::print_job
	{
	public:


	   print_job(sp(::aura::application) papp);
	   virtual ~print_job();


	   virtual int32_t run();

	};


} // namespace windows




