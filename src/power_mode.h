#ifndef AUTOSAR_STATE_MANAGEMENT_POWER_MODE_H
#define AUTOSAR_STATE_MANAGEMENT_POWER_MODE_H
/** @file PowerMode.h
  * @brief Power Mode interface propagates a diagnostic Power Mode request to all running Processes. */

#include "sm_types.h"

namespace ara::com {
        /** @brief Class PowerMode to be used by CommunicationGroup Client and Server
         *         Fills [SWS_SM_91020]. */
        class PowerMode {
            private:
                bool msgToProcesses;
                bool msgToStateMachine;
                sm::PowerModeRespMsg processResponse;
                std::string powerModeMsg;


            public:
                /** @brief PowerMode constructor. */
                PowerMode() : msgToProcesses{false}, msgToStateMachine{false} {}

                /**
                 * @brief Event
                 * @details All Processes which have received a Power Mode request shall call this method to provide
                    an answer toState Management.
                 * @param[in] respondMsg - ResponseMessage from a Processes which received PowerMode request from
                    State Management.
                 * @return None
                */
                void Event(sm::PowerModeRespMsg respondMsg);

                /**
                 * @brief Message
                 * @details Sends a Power Mode request to all running Processes.
                 * @param[in] msg - Message to all running Processes in the system to indicate a request to enter this
                    state.
                 * @return true if operation succeed or false if failed (for example inappropriate)
                */
                bool Message(std::string msg);


            public:
                /**
                 * @brief TryGetPowerMsg
                 * @details HMethod used by process to check if power message is sent and to acquire it from interface.
                 * @param[in] *msg - pointer to PowerModeMsg type object.
                 * @return bool true if message can be read or false if there is no messages to get.
                */
                bool TryGetPowerMsg(std::string *msg);

                /**
                  * @brief TryGetPowerMsgResponse
                  * @details HMethod used by SM to check if response to power message is sent and to acquire it.
                  * @param[in] *msg - pointer to PowerModeRespMsg type object.
                  * @return bool true if message can be read or false if there is no messages to get.
                */
                bool TryGetPowerMsgResponse(sm::PowerModeRespMsg *respondMsg);
            };

}

#endif //AUTOSAR_STATE_MANAGEMENT_POWER_MODE_H