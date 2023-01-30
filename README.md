# Autosar State Management
Basic Autosar Adaptive Platform State Management module implementation

## Cloning the repo with Google Test

`git clone --recurse-submodules https://github.com/r4jmond/autosar-state-management.git`

## Prerequisites

* gcc
* Gcov
* Cppcheck
* Google Test
* gMock

## Useful information
* [RS State Management](doc/AUTOSAR_RS_StateManagement.pdf) - State Management Requirement
* [SWS State Management](doc/AUTOSAR_SWS_StateManagement.pdf) -  State Management Software Specification
* Naming conventions - [RS General](doc/AUTOSAR_RS_General.pdf) - RS_AP_00122 and below  
* Namespaces -  [RS General](doc/AUTOSAR_RS_General.pdf) - RS_AP_00115 - everything shall be in ara namespace and namespace specific to function group - names 
[here](doc/AUTOSAR_TR_FunctionalClusterShortnames.pdf)
* [Cpp Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)

All documents can be found in [doc](doc) directory.



## Cppcheck configuration
For Cppcheck CLion integration:
1. Install [Cppcheck](https://cppcheck.sourceforge.io/)
2. Install [Cppcheck CLion plugin](https://plugins.jetbrains.com/plugin/8143-cppcheck)
3. In CLion go to settings -> Cppcheck Configuration. Set valid Cppcheck path and add those options:

`--language=c++ --std=c++17 --enable=all --addon=cert.py`

For use without CLion, just [Install Cppcheck](https://cppcheck.sourceforge.io/) and run it with flags from above.

## Differences against full implementation

* Completely static configuration on source code level
* Minimal error handling
* Using fake interfaces with setters and getters instead of real ones.
