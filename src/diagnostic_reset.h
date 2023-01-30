#ifndef AUTOSAR_STATE_MANAGEMENT_DIAGNOSTIC_RESET_H
#define AUTOSAR_STATE_MANAGEMENT_DIAGNOSTIC_RESET_H
/** @file  diagnostic_reset.h
  * @brief Diagnostic Reset interface propagates a diagnostic Reset message to processes form state management. */

#include "sm_types.h"

namespace ara::sm {
        /** @brief Class DiagnosticReset to be used by State Management and processes in SoftwareCluster.
          *         Fills [SWS_SM_91015]. */
        class DiagnosticReset {
            private:
               bool msgToProcesses;
               bool msgToStateMachine;
               DiagnosticResetRespMsg processResponse;
               std::string diagnosticResetMsg;


            public:
               /** @brief DiagnosticReset constructor. */
               DiagnosticReset() : msgToProcesses{false}, msgToStateMachine{false} {}

               /**
                * @brief Event
                * @details  All Processes which got a DiagnosticReset request sends this as answer to State Management
                * @param[in] respondMsg - ResponseMessage from a Processes which received DiagnosticReset request from
                                          State Management.
                * @return None
               */
               void Event(DiagnosticResetRespMsg respondMsg);

               /**
                * @brief Message
                * @details . sends DiagnosticResetMsg to all Processes in a SoftwareCluster.
                * @param[in] msg - Message to all running Processes in the SoftwareCluster to indicate a request to
                                   perform softReset.
                * @return true if operation succeed or false if failed (for example inappropriate)
               */
               bool Message(std::string msg);


            public:
               /**
                * @brief TryGetDiagnosticResetMsg
                * @details HMethod used by process to check if diagnostic reset message is sent and to acquire it from
                           interface.
                * @param[in] *msg - pointer to DiagnosticResetMsg type object.
                * @return bool true if message can be read or false if there is no messages to get.
               */
               bool TryGetDiagnosticResetMsg(std::string *msg);

               /**
                 * @brief TryGetDiagnosticResetMsgResponse
                 * @details Method used by SM to check if response to diagnostic reset message is sent and to acquire it.
                 * @param[in] *msg - pointer to DiagnosticResetRespMsg type object.
                 * @return bool true if message can be read or false if there is no messages to get.
               */
               bool TryGetDiagnosticResetMsgResponse(DiagnosticResetRespMsg *respondMsg);
        };
} // ara::sm

#endif //AUTOSAR_STATE_MANAGEMENT_DIAGNOSTICRESET_H
