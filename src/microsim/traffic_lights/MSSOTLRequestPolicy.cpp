/****************************************************************************/
/// @file    MSSOTLRequestPolicy.cpp
/// @author  Gianfilippo Slager
/// @author  Anna Chiara Bellini
/// @date    Apr 2013
/// @version $Id: MSSOTLRequestPolicy.cpp 19604 2015-12-13 20:49:24Z behrisch $
///
// The class for SOTL Request logics
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright 2001-2009 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/

#include "MSSOTLRequestPolicy.h"

MSSOTLRequestPolicy::MSSOTLRequestPolicy(
    const std::map<std::string, std::string>& parameters) :
    MSSOTLPolicy("Request", parameters) {
}

MSSOTLRequestPolicy::MSSOTLRequestPolicy(
    MSSOTLPolicyDesirability* desirabilityAlgorithm) :
    MSSOTLPolicy("Request", desirabilityAlgorithm) {
    getDesirabilityAlgorithm()->setKeyPrefix("REQUEST");
}

MSSOTLRequestPolicy::MSSOTLRequestPolicy(
    MSSOTLPolicyDesirability* desirabilityAlgorithm,
    const std::map<std::string, std::string>& parameters) :
    MSSOTLPolicy("Request", desirabilityAlgorithm, parameters) {
    getDesirabilityAlgorithm()->setKeyPrefix("REQUEST");

}

bool MSSOTLRequestPolicy::canRelease(int elapsed, bool thresholdPassed,  bool pushButtonPressed,
                                     const MSPhaseDefinition* stage, int vehicleCount) {
    if (elapsed >= getMinDecisionalPhaseDuration()) {
        return thresholdPassed;
    }
    return false;
}