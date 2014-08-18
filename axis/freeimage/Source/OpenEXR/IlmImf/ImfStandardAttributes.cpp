#include "Imf.h"


#define IMF_STRING(name) #name

#define IMF_STD_ATTRIBUTE_IMP(name,suffix,type)				 \
									 \
    void								 \
    add##suffix (Header &header, const type &value)			 \
    {									 \
	header.insert (IMF_STRING (name), TypedAttribute<type> (value)); \
    }									 \
									 \
    bool								 \
    has##suffix (const Header &header)					 \
    {									 \
	return header.findTypedAttribute <TypedAttribute <type> >	 \
		(IMF_STRING (name)) != 0;				 \
    }									 \
									 \
    const TypedAttribute<type> &					 \
    name##Attribute (const Header &header)				 \
    {									 \
	return header.typedAttribute <TypedAttribute <type> >		 \
		(IMF_STRING (name));					 \
    }									 \
									 \
    TypedAttribute<type> &						 \
    name##Attribute (Header &header)					 \
    {									 \
	return header.typedAttribute <TypedAttribute <type> >		 \
		(IMF_STRING (name));					 \
    }									 \
									 \
    const type &							 \
    name (const Header &header)						 \
    {									 \
	return name##Attribute(header).value();				 \
    }									 \
									 \
    type &								 \
    name (Header &header)						 \
    {									 \
	return name##Attribute(header).value();				 \
    }


namespace Imf {

   
IMF_STD_ATTRIBUTE_IMP (chromaticities, Chromaticities, Chromaticities)
IMF_STD_ATTRIBUTE_IMP (whiteLuminance, WhiteLuminance, float)
IMF_STD_ATTRIBUTE_IMP (adoptedNeutral, AdoptedNeutral, Imath::V2f)
IMF_STD_ATTRIBUTE_IMP (renderingTransform, RenderingTransform, std::string)
IMF_STD_ATTRIBUTE_IMP (lookModTransform, LookModTransform, std::string)
IMF_STD_ATTRIBUTE_IMP (xDensity, XDensity, float)
IMF_STD_ATTRIBUTE_IMP (owner, Owner, std::string)
IMF_STD_ATTRIBUTE_IMP (comments, Comments, std::string)
IMF_STD_ATTRIBUTE_IMP (capDate, CapDate, std::string)
IMF_STD_ATTRIBUTE_IMP (utcOffset, UtcOffset, float)
IMF_STD_ATTRIBUTE_IMP (longitude, Longitude, float)
IMF_STD_ATTRIBUTE_IMP (latitude, Latitude, float)
IMF_STD_ATTRIBUTE_IMP (altitude, Altitude, float)
IMF_STD_ATTRIBUTE_IMP (focus, Focus, float)
IMF_STD_ATTRIBUTE_IMP (expTime, ExpTime, float)
IMF_STD_ATTRIBUTE_IMP (aperture, Aperture, float)
IMF_STD_ATTRIBUTE_IMP (isoSpeed, IsoSpeed, float)
IMF_STD_ATTRIBUTE_IMP (envmap, Envmap, Envmap)
IMF_STD_ATTRIBUTE_IMP (keyCode, KeyCode, KeyCode)
IMF_STD_ATTRIBUTE_IMP (timeCode, TimeCode, TimeCode)
IMF_STD_ATTRIBUTE_IMP (wrapmodes, Wrapmodes, std::string)
IMF_STD_ATTRIBUTE_IMP (framesPerSecond, FramesPerSecond, Rational)
IMF_STD_ATTRIBUTE_IMP (multiView, MultiView, StringVector)
IMF_STD_ATTRIBUTE_IMP (worldToCamera, WorldToCamera, Imath::M44f)
IMF_STD_ATTRIBUTE_IMP (worldToNDC, WorldToNDC, Imath::M44f)

} // namespace Imf
