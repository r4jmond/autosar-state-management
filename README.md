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

## Cppcheck configuration
For Cppcheck CLion integration:
1. Install [Cppcheck](https://cppcheck.sourceforge.io/)
2. Install [Cppcheck CLion plugin](https://plugins.jetbrains.com/plugin/8143-cppcheck)
3. In CLion go to settings -> Cppcheck Configuration. Set valid Cppcheck path and add those options:

`--language=c++ --std=c++14 --enable=all --addon=cert.py`

For use without CLion, just [Install Cppcheck](https://cppcheck.sourceforge.io/) and run it with flags from above.

## Differences against full implementation

* Completely static configuration on source code level
* Minimal error handling
