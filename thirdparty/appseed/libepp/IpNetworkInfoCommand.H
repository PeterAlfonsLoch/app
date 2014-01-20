#pragma once


namespace libepp 
{

   /// EPP IpNetworkInfo Class
   class IpNetworkInfoCommand : public Command
   {
   public:
      /// Default constructor
      IpNetworkInfoCommand(bool reset = true) : Command(false)
      {
         if (reset) {
            this->reset();
         }
      }

      /// Sets ip range
      /**
      @param ipRange  ip range
      */
      void set_ipRange(const IpRange &ipRange)
      {
         _ipRange = ipRange;
      }

      /// Returns ip range
      /**
      @return ip range
      */
      IpRange get_ipRange() const
      {
         return _ipRange;
      }

      /// Sets repository object ID
      /**
      @param roid   contains the server-unique id for the created IP network
      */
      void set_roid(const char *roid)
      {
         _roid = roid;
      }

      /// Returns repository object ID
      /**
      @return server-unique id for the created IP network
      */
      string get_roid() const
      {
         return _roid;
      }

      void reset()
      {
         Command::reset();
         _ipRange.reset();
         _roid = "";
      }

   protected:
      /// ip range
      IpRange _ipRange;

      /// server-unique id for the created IP network
      string _roid;
   };

} // namespace libepp
