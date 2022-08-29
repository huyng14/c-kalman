#include <stddef.h>

#include "../include/kalman.h"

void initialization (kalman_state *state, kalman_parameters para)
{
    // Initial velocity
    state->x = para.init_velocity;

    // Initial covariance
    state->p = para.init_vel_std*para.init_vel_std;

    state->F = 1;

    state->Q = para.acceleration_std*para.acceleration_std * para.time_step;

    state->H = 1;

    state->r = para.measurement_std*para.measurement_std;
}

void prediction_step(kalman_state *state)
{
    if(state != NULL)
    {
        // Predicted State (predicted velocity)
        state->x = state->F * state->x;

        // Predicted covariance 
        state->p = state->F * state->F * state->p + state->Q;
    }
}

void update_step(kalman_state *state, float measurement)
{
    if (state->x != -1.0)
    {
        // Get z measurement
        float z = measurement;

        // Predicted measurement
        // float z_hat = H*x;
        float z_hat = state->H * state->x;

        // Innovation (error function between Measurement(z) and predicted measurement(z_hat))
        float y = z - z_hat;

        // Kalman gain
        float K;
        K = state->p * state->H / (state->p * state->H * state->H + state->r);


        // State Update
        state->x = state->x + K * y;

        // Covariance Update
        state->p = (1 - K * state->H) * state->p;
    }
    else {
        state->x = measurement;
    }
}