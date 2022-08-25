#include <stdio.h>
#include <stdlib.h>

#include "../include/kalman.h"

int main(){
    kalman_parameters init_parameter;
    init_parameter.time_step = 0.01;
    init_parameter.init_pos_std = 0.0;
    init_parameter.init_vel_std = 0.0;
    init_parameter.init_position = 0.0;
    init_parameter.init_velocity = -1.0;
    init_parameter.acceleration_std = 0.0015;
    init_parameter.measurement_std = 0.75;

    kalman_state state;

    initialization(&state, init_parameter);

    FILE *file = fopen("../dataset/wheel1_15k-25k.txt","r");
    FILE *fposition = fopen("../results/result_position.txt","w+");
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
        // printf("x[1] = %f\n", state.x[1]);
        fprintf(fposition, "%f\n",state.x[0]);
        fprintf(fvelocity, "%f\n",state.x[1]);
    }

    fclose(file);
    fclose(fposition);
    fclose(fvelocity);

    return 0;
}