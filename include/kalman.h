#ifndef kalman_filter
#define  kalman_filter

typedef struct
{
    float time_step;
    float init_pos_std;
    float init_vel_std;
    float init_position;
    float init_velocity;
    float acceleration_std;
    float measurement_std;
} kalman_parameters;

typedef struct 
{
    float x[2];
    float p[2][2];
    float F[2][2];
    float Q[2][2];
    float H[2];
    float r;
} kalman_state;

void initialization (kalman_state *state, kalman_parameters para);
void prediction_step(kalman_state *state);
void update_step(kalman_state *state, float measurement);

#endif