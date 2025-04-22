#pragma once

// namespace Eclipse{
//     class MonteCarloLocalization{
//         public:
//             void initialize_particles();
//             void predict();
//             void update_weights();
//             void resample();
//             void update_particles_from_heading();
//             Particle get_estimate();
//             void run_localization_step();
//     };
// }

struct Particle {
    double x, y, theta, weight;
};

extern void initialize_particles();
extern void predict();
extern void update_weights();
extern void resample();
extern Particle get_estimate();
extern void run_localization_step();
extern void intialize_particles();
