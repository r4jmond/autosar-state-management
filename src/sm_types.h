#ifndef AUTOSAR_STATE_MANAGEMENT_SM_TYPES_H
#define AUTOSAR_STATE_MANAGEMENT_SM_TYPES_H

/** @file sm_types.h
 * @brief State Machine types
 * @details Definitions of types used by SM and its interfaces. */

#include <string>
#include <vector>

namespace ara { namespace sm {

    /** @brief List of SM stateMachine states. Fills [RS_SM_00005]. */
    enum class SMStateType {
        Start_Engine,
        Drive,
        Shutdown
    };

    /** @brief Error type of SM. Fills [SWS_SM_91010]. */
    enum class ErrorType {
        /** No error. */
        kSuccess        = 0,
        /** Requested operation was rejected due to State Management machines internal state. */
        kRejected       = 5,
        /** Verification step of update failed. */
        kVerifyFailed   = 6,
        /** Preparation step of update failed. */
        kPrepareFailed  = 7,
        /** Rollback step of update failed. */
        kRollbackFailed = 8,
        /** Request for new session was rejected as only single active
            (update) session is allowed. */
        kNotAllowedMultipleUpdateSessions = 9
    };

    /**
     * @brief Fills [SWS_SM_91011]
     * @details Message to all running Processes in the system to indicate a request for a PowerMode
                switch.
     * 'On' - normal operation
     * 'Off' - persist data preparation for shutdown.
     * 'Suspend' - prepare for suspend2ram. */
    typedef std::string PowerModeMsg;

    /**
     * @brief Fills [SWS_SM_91012]
     * @details Reply message from Process, which received PowerModeMessage from State Management. */
    enum class PowerModeRespMsg {
        /** requested mode successfully reached. */
        kDone,
        /** requested mode not reached. */
        kFailed,
        /** can't process requested mode e.g. important things are ongoing. */
        kBusy,
        /** requested mode not supported. */
        kNotSupported
    };

    /**
    * @brief Fills [SWS_SM_91013]
    * @details Message to all Processes(in a SoftwareCluster) to indicate a request to perform
               Diagnostic SoftReset.
    * @enum 'SoftReset' - normal operation */
    typedef std::string DiagnosticResetMsg;

    /**
 * @brief Fills [SWS_SM_91014]
 * @details Reply message from Process, which received DiagnosticResetMessage from State Management. */
    enum class DiagnosticResetRespMsg {
        /** reset performed successfully. */
        kDone,
        /** reset not succesfully performed. */
        kFailed,
        /** can’t perform reset(e.g. important things are ongoing). */
        kBusy,
        /** reset not supported. */
        kNotSupported
    };


    /** @brief FunctionGroup shortName. Fills [SWS_SM_91018]. */
    typedef std::string FunctionGroupNameType;
    /** @brief A list of FunctionGroups. Fills [SWS_SM_91019]. */
    typedef std::vector<FunctionGroupNameType> FunctionGroupListType;

    /** @brief List of used FunctionGroups. Fills [SWS_SM_00001].
     *  @details Normally it would be read from manifest, but we use static configuration here */
    FunctionGroupListType GlobalFunctionGroupList = {"sm", "exec", "phm", "diag", "ucm", "nm"};


}}

#endif //AUTOSAR_STATE_MANAGEMENT_SM_TYPES_H
