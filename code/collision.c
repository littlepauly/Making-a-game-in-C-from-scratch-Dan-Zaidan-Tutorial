/*
COLLISION
*/



inline b32
rect_aabb(v2 p1, v2 half_size1, v2 p2, v2 half_size2) {
    // corner ords 1
    f32 x11 = p1.x - half_size1.x;
    f32 x12 = p1.x + half_size1.x;
    f32 y11 = p1.y + half_size1.y;
    f32 y12 = p1.y - half_size1.y;
    
    // corner ords 2
    f32 x21 = p2.x - half_size2.x;
    f32 x22 = p2.x + half_size2.x;
    f32 y21 = p2.y + half_size2.y;
    f32 y22 = p2.y - half_size2.y;
    
    if (y22 < y11 &&  y21 > y12 && x21 < x12 && x22 > x11) {
        return true;
    } else {
        return false;
    }
    
}



inline v2
window_boundary_collision(v2 p, v2 half_size, v2 v) {
    
    // corner ords
    f32 x1 = p.x - half_size.x;
    f32 x2 = p.x + half_size.x;
    f32 y1 = p.y + half_size.y;
    
    if (y1 >= 50) {
        v.y *= -1;
    }
    
    if (x1 <= -50) {
        v.x *= -1;
    }
    if (x2 >= 50) {
        v.x *= -1;
    }
    
    return v;
}

inline b32
ball_lost(f32 y) {
    if (y < -50) {
        return true;
    } else {
        return false;
    }
    
}
