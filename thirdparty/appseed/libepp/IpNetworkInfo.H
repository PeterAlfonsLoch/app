#pragma once


namespace libepp 
{

   /// EPP IpNetworkInfo Class
   class IpNetworkInfo : public Action
   {
   public:
      /// Constructor
      IpNetworkInfo(const ActionType type = IP_NETWORK_INFO) : Action(type)
      {
         if (type == IP_NETWORK_INFO) {
            _command = new IpNetworkInfoCommand();
            _response = new IpNetworkInfoResponse();
         }
      }

      /// Sets XML template
      /**
      @param xml_template   XML command template
      */
      void set_xml_template(DomParser * pparser, const char * xml_template);

      /// Pure virtual method to comparable_array response from a XML document
      /**
      @param xml_payload   XML document
      @param parser        reference to the XML parser
      */
      void set_response(const char *xml_payload, DomParser *parser) 
      {
         get_response()->reset();
         parser->parse_ipnetwork_info_response(xml_payload, get_response());
      }

      /// Returns raw pointer to the command
      /**
      @return raw pointer to the command
      */
      IpNetworkInfoCommand* get_command() 
      {
         return (IpNetworkInfoCommand*) _command.get_p(); 
      }

      /// Returns raw pointer to the response
      /**
      @return raw pointer to the response
      */
      IpNetworkInfoResponse* get_response() 
      { 
         return (IpNetworkInfoResponse*) _response.get_p(); 
      }
   };

} // namespace libepp
