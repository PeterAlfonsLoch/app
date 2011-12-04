#pragma once

namespace calculator
{


   class CLASS_DECL_ca2 value
   {
   public:

      enum e_mode
      {
         mode_rectangular,
         mode_polar_radian,
         mode_polar_degree,
      };

      double      m_dR; // real part
      double      m_dI; // imaginary part


      double arg() const;
      double mod() const;


      value();
      ~value();

      string to_string(e_mode mode = mode_rectangular);


   };


   CLASS_DECL_ca2 double pi();

   CLASS_DECL_ca2 calculator::value operator + (const calculator::value & val1, const calculator::value & val2);
   CLASS_DECL_ca2 calculator::value operator - (const calculator::value & val1, const calculator::value & val2);
   CLASS_DECL_ca2 calculator::value operator * (const calculator::value & val1, const calculator::value & val2);
   CLASS_DECL_ca2 calculator::value operator / (const calculator::value & val1, const calculator::value & val2);

   CLASS_DECL_ca2 value pow(const value & val1, const value & val2);

   CLASS_DECL_ca2 value sqr(const value & val);
   CLASS_DECL_ca2 value sqrt(const value & val);
   CLASS_DECL_ca2 value exp(const value & val);
   CLASS_DECL_ca2 value log(const value & val);

} // namespace calculator

