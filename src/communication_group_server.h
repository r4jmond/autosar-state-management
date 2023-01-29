#ifndef AUTOSAR_STATE_MANAGEMENT_COMMUNICATION_GROUP_SERVER_H
#define AUTOSAR_STATE_MANAGEMENT_COMMUNICATION_GROUP_SERVER_H
/** @file communication_group_server.h
  * @brief Power Mode interface propagates a diagnostic Power Mode request to all running Processes. */

#include "sm_types.h"

namespace ara::com {
        /** @brief Class CommunicationGroupServer
         *         Fills [SWS_SM_91020]. */
        template<class T>
        class CommunicationGroupServer {
        private:
            std::map<std::string, T> groupClients;

        public:
            /** @brief CommunicationGroupServer constructor. */
            CommunicationGroupServer() : groupClients() {}

            /** @brief CommunicationGroupServer parametrized constructor with map object as arguemtn. */
            CommunicationGroupServer(std::map<std::string, T> map) : groupClients{map} {}


        public:
            /**
            * @brief addClientToGroup
            * @details Connect client PowerMode interface to this server to provide proper communication and power
            mode change notification.
            * @param[in] name - client identifier
            * @param[in] powerModeCOM - client power mode communication interface
            * @return true if succeed, false if client with this identifier exists
            */
            bool addClientToGroup(std::string name, T powerModeCOM){
                if(groupClients.count(name) == 0)
                {
                    return false;
                }
                else{
                    groupClients.insert(name, powerModeCOM);
                    return true;
                }
            }

            /**
            * @brief broadcast
            * @details Send PowerMode message to all clients in group;
            * @param[in] msg - PowerMode string message
            * @return None
            */
            void broadcast(std::string msg)
            {
                for(const auto& kv : groupClients)
                {
                    PowerMode* powerMode = &kv.second;
                    powerMode->message(msg);
                }
            }

            /**
            * @brief listClients
            * @details Get list of all clients as vector;
            * @return vector of strings
            */
            std::vector<std::string> listClients()
            {
                std::string tmp = "";
                std::vector<std::string> listOfClients(10);
                for(const auto& kv : groupClients)
                {
                    listOfClients.push_back(kv.first);
                }

                return listOfClients;
            }

            /**
            * @brief message
            * @details Send PowerMode message to selected client in group;
            * @param[in] clientID - selected client identifier
            * @param[in] msg - PowerMode string message
            * @return true if succeed, false if client with this identifier exists
            */
            bool message(std::string clientID, std::string msg)
            {
                if(groupClients.count(clientID) == 0)
                {
                    return false;
                }
                else
                {
                    PowerMode* powerMode = &groupClients[clientID];
                    powerMode->message(msg);
                    return true;
                }
            }

            /**
            * @brief response
            * @details Get set of pairs key-value, where key is client identifier and value is PowerMode object
              associated with concrete specific client group;
            * @return map set of client identifiers and PowerMode objects
            */
            std::map<std::string, T> response()
            {
                return groupClients;
            }
        };

} // ara::com

#endif //AUTOSAR_STATE_MANAGEMENT_COMMUNICATION_GROUP_SERVER_H