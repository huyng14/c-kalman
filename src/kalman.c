#include <stddef.h>

#include "../include/kalman.h"

void initialization (kalman_state *state, kalman_parameters para)
{
    state->x[0] = para.init_position;
    state->x[1] = para.init_velocity;

    state->p[0][0] = para.init_pos_std*para.init_pos_std;
    state->p[0][1] = 0;
    state->p[1][0] = 0;
    state->p[1][1] = para.init_vel_std*para.init_vel_std;

    state->F[0][0] = 1;
    state->F[0][1] = para.time_step;
    state->F[1][0] = 0;
    state->F[1][1] = 1;

    state->Q[0][0] = para.acceleration_std*para.acceleration_std * para.time_step*para.time_step *0.5;
    state->Q[0][1] = 0;
    state->Q[1][0] = 0;
    state->Q[1][1] = para.acceleration_std*para.acceleration_std * para.time_step;

    state->H[0] = 0;
    state->H[1] = 1;

    state->r = para.measurement_std*para.measurement_std;
}

void prediction_step(kalman_state *state)
{
    if(state != NULL)
    {
        state->x[0] = state->F[0][0] * state->x[0] + state->F[0][1] * state->x[1];
        state->x[1] = state->F[1][0] * state->x[0] + state->F[1][1] * state->x[1];

        state->p[0][0] = (state->F[0][0] * state->p[0][0]) * state->F[0][0] 
                        + (state->F[0][1] * state->p[1][1]) * state->F[0][1] 
                        + state->Q[0][0];
        state->p[0][1] = state->F[0][0] * state->p[0][0] * state->F[1][0]
                        + state->F[0][1] * state->p[1][1] * state->F[1][1]
                        + state->Q[0][1];
        state->p[1][0] = (state->F[1][1] * state->p[1][1]) * state->F[0][1]
                        + state->Q[1][0];
        state->p[1][1] = state->F[1][1] * state->p[1][1] * state->F[1][1]
                        + state->Q[1][1];
    }
}

void update_step(kalman_state *state, float measurement)
{
    if (state->x[1] != -1.0)
    {
        // Get z measurement
        float z = measurement;

        // Predicted measurement
        // float z_hat = state->x[1];
        float z_hat = state->H[0] * state->x[0] + state->H[1] * state->x[1];

        // Innovation (error function between Measurement(z) and predicted measurement(z_hat))
        float y = z - z_hat;

        // Kalman gain
        float K[2];
        float temp0 = 0.0f;
        float temp1 = 0.0f;
        float temp = 0.0f;
        temp0 = state->p[0][0] * state->H[0] + state->p[0][1] * state->H[1];
        temp1 = state->p[1][0] * state->H[0] + state->p[1][1] * state->H[1];
        temp  = state->r + state->H[0] * temp0 + state->H[1] * temp1;
        K[0] = temp0 / temp;
        K[1] = temp1 / temp;

        // State Update
        state->x[0] = state->x[0] + K[0] * y;
        state->x[1] = state->x[1] + K[1] * y;

        // Covariance Update
        state->p[0][0] = (1 - K[0] * state->H[0]) * state->p[0][0];
        state->p[0][1] = (1 - K[0] * state->H[1]) * state->p[0][1];
        state->p[1][0] = (1 - K[1] * state->H[0]) * state->p[1][0];
        state->p[1][1] = (1 - K[1] * state->H[1]) * state->p[1][1];
    }
    else {
        state->x[1] = measurement;
    }
}