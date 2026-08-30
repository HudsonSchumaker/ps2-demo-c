/**
 * @file collision.h
 * @author Hudson Schumaker
 * @version 1.0.0
 *
 * Dodoi-Engine is a game engine developed by Dodoi-Lab.
 * @copyright Copyright (c) 2024, Dodoi-Lab
*/
#ifndef DE_COLLISION_H
#define DE_COLLISION_H

#include "../de.h"
#include "../math/math2d.h"

static inline bool point_in_rect(int px, int py, int rx, int ry, int rw, int rh) {
    return (
        px >= rx &&
        px <= rx + rw &&
        py >= ry &&
        py <= ry + rh
    );
}

static inline bool pointf_in_rectf(float px, float py, float rx, float ry, float rw, float rh) {
    return (
        px >= rx &&
        px <= rx + rw &&
        py >= ry &&
        py <= ry + rh
    );
}

static inline bool rect_intersects(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
    return !(
        ax + aw < bx ||
        ax > bx + bw ||
        ay + ah < by ||
        ay > by + bh
    );
}

/**
 * @brief Checks if two circles intersect.
 * @param a First circle center
 * @param ra First circle radius
 * @param b Second circle center
 * @param rb Second circle radius
 * @return true if the circles intersect, false otherwise
*/
static inline bool circle_intersects(vec2_t a, int ra, vec2_t b, int rb) {
    int rr = ra + rb;
    return vec2_distance_sq(a, b) <= (rr * rr);
}

#endif /* DE_COLLISION_H */
