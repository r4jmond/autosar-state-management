//
// Created by Filip Księżyc on 21.01.2023.
//

#include "communication_group_server.h"

namespace ara {
    namespace com {
        template<class T>
        bool CommunicationGroupServer<T>::addClientToGroup(std::string name, T powerModeCOM){
            if(groupClients.count(name) == 0)
                return false;
            else{
                groupClients.insert(name, powerModeCOM);
                return true;
            }
        }


        template <class T>
        void CommunicationGroupServer<T>::broadcast(std::string msg) {
            for(const auto& kv : groupClients){
                PowerMode* powerMode = &kv.second;
                powerMode->message(msg);
            }
        }


        template <class T>
        bool CommunicationGroupServer<T>::message(std::string clientID, std::string msg) {
            if(groupClients.count(name) == 0)
                return false;
            else{
                PowerMode* powerMode = &groupClients[clientID];
                powerMode->message(msg);
                return true;
            }
        }

        template <class T>
        std::vector<std::string> CommunicationGroupServer<T>::listClients() {
            std::string tmp = "";
            for(const auto& kv : groupClients){
                tmp = tmp + kv.first;
            }

            return tmp;
        }

        template <class T>
        std::map<std::string, T> CommunicationGroupServer<T>::response() {
            return groupClients;
        }
    } // ara
} // com