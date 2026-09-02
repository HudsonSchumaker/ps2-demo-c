/**
 * @file math2d.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_MATH2D_H
#define DE_MATH2D_H

#include "../de.h"
#include "../core/types.h"

#define SIN_LUT_SIZE 2048
#define ANGLE_MASK (SIN_LUT_SIZE - 1)
#define TABLE_SCALE (SIN_LUT_SIZE / 360.0f)

//----------------------------------------------------------------
// Lookup tables for trigonometric functions
//----------------------------------------------------------------

/**
 * @brief Builds the sine, cosine, and arctangent lookup tables. This function should be called once during initialization.
*/
void build_trigo_tables(void);

/**
 * @brief Converts degrees to the corresponding index in the lookup table.
 * @param degrees The angle in degrees
 * @return The corresponding index in the range [0, 1024) where 1024 represents 360 degrees
*/
int degrees_to_index(float degrees);

/**
 * @brief Approximates the sine of an angle using a lookup table.
 * @param angle The input angle in the range [0, 1024) where 1024 represents 360 degrees
 * @return Approximation of the sine of the angle
*/    
float de_sinf(int angle);

/**
 * @brief Approximates the cosine of an angle using a lookup table.
 * @param angle The input angle in the range [0, 1024) where 1024 represents 360 degrees
 * @return Approximation of the cosine of the angle
*/
float de_cosf(int angle);

/**
 * @brief Approximates the tangent of an angle using a lookup table.
 * @param angle The input angle in the range [0, 1024) where 1024 represents 360 degrees
 * @return Approximation of the tangent of the angle
*/
float de_tanf(int angle);

//----------------------------------------------------------------
// Square root and inverse fast square root
//----------------------------------------------------------------

/**
 * @brief Fast inverse square root approximation.
 * @param number The input number
 * @return Approximation of 1/sqrt(number)
*/
static inline float rsqrtf(float number) {
    union {
        float f;
        int i;
    } conv;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5f;
    conv.f = number;

    conv.i = 0x5f3759df - (conv.i >> 1);
    y = conv.f;

    y = y * (threehalfs - (x2 * y * y));
    return y;
}

/**
 * @brief Fast square root approximation using the inverse square root.
 * @param number The input number
 * @return Approximation of sqrt(number)
*/
static inline float fsqrtf(float number) {
    return number * rsqrtf(number);
}

//----------------------------------------------------------------
// Vector2D struct and functions
//----------------------------------------------------------------

/**
 * @brief Creates a new 2D vector with the specified x and y components.
 * @param x The X component of the vector
 * @param y The Y component of the vector
 * @return A vec2_t struct with the specified components
*/
static inline vec2_t vec2_create(float x, float y) {
    vec2_t v;
    v.x = x;
    v.y = y;
    return v;
}

/**
 * @brief Returns a zero vector.
 * @return A vector with x = 0 and y = 0
*/
static inline vec2_t vec2_zero(void) {
    return vec2_create(0.0f, 0.0f);
}

/**
 * @brief Returns a vector pointing to the left.
 * @return A vector with x = -1 and y = 0
*/
static inline vec2_t vec2_left(void) {
    return vec2_create(-1.0f, 0.0f);
}

/**
 * @brief Returns a vector pointing to the right.
 * @return A vector with x = 1 and y = 0
*/
static inline vec2_t vec2_right(void) {
    return vec2_create(1.0f, 0.0f);
}

/**
 * @brief Returns a vector pointing upwards.
 * @return A vector with x = 0 and y = -1
*/
static inline vec2_t vec2_up(void) {
    return vec2_create(0.0f, -1.0f);
}

/**
 * @brief Returns a vector pointing downwards.
 * @return A vector with x = 0 and y = 1
*/
static inline vec2_t vec2_down(void) {
    return vec2_create(0.0f, 1.0f);
}

/**
 * @brief Adds two vectors a and b.
 * @param a First vector
 * @param b Second vector
 * @return The resulting vector after addition
*/
static inline vec2_t vec2_add(vec2_t a, vec2_t b) {
    vec2_t r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    return r;
}

/**
 * @brief Subtracts vector b from vector a.
 * @param a First vector
 * @param b Second vector to subtract from the first
 * @return The resulting vector after subtraction
 */
