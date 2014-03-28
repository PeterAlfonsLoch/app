#pragma once


namespace html
{


   enum e_position
   {

      PositionRelative,

   };


   enum e_flag
   {
      // the width can be expanded
      FlagWidthExpandable,
      // the height can be expanded
      FlagHeightExpandable,
      // the width is fixed but can grow to make space to a single long uint16_t
      FlagWidthFixedTable,
      // the width is fixed
      FlagWidthFixed,
      // the height is fixed
      FlagHeightFixed,
      // width in percent
      FlagWidthPercent,
      // width in pixel
      FlagWidthPixel,
      FlagWidth,
   };


} // namespace html




