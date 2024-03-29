#ifndef AUTOSAR_STATE_MANAGEMENT_SM_TYPES_H
#define AUTOSAR_STATE_MANAGEMENT_SM_TYPES_H

/** @file sm_types.h
 * @brief State Machine types
 * @details Definitions of types used by SM and its interfaces. */

#include <string>
#include <vector>

namespace ara::sm {

    /** @brief Error type of SM. Fills [SWS_SM_91010]. */
    enum class ErrorType {
        /** No error. */
        kSuccess                          =  0,
        /** Requested operation was rejected due to State Management/machines internal state. */
        kRejected                         =  5,
        /** Requested operation failed. */
        kFailed                           =  6,
        /** Request for new session was rejected as only single active
            (update) session is allowed. */
        kNotAllowedMultipleUpdateSessions =  9,
        /** The provided value is not mapped to any transition */
        kInvalidValue                     = 10,
        /** Requested transition is not possible from current StateMachine state. */
        kTransitionNotAllowed             = 11,
        /** Request will not be carried out, because currently recovery is ongoing. */
        kRecoveryTransitionOngoing       = 12,
        /** During transition to the requested state an error occurred. */
        kTransitionFailed                 = 13,
        /** The request was replaced by a newer one and therefore it was cancelled. */
        kCanceled                         = 14
    };

    /**
    * @brief The state type of the Function Group.
    * @details The element of State Management that characterizes the current status of a set of
    *          (functionally coherent) user-level Applications. */
    enum class FunctionGroupStateType {
        /** function group switched off. */
        Off,
        /** function group working. */
        On,
        /** function group update in progress */
        Update
    };

    /**
    * @brief The state type of the "MachineFG" Function Group
    * @details The state of Function Group "MachineFG" with some predefined states (Startup/Shutdown/Restart).
    *          "MachineFG" is a Function Group with a predefined name, which is mainly used to control Machine
    *          lifecycle and processes of platform level Applications. */
    enum class MachineStateType {
        /** Turning on the machine. */
        Startup,
        /** Machine working state. */
        On,
        /** Turning off the machine. */
        Shutdown,
        /** Restarting the machine. */
        Restart
    };

    /**
     * @brief Fills [SWS_SM_91011]
     * @details Message to all running Processes in the system to indicate a request for a PowerMode switch */
    class PowerModeMsg {
    public:
        /** @brief 'On' - normal operation */
        static inline const std::string On = "On";
        /** @brief 'Off' - persist data preparation for shutdown. */
        static inline const std::string Off = "Off";
        /** @brief 'Suspend' - prepare for suspend2ram. */
        static inline const std::string Suspend = "Suspend";
    };

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
               Diagnostic SoftReset. */
    class DiagnosticResetMsg {
    public:
        /** @brief 'SoftReset' - normal operation */
        static inline const std::string SoftReset = "SoftReset";
    };

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

    /** @brief FunctionGroup shortName type. Fills [SWS_SM_91018]. */
    class FunctionGroupNameType {
    public:
        /** @brief Adaptive Platform Core */
        static inline const std::string core = "core";
        /** @brief Communication Management */
        static inline const std::string com = "com";
        /** @brief Cryptography */
        static inline const std::string crypto = "crypto";
        /** @brief Diagnostics */
        static inline const std::string diag = "diag";
        /** @brief Execution management */
        static inline const std::string exec = "exec";
        /** @brief Firewall */
        static inline const std::string fw = "fw";
        /** @brief Identity and Access Management */
        static inline const std::string iam = "iam";
        /** @brief Intrusion Detection System Manager */
        static inline const std::string idsm = "idsm";
        /** @brief Log and Trace */
        static inline const std::string log = "log";
        /** @brief Network Management */
        static inline const std::string nm   = "nm";
        /** @brief Operating System Interface */
        static inline const std::string na   = "n/a";
        /** @brief Persistency */
        static inline const std::string per  = "per";
        /** @brief Platform Health Management */
        static inline const std::string phm  = "phm";
        /** @brief State Management */
        static inline const std::string sm   = "sm";
        /** @brief Time Synchronization */
        static inline const std::string tsync  = "tsync";
        /** @brief Update and Configuration Management */
        static inline const std::string ucm  = "ucm";
    };

    /** @brief A list of FunctionGroups type. Fills [SWS_SM_91019]. */
    typedef std::vector<std::string> FunctionGroupListType;

    /**
    * @brief Fills [SWS_SM_91009]
    * @details Type used for triggering SM state change */
    class TriggerInOutNotifierType {
    public:
        TriggerInOutNotifierType() :
            result(ErrorType::kFailed),
            currentSMState(FunctionGroupStateType::Off) {}
    public:
        /** @brief To inform applications about state transition */
        sm::ErrorType result;
        /** @brief SM state after processing trigger */
        FunctionGroupStateType currentSMState;
    };

    /**
    * @brief Fills [SWS_SM_91007]
    * @details Type used for triggering SM state change */
    class TriggerType {
    public:
        /** @brief TriggerType default constructor */
        TriggerType() :
            isNewTrigger(false),
            desiredSMState(FunctionGroupStateType::Off) {}
        /** @brief To inform SM about incoming trigger */
        bool isNewTrigger;
        /** @brief Desired SM state after trigger */
        FunctionGroupStateType desiredSMState;
    };
}

#endif //AUTOSAR_STATE_MANAGEMENT_SM_TYPES_H