static inline vec2_t vec2_sub(vec2_t a, vec2_t b) {
    vec2_t r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

/**
 * @brief Multiplies a vector v by a scalar s.
 * @param v The input vector
 * @param s The scalar value
 * @return The resulting vector after multiplication
*/
static inline vec2_t vec2_mul(vec2_t v, f32 s) {
    vec2_t r;
    r.x = v.x * s;
    r.y = v.y * s;
    return r;
}

/**
 * @brief Calculates the dot product of two vectors a and b.
 * @param a First vector
 * @param b Second vector
 * @return The dot product of the two vectors
*/
static inline float vec2_dot(vec2_t a, vec2_t b) {
    return (a.x * b.x) + (a.y * b.y);
}

/**
 * @brief Calculates the squared length of a vector v.
 * @param v The input vector
 * @return The squared length of the vector
*/
static inline float vec2_length_sq(vec2_t v) {
    return vec2_dot(v, v);
}

/**
 * @brief Calculates the length of a vector v using a fast approximation.
 * @param v The input vector
 * @return Approximation of the length of the vector
*/
static inline float vec2_length(vec2_t v) {
    float len_sq = vec2_length_sq(v);
    if (len_sq <= 0.0f) {
        return 0.0f;
    }

    return len_sq * rsqrtf(len_sq);
}

/**
 * @brief Normalizes a vector v using a fast approximation.
 * @param v The input vector
 * @return Approximation of the normalized vector
*/
static inline vec2_t vec2_normalize(vec2_t v) {
    float len_sq = vec2_length_sq(v);
    if (len_sq < EPSILON_F) {
        return vec2_zero();
    }

    float inv_len = rsqrtf(len_sq);
    vec2_t r;
    r.x = v.x * inv_len;
    r.y = v.y * inv_len;

    return r;
}

/**
 * @brief Rotates a vector v by a given angle using the sine and cosine lookup tables.
 * @param v The input vector
 * @param angle The angle to rotate by in the range [0, 1024) where 1024 represents 360 degrees
 * @return The rotated vector
*/
static inline vec2_t vec2_rotate(vec2_t v, int angle) {
    float s = de_sinf(angle); 
    float c = de_cosf(angle);

    vec2_t r;
    r.x = (v.x * c) - (v.y * s);
    r.y = (v.x * s) + (v.y * c);

    return r;
}

/**
 * @brief Moves a position forward in the direction of a given angle by a specified speed.
 * @param position The current position
 * @param angle The direction to move in the range [0, 1024) where 1024 represents 360 degrees
 * @param speed The distance to move
 * @return The new position after moving forward
*/
static inline vec2_t vec2_move_forward(vec2_t position, int angle, float speed) {
    position.x += de_cosf(angle) * speed;
    position.y += de_sinf(angle) * speed;

    return position;
}

//----------------------------------------------------------------
// Math utility functions
//----------------------------------------------------------------

/**
 * @brief Returns the minimum of two floating-point values.
 * @param a First value
 * @param b Second value
 * @return The minimum value
*/
static inline float minf(float a, float b) {
    return (a < b) ? a : b;
}

/**
 * @brief Returns the maximum of two floating-point values.
 * @param a First value
 * @param b Second value
 * @return The maximum value
*/
static inline float maxf(float a, float b) {
    return (a > b) ? a : b;
}

/**
 * @brief Clamps a floating-point value between a minimum and maximum range.
 * @param v The value to clamp
 * @param min The minimum value
 * @param max The maximum value
 * @return The clamped value
*/
static inline float clampf(float v, float min, float max) {
    return minf(maxf(v, min), max);
}

/**
 * @brief Returns the absolute value of a floating-point number.
 * @param v The input value
 * @return The absolute value of the input
*/
static inline float absf(float v) {
    return (v < 0.0f) ? -v : v;
}

/**
 * @brief Returns a random floating-point number between min and max.
 * @param min The minimum value
 * @param max The maximum value
 * @return A random floating-point number in the range [min, max]
*/
static inline float randf(float min, float max) {
    return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}

/**
 * @brief Calculates the distance between two points (x1, y1) and (x2, y2) using a fast approximation.
 * @param x1 First point X coordinate
 * @param y1 First point Y coordinate
 * @param x2 Second point X coordinate
 * @param y2 Second point Y coordinate
 * @return Approximation of the distance between the two points
*/
static inline float distance_pointsf(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float dist_sq = dx * dx + dy * dy;
    float inv = rsqrtf(dist_sq);
    return dist_sq * inv;
}

/**
 * @brief Calculates the squared distance between two points (x1, y1) and (x2, y2).
 * @param x1 First point X coordinate
 * @param y1 First point Y coordinate
 * @param x2 Second point X coordinate
 * @param y2 Second point Y coordinate
 * @return Squared distance between the two points
*/
static inline float distance_points_sqf(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return dx * dx + dy * dy;
}

/**
 * @brief Calculates the squared distance between two vectors a and b.
 * @param a First vector
 * @param b Second vector
 * @return Squared distance between the two vectors
*/
static inline float vec2_distance_sq(vec2_t a, vec2_t b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return dx * dx + dy * dy;
}

/**
 * @brief Calculates the distance between two vectors a and b using a fast approximation.
 * @param a First vector
 * @param b Second vector
 * @return Approximation of the distance between the two vectors
*/
static inline float vec2_distance(vec2_t a, vec2_t b) {
    return fsqrtf(vec2_distance_sq(a, b));
}

/**
 * @brief Calculates the angle in radians between two points (x1, y1) and (x2, y2).
 * @param x1 First point X coordinate
 * @param y1 First point Y coordinate
 * @param x2 Second point X coordinate
 * @param y2 Second point Y coordinate
 * @return The angle in radians between the two points
*/
static inline float angle_between_pointsf(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return atan2f(dy, dx);
}

static inline float angle_between_direction(float dx, float dy) {
    return atan2f(dy, dx);
}

//----------------------------------------------------------------
// Angle utilities
//----------------------------------------------------------------

/**
 * @brief Wraps an angle to the range [0, 1024) where 1024 represents 360 degrees.
 * @param angle The input angle
 * @return The wrapped angle in the range [0, 1024)
*/
static inline int wrap_angle(int angle) {
    return angle & ANGLE_MASK;
}

/**
 * @brief Converts degrees to radians.
 * @param deg The angle in degrees
 * @return The angle in radians
*/
static inline float deg2rad(float deg) {
    return deg * DEG_2_RAD_F;
}

/**
 * @brief Converts radians to degrees.
 * @param rad The angle in radians
 * @return The angle in degrees
*/
static inline float rad2deg(float rad) {
    return rad * RAD_2_DEG_F;
}

#endif /* DE_MATH2D_H */
