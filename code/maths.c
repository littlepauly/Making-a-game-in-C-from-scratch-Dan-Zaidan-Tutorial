/*
MATHS
*/


// clamp function to make sure objects are only draw in window space
internal int
clamp(int min,int  val,int  max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

internal f32
clampf(f32  min,f32  val,f32  max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}


// Vector 2 Struct

struct {
    union {
        struct {
            f32 x;
            f32 y;
        };
        
        f32 e[2];
    };
} typedef v2;

// Int V2
struct {
    union {
        struct {
            int x;
            int y;
        };
        
        int e[2];
    };
} typedef v2i;


// Define vector addition
inline v2
sum_v2(v2 a, v2 b) {
    return (v2){a.x + b.x, a.y + b.y};
}


// Define vector multiplication
inline f32
dot_prod_v2(v2 a, v2 b) {
    return (f32){a.x * b.x + a.y * b.y};
}

// Define scalar
inline v2
scale_v2(v2 a, f32 b) {
    return (v2){b*a.x, b*a.y};
}

// Convert a v2 int to float
inline v2
conv_v2i(v2i a) {
    return (v2){(f32)a.x, (f32)a.y};
}


