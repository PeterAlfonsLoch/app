#pragma once


namespace libepp 
{

   /// EPP IpNetworkInfoResponse Class
   class IpNetworkInfoResponse : public Response
   {
   public:
      /// EPP Network Class used in IpNetworkInfoResponse Class
      class Network
      {
      public:
         /// Default constructor
         Network()
         {
            this->reset();
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
            _ipRange.reset();
            _roid = "";
         }

      private:
         /// ip range
         IpRange _ipRange;

         /// server-unique id for the created IP network
         string _roid;
      };

      /// EPP IpRangeInfo Class used in IpRangeInfoResponse Class
      class IpRangeInfo
      {
      public:
         /// Default constructor
         IpRangeInfo()
         {
            this->reset();
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

         /// Sets allocation type
         /**
         @param allocType   ip range allocation type
         */
         void set_allocType(const char *allocType)
         {
            _allocType = allocType;
         }

         /// Returns allocation type
         /**
         @return ip range allocation type
         */
         string get_allocType() const
         {
            return _allocType;
         }

         /// Sets organization
         /**
         @param organization   organization to be associated with the ip range
         */
         void set_organization(const char *organization)
         {
            _organization = organization;
         }

         /// Returns organization associated with the ip range
         /**
         @return organization owner of the ip range
         */
         string get_organization() const
         {
            return _organization;
         }

         /// Inserts a contact in the map of other contacts
         /**
         @param type             contact type
         @param identification   contact identification
         */
         void insert_contact(const char *type, const char *identification)
         {
            _contacts[type] = identification;
         }

         /// Returns map of other contacts
         /**
         @return map of other contacts
         */
         string_to_string_map get_contacts() const 
         { 
            return _contacts; 
         }

         /// Sets asn
         /**
         @param asn   autonomous system number that is going to manage the 
         ip range
         */
         void set_asn(const int asn)
         {
            _asn = asn;
         }

         /// Returns asn
         /**
         @return autonomous system number that manages the ip range
         */
         int get_asn() const
         {
            return _asn;
         }

         /// Sets reverse dns
         /**
         @param reverseDns   delegation information for the ip range
         */
         void insert_reverseDns(const ReverseDns &reverseDns)
         {
            _reversesDns.add(reverseDns);
         }

         /// Returns reverses dns
         /**
         @return all delegation information for the ip range
         */
         comparable_array<ReverseDns> get_reversesDns() const
         {
            return _reversesDns;
         }

         /// Sets parent network
         /**
         @param parentNetwork   range of IP addresses and roid of the parent 
         IP network
         */
         void set_parentNetwork(const Network &network)
         {
            _parentNetwork = network;
         }

         /// Returns parent network
         /**
         @return range of IP addresses and roid of the parent IP network
         */
         Network get_parentNetwork() const
         {
            return _parentNetwork;
         }

         /// Inserts child network
         /**
         @param network   IP address and roid of allocated or assigned 
         subnetwork of the IP network
         */
         void insert_childNetwork(const Network &network)
         {
            _childNetworks.add(network);
         }

         /// Returns child networks
         /**
         @return range of IP addresses and roids of allocated or assigned 
         subnetworks of the IP network
         */
         comparable_array<Network> get_childNetworks() const
         {
            return _childNetworks;
         }

         /// Sets sponsoring client
         /**
         @param clId   identifier of the client that created the IP 
         network object
         */
         void set_clId(const string& clId)
         {
            _clId = clId;
         }

         /// Returns sponsoring client
         /**
         @return identifier of the client that created the IP network object
         */
         string get_clId() const
         {
            return _clId;
         }

         /// Sets client that created the ip range
         /**
         @param crId   identifier of the client that created the IP 
         network object
         */
         void set_crId(const string& crId)
         {
            _crId = crId;
         }

         /// Returns client that created the ip range
         /**
         @return identifier of the client that created the IP network object
         */
         string get_crId() const
         {
            return _crId;
         }

         /// Sets date of the ip range creation
         /**
         @param crDate   date and time of the IP network object creation
         */
         void set_crDate(const string& crDate)
         {
            _crDate = crDate;
         }

         /// Returns date of the ip range creation
         /**
         @return date and time of the IP network object creation
         */
         string get_crDate() const
         {
            return _crDate;
         }

         /// Sets ip range's expiration date
         /**
         @param exDate   date and time identifying the end of the IP network
         object registration period
         */
         void set_exDate(const char *exDate)
         {
            _exDate = exDate;
         }

         /// Returns ip range's expiration date
         /**
         @return date and time identifying the end of the IP network object
         registration period
         */
         string get_exDate() const
         {
            return _exDate;
         }

         /// Sets last client that updated the ip range
         /**
         @param upId   identifier of the client that last updated the network 
         object
         */
         void set_upId(const char *upId)
         {
            _upId = upId;
         }

         /// Returns last client that updated  the ip range
         /**
         @return identifier of the client that last updated the network object
         */
         string get_upId() const
         {
            return _upId;
         }

         /// Sets date of the last update
         /**
         @param upDate   date and time of the most recent network object 
         modification
         */
         void set_upDate(const char *upDate)
         {
            _upDate = upDate;
         }

         /// Returns date of the last update
         /**
         @return date and time of the most recent network object modification
         */
         string get_upDate() const
         {
            return _upDate;
         }

         /// Sets most recent successful IP network object transfer
         /**
         @param trDate   most recent successful IP network object transfer
         */
         void set_trDate(const char *trDate)
         {
            _trDate = trDate;
         }

         /// Returns most recent successful IP network object transfer
         /**
         @return most recent successful IP network object transfer
         */
         string get_trDate() const
         {
            return _trDate;
         }

         void reset()
         {
            _roid = "";
            _allocType = "";
            _organization = "";
            _contacts.remove_all();
            _asn = 0;
            _reversesDns.remove_all();
            _parentNetwork.reset();
            _childNetworks.remove_all();
            _clId = "";
            _crId = "";
            _crDate = "";
            _exDate = "";
            _upId = "";
            _upDate = "";
            _trDate = "";
         }

      private:
         /// server-unique id for the created IP network
         string _roid;

         /// allocation type    
         string _allocType;

         /// organization identifier that manages the IP network
         string _organization;

         /// indentifiers for contact objects associated with the IP network
         string_to_string_map _contacts;

         /// Autonomous System Number that manages the network    
         int _asn;

         /// DNS delegation information for the IP network
         comparable_array<ReverseDns> _reversesDns;

         /// range of IP addresses and roid of the parent IP network
         Network _parentNetwork;

         /// range of IP addresses and roids of allocated or assigned 
         /// subnetworks of the IP network
         comparable_array<Network> _childNetworks;

         /// identifier of the sponsoring client
         string _clId;

         /// identifier of the client that created the IP network object
         string _crId;

         /// date and time of the IP network object creation
         string _crDate;

         /// date and time identifying the end of the IP network object
         /// registration period
         string _exDate;

         /// identifier of the client that last updated the network object
         string _upId;

         /// date and time of the most recent network object modification
         string _upDate;

         /// most recent successful IP network object transfer
         string _trDate;
      };

      /// Default constructor
      IpNetworkInfoResponse(bool reset = false) : Response(false)
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

      /// Inserts ip range info
      /**
      @param ipRangeInfo   information about an ip range
      */
      void insert_ipRangeInfo(const IpRangeInfo &ipRangeInfo)
      {
         _ipRangeInfo.add(ipRangeInfo);
      }

      /// Returns list of all ip range infos
      /**
      @return information about an ip range
      */
      comparable_array<IpRangeInfo> get_ipRangeInfo() const
      {
         return _ipRangeInfo;
      }

      void reset()
      {
         Response::reset();
         _ipRange.reset();
         _ipRangeInfo.remove_all();
      }

   protected:
      /// ip range
      IpRange _ipRange;

      /// ip range info
      comparable_array<IpRangeInfo> _ipRangeInfo;
   };

} // namespace libepp
