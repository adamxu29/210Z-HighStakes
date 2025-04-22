#include "main.h"
#include "pros/distance.hpp"
#include "pros/imu.hpp"
#include <vector>
#include <random>
#include <cmath>

#define NUM_PARTICLES 500
#define FIELD_SIZE_IN 144
#define LADDER_CENTER_X 72
#define LADDER_CENTER_Y 72
#define LADDER_MIN_X 60
#define LADDER_MAX_X 84
#define LADDER_MIN_Y 60
#define LADDER_MAX_Y 84
#define SENSOR_REFRESH_INTERVAL 1
#define MCL_UPDATE_INTERVAL 1
#define SENSOR_JUMP_THRESHOLD 10

std::vector<Particle> particles(NUM_PARTICLES);
std::random_device rd;
std::mt19937 gen(rd());

std::uniform_real_distribution<double> rand_x(-6, 6);
std::uniform_real_distribution<double> rand_y(-6, 6);
std::uniform_real_distribution<double> rand_theta(-5, 5);
std::normal_distribution<double> noise_x(0, 0.2);
std::normal_distribution<double> noise_y(0, 0.2);
std::normal_distribution<double> noise_theta(0, 1.5);

uint32_t last_update_time = 0;
uint32_t last_sensor_refresh = 0;

double last_front, last_back, last_left, last_right;
double cached_front, cached_back, cached_left, cached_right;

double clamp_sensor(double mm) {
    return std::min(mm / 25.4, (double)FIELD_SIZE_IN);
}

bool in_ladder(double x, double y) {
    return x >= LADDER_MIN_X && x <= LADDER_MAX_X &&
           y >= LADDER_MIN_Y && y <= LADDER_MAX_Y;
}

bool ray_hits_ladder_from_sensor(double heading_deg, double sensor_offset_angle_deg, double distance_in) {
    double total_angle = heading_deg + sensor_offset_angle_deg;
    double rad = total_angle * M_PI / 180.0;

    double x = LADDER_CENTER_X + distance_in * cos(rad);
    double y = LADDER_CENTER_Y + distance_in * sin(rad);

    return in_ladder(x, y);
}

void initialize_particles() {
    for (auto& p : particles) {
        p.x = LADDER_CENTER_X + rand_x(gen);
        p.y = LADDER_CENTER_Y + rand_y(gen);
        p.theta = rand_theta(gen);
        p.weight = 1.0 / NUM_PARTICLES;
    }

    last_front = clamp_sensor(front_sensor.get());
    last_back  = clamp_sensor(back_sensor.get());
    last_left  = clamp_sensor(left_sensor.get());
    last_right = clamp_sensor(right_sensor.get());

    cached_front = last_front;
    cached_back  = last_back;
    cached_left  = last_left;
    cached_right = last_right;
}

void refresh_sensors() {
    double heading = util.get_heading();

    double f = clamp_sensor(front_sensor.get());
    if (!ray_hits_ladder_from_sensor(heading, 180, f) && fabs(f - last_front) < SENSOR_JUMP_THRESHOLD)
        cached_front = f;

    double b = clamp_sensor(back_sensor.get());
    if (!ray_hits_ladder_from_sensor(heading, 0, b) && fabs(b - last_back) < SENSOR_JUMP_THRESHOLD)
        cached_back = b;

    double l = clamp_sensor(left_sensor.get());
    if (!ray_hits_ladder_from_sensor(heading, 270, l) && fabs(l - last_left) < SENSOR_JUMP_THRESHOLD)
        cached_left = l;

    double r = clamp_sensor(right_sensor.get());
    if (!ray_hits_ladder_from_sensor(heading, 90, r) && fabs(r - last_right) < SENSOR_JUMP_THRESHOLD)
        cached_right = r;

    last_front = f;
    last_back = b;
    last_left = l;
    last_right = r;
}

void update_particles_from_heading() {
    double heading = util.get_heading();  // degrees
    double dx = (cached_right - cached_left) / 2.0;
    double dy = (cached_back - cached_front) / 2.0;

    double rad = heading * M_PI / 180.0;
    double rotated_x = dx * cos(rad) - dy * sin(rad);
    double rotated_y = dx * sin(rad) + dy * cos(rad);

    // Flip the Y-axis based on 90 and 270 degree turns
    if (fmod(heading, 360) == 90 || fmod(heading, 360) == 270) {
        rotated_y = -rotated_y;
    }

    // When rotating, don't update the X and Y unless moving forward/backward
    for (auto& p : particles) {
        if (fabs(dx) > 0.5 || fabs(dy) > 0.5) {
            p.x = LADDER_CENTER_X + rotated_x + noise_x(gen);
            p.y = LADDER_CENTER_Y + rotated_y + noise_y(gen);
        }

        p.theta = heading + noise_theta(gen);
        p.weight = in_ladder(p.x, p.y) ? 0.1 : 1.0;
    }

    // Normalize weights
    double total = 0;
    for (const auto& p : particles) total += p.weight;
    for (auto& p : particles) p.weight /= total;
}

Particle get_estimate() {
    double sx = 0, sy = 0, st = 0, tw = 0;
    for (const auto& p : particles) {
        sx += p.x * p.weight;
        sy += p.y * p.weight;
        st += p.theta * p.weight;
        tw += p.weight;
    }

    return {
        round((sx - LADDER_CENTER_X) * 10) / 10.0,
        round((sy - LADDER_CENTER_Y) * 10) / 10.0,
        round(st / tw),
        1.0
    };
}

void run_localization_step() {
    uint32_t now = pros::millis();
    if (now - last_sensor_refresh >= SENSOR_REFRESH_INTERVAL) {
        refresh_sensors();
        last_sensor_refresh = now;
    }

    if (now - last_update_time < MCL_UPDATE_INTERVAL) return;

    update_particles_from_heading();
    Particle est = get_estimate();

    pros::lcd::print(0, "X: %.1f in", est.x);
    pros::lcd::print(1, "Y: %.1f in", est.y);
    pros::lcd::print(2, "Heading: %.0f", est.theta);
    pros::lcd::print(3, "In Ladder: %s", in_ladder(est.x + LADDER_CENTER_X, est.y + LADDER_CENTER_Y) ? "Yes" : "No");

    last_update_time = now;
}
