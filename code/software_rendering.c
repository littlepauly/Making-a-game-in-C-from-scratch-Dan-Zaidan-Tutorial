/*
SOFTWARE RENDERING
*/

// function to clear the screen and set to a uniform colour
internal void
clear_screen(u32 colour) {
    u32 *pixel = render_buffer.pixels;
    
    for (int y = 0; y < render_buffer.height; y++) {
        for (int x = 0; x < render_buffer.width; x++) {
            *pixel++ = colour;
            
        }
    }
}

// function to draw an arb. sized rectangle in pixels
internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 colour) {
    
    x0 = clamp(0, x0, render_buffer.width);
    y0 = clamp(0, y0, render_buffer.height);
    
    x1 = clamp(0, x1, render_buffer.width);
    y1 = clamp(0, y1, render_buffer.height);
    
    for (int y = y0; y < y1; y++) {
        u32 *pixel = render_buffer.pixels + x0 + render_buffer.width*y;
        for (int x = x0; x < x1; x++) {
            *pixel++ = colour;
        }
    }
    
}


// Convert game space units to pixel space and call draw_rect_in_pixels
// Scale the game such that it preserves the aspect ratio. If thinner than 16:9 scale to the width. If wider than 16:9 scale to the height.

inline f32
calculate_aspect_multiplier(){
    
    f32 aspect_corrector = (f32)render_buffer.height * 1.777778f;
    if ((f32)render_buffer.width / (f32)render_buffer.height < 1.777778f) {
        aspect_corrector = (f32)render_buffer.width;
    }
    return aspect_corrector;
}

internal v2
pixels_to_world(v2i pixels_coord) {
    // convert from percent to fraction
    f32 scale = 0.01f;
    
    f32 aspect_corrector = calculate_aspect_multiplier();
    
    v2 result;
    result.x = (f32)pixels_coord.x  - (f32)render_buffer.width * .5f;
    result.y = (f32)pixels_coord.y  - (f32)render_buffer.height * .5f;
    
    result.x /= aspect_corrector*scale;
    result.y /= aspect_corrector*scale;
    
    return result;
}

//Replace pixels_to_world with pixels to percent
internal v2
pixels_to_percent(v2i pixels_coord) {
    f32 scale = 0.01f;
    v2 out;
    
    out = conv_v2i(pixels_coord);
    out.x /=  (f32)render_buffer.width * scale;
    out.y /= (f32)render_buffer.height * scale;
    
    out.x -= 50;
    
    return out;
}


// Create a rectangle scaled to the game space. Takes values in percent and returns a rect in pixels
internal void
draw_rect(v2 p, v2 half_size, u32 colour) {
    // convert from percent to fraction
    f32 scale = 0.01f;
    
    //@Cleanup only needs to be rescaled when window size changes
    f32 aspect_corrector = calculate_aspect_multiplier();
    
    // convert percent t0 fraction
    half_size = scale_v2(half_size, scale);
    p = scale_v2(p, scale);
    
    // get the width and height
    f32 width = render_buffer.width;
    f32 height = render_buffer.height;
    
    // convert from fraction to screen pixels using horizontal
    p.x *= width;
    p.y *= height;
    
    // aspect ratio does weird stuff: half_size = scale_v2(half_size, aspect_corrector * 0.5f);
    
    half_size.x *= width;
    half_size.y *= height;
    
    // offset p for (0,0) position
    p = sum_v2(p, (v2){width * 0.5f, height * 0.5f});
    
    
    int x0 = (int)(p.x-half_size.x);
    int y0 = (int)(p.y-half_size.y);
    int x1 = (int)(p.x+half_size.x);
    int y1 = (int)(p.y+half_size.y);
    
    draw_rect_in_pixels(x0, y0, x1, y1, colour);
    
}

