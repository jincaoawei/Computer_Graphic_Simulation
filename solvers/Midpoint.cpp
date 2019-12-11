//
// Created by Ruud Andriessen on 13/05/2017.
//

#include "Midpoint.h"

void Midpoint::simulateStep(System *system, float h) {

    // Get the initial state
    VectorXf oldState = system->getState();

    // Evaluate a deriv step
    VectorXf deriv = system->derivEval();

    // Compute the halfway point
    VectorXf midPointState = oldState + h * 0.5f * deriv;

    // Set the state to this midpoint
    system->setState(midPointState, system->getTime() + h);

    // Evaluate derivative at the midpoint
    deriv = system->derivEval();

    // Update the state based on the computation from this midpoint
    VectorXf newState = oldState + h * deriv;

    system->setState(newState, system->getTime() + h);
}
