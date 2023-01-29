#ifndef AUTOSAR_STATE_MANAGEMENT_EXECUTION_CLIENT_H
#define AUTOSAR_STATE_MANAGEMENT_EXECUTION_CLIENT_H
/** @file execution_client.h
 * @brief Execution Client header file. */

#include "sm_types.h"

namespace ara::exec {
    class ExecutionClient {
    public:
        /**
        * @brief ReportApplicationState
        * @details Provides functionality for a Process to report its execution state to Execution Management
        */
        virtual void ReportApplicationState(sm::SMStateType state) {};
        virtual ~ExecutionClient() = default;;
    };
}

#endif //AUTOSAR_STATE_MANAGEMENT_EXECUTION_CLIENT_H
