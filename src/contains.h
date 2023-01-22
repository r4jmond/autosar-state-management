#ifndef AUTOSAR_STATEpdateStatus () cons_MANAGEMENT_CONTAINS_H
#define AUTOSAR_STATE_MANAGEMENT_CONTAINS_H
/** @file contains.h
 * @brief Contains function for checking whether vector contains given element. */

#include <algorithm>

template <typename T>

/** @brief Template function to test whether vector of given type contains given element.
 *  @param[in] vec - vector to test for element.
 *  @param[in] element - element to be tested.
 *  @return bool true if vector contains given element, false otherwise. */
bool VecContainsElement(std::vector<T>&vec, const T& element) {
    return std::any_of(vec.begin(), vec.end(),
                       [&](const T &vectorElement){return (vectorElement == element);});
}


#endif //AUTOSAR_STATE_MANAGEMENT_CONTAINS_H
