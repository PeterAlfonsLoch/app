#pragma once

class CLASS_DECL_CA2_CUBE AlbumViewUpdateHint : public ::radix::object  
{
   
public:
   AlbumViewUpdateHint();
   AlbumViewUpdateHint(AlbumViewUpdateHint & uh);
   virtual ~AlbumViewUpdateHint();

public:
   AlbumViewUpdateHint & operator =(AlbumViewUpdateHint &uh);
   VMSRESULT copy(AlbumViewUpdateHint & uh);

   int m_i;
   string m_str;
   int m_iKey;
};
