#include <stdio.h>
#include <stdlib.h>

#include "../include/kalman.h"

int main(){
    kalman_parameters init_parameter;

    init_parameter.time_step = 0.01;        // Initial time step is Delta t
    init_parameter.init_vel_std = 0.0;      // Initial Velocity Standard Deviation
    init_parameter.init_velocity = -1.0;    // Initial velocity (-1.0 means NULL)
    init_parameter.acceleration_std = 0.0015; // Initial Acceleration Standard Deviation is sigma
    init_parameter.measurement_std = 0.75;  // Measurement standard deviation

    kalman_state state;

    initialization(&state, init_parameter);

    FILE *file = fopen("../dataset/wheel1.txt","r");
    FILE *fvelocity = fopen("../results/result_velocity.txt","w+");

    char chunk[128];

    if (file == NULL)
    {
        perror("Unable to open file!");
        return 0;
    }
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        float measurement = atof(chunk);
        prediction_step(&state);
        update_step(&state, measurement);
        fprintf(fvelocity, "%f\n",state.x);
    }

    fclose(file);
    fclose(fvelocity);

    return 0;
}