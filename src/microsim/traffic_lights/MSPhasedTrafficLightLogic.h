/****************************************************************************/
/// @file    MSPhasedTrafficLightLogic.h
/// @author  Daniel Krajzewicz
/// @date    Sept 2002
/// @version $Id: MSPhasedTrafficLightLogic.h 22627 2017-01-18 12:56:36Z behrisch $
///
// The base class for traffic light logic with phases
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2010-2017 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef MSPhasedTrafficLightLogic_h
#define MSPhasedTrafficLightLogic_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <utility>
#include <vector>
#include <bitset>
#include <microsim/MSEventControl.h>
#include <microsim/MSNet.h>
#include "MSTrafficLightLogic.h"
#include "MSPhaseDefinition.h"


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class MSPhasedTrafficLightLogic
 * @brief A fixed traffic light logic
 *
 * The base class for a traffic light which switches between
 * it's phases and sets the lights to red in between.
 * Some functions are called with an information about the current step. This
 * is needed as a single logic may be used by many junctions and so the current
 * step is stored within them, not within methods.
 */
class MSPhasedTrafficLightLogic : public MSTrafficLightLogic {
public:
    /** @brief Constructor
     * @param[in] tlcontrol The tls control responsible for this tls
     * @param[in] id This tls' id
     * @param[in] subid This tls' sub-id (program id)
     * @param[in] phases Definitions of the phases
     * @param[in] step The initial phase index
     * @param[in] delay The time to wait before the first switch
     */
    MSPhasedTrafficLightLogic(MSTLLogicControl& tlcontrol,
                              const std::string& id, const std::string& subid,
                              const Phases& phases, int step, SUMOTime delay,
                              const std::map<std::string, std::string>& parameters);


    /// @brief Destructor
    ~MSPhasedTrafficLightLogic();



    /// @name Switching and setting current rows
    /// @{
    /// MEMBER FACTORIZED TO PARENT CLASS (MSTrafficLightLogic)
    /** @brief Switches to the next phase
     * @param[in] isActive Whether this program is the currently used one
     * @return The time of the next switch
     * @see MSTrafficLightLogic::trySwitch
     */
    /* SUMOTime trySwitch(bool isActive) throw();*/



    /// @name Static Information Retrieval
    /// @{

    /** @brief Returns the number of phases
     * @return The number of this tls program's phases
     * @see MSTrafficLightLogic::getPhaseNumber
     */
    int getPhaseNumber() const;


    /** @brief Returns the phases of this tls program
     * @return The phases of this tls program
     * @see MSTrafficLightLogic::getPhases
     */
    const Phases& getPhases() const;

    /** @brief Returns the definition of the phase from the given position within the plan
     * @param[in] givenstep The index of the phase within the plan
     * @return The definition of the phase at the given position
     * @see MSTrafficLightLogic::getPhase
     */
    const MSPhaseDefinition& getPhase(int givenstep) const;
    /// @}



    /// @name Dynamic Information Retrieval
    /// @{

    /** @brief Returns the current index within the program
     * @return The index of the current phase within the tls
     * @see MSTrafficLightLogic::getCurrentPhaseIndex
     */
    int getCurrentPhaseIndex() const;


    /** @brief Returns the definition of the current phase
     * @return The current phase
     * @see MSTrafficLightLogic::getCurrentPhaseDef
     */
    const MSPhaseDefinition& getCurrentPhaseDef() const;
    /// @}



    /// @name Conversion between time and phase
    /// @{

    /** @brief Returns the index of the logic at the given simulation step
     * @return The (estimated) index of the tls at the given simulation time step
     * @see MSTrafficLightLogic::getPhaseIndexAtTime
     */
    SUMOTime getPhaseIndexAtTime(SUMOTime simStep) const;


    /** @brief Returns the position (start of a phase during a cycle) from of a given step
     * @param[in] index The index of the phase to return the begin of
     * @return The begin time of the phase
     * @see MSTrafficLightLogic::getOffsetFromIndex
     */
    SUMOTime getOffsetFromIndex(int index) const;


    /** @brief Returns the step (the phasenumber) of a given position of the cycle
     * @param[in] offset The offset (time) for which the according phase shall be returned
     * @return The according phase
     * @see MSTrafficLightLogic::getIndexFromOffset
     */
    int getIndexFromOffset(SUMOTime offset) const;
    /// @}



    /// @name Changing phases and phase durations
    /// @{

    /** @brief Changes the current phase and her duration
     * @param[in] tlcontrol The responsible traffic lights control
     * @param[in] simStep The current simulation step
     * @param[in] step Index of the phase to use
     * @param[in] stepDuration The left duration of the phase
     * @see MSTrafficLightLogic::changeStepAndDuration
     */
    void changeStepAndDuration(MSTLLogicControl& tlcontrol, SUMOTime simStep,
                               int step, SUMOTime stepDuration);
    /// @}

    /** @brief Replaces the phases and set the phase index
     */
    void setPhases(const Phases& phases, int index);
    /// @}

protected:
    /// @brief The list of phases this logic uses
    Phases myPhases;

    /// @brief Proceed to the next step
    void proceedToNextStep();

    /// @brief Forces a specific step
    void setStep(int step);

private:

    /// @brief frees memory responsibilities
    void deletePhases();

protected:

    /// @brief The current step
    int myStep;



};


#endif

/****************************************************************************/

