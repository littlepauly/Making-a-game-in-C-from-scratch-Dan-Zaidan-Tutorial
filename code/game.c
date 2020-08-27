/*
GAME

Contains all of the code movement interactions etc.

*/

// ball position, velocity and size
v2 ball_p;
v2 ball_v;
v2 ball_half_size = {0.75, 0.75 * 1.777778f};

// player position, velocity size
v2 player_p;
v2 player_v;
v2 player_half_size = {5, 0.5 * 1.777778f};
v2 player_p_last;

b32 initialised = false;

internal void
simulate_game(Input *input, f32 dt, f32 cpu) {
    
    // start the ball
    if (!initialised) {
        initialised = true;
        ball_p = (v2){0, 0};
        ball_v.y = -30;
        f32 random = (f32)rand() / 32767 - 0.5; // should give rand b/w -0.5 and 0.5
        ball_v.x = 40 * random;
    }
    
    // get the player postion from the mouse input
    player_p = pixels_to_percent(input->mouse);
    // clamp player x position
    player_p.x = clampf(-50, player_p.x, 50);
    player_p.y = -40; // fix the y postion
    
    // get the player x velocity
    player_v.x = player_p.x - player_p_last.x;
    player_p_last.x = player_p.x;
    
    
    // vector addition and scaling
    ball_p = sum_v2(ball_p, scale_v2(ball_v, dt));
    
    // collision detection
    if (rect_aabb(player_p, player_half_size, ball_p, ball_half_size)) {
        ball_v.y *= -1;
        ball_v.x += 50*player_v.x;
        ball_p.y = player_p.y + player_half_size.y + ball_half_size.y;
    }
    
    //screen edge collision;
    ball_v = window_boundary_collision(ball_p, ball_half_size, ball_v);
    
    // lost ball
    if (ball_lost(ball_p.y)) {
        initialised = false;
    }
    
    //reset
    if (pressed(BUTTON_DOWN)) {
        initialised = false;
    }
    
    clear_screen(0x2474ff);
    draw_rect(ball_p,  ball_half_size, 0x00ffff);
    draw_rect(player_p, player_half_size, 0xffbc12);
    draw_rect((v2){-50,-50}, (v2){10,10}, 0x00df12);
    draw_rect((v2){50,-50}, (v2){10,10}, 0x00df12);
    draw_rect((v2){-50,50}, (v2){10,10}, 0x00df12);
    draw_rect((v2){50,50}, (v2){10,10}, 0x00df12);
}

/* Removing keyboard player

v2 player_p;
f32 speed = 100;

if(is_down(BUTTON_LEFT)) player_p.x -= speed*dt;
    if(is_down(BUTTON_RIGHT)) player_p.x += speed*dt;
    if(is_down(BUTTON_UP)) player_p.y += speed*dt;
    if(is_down(BUTTON_DOWN)) player_p.y -= speed*dt;
    
draw_rect(player_p, (v2){1, 1}, 0xffbc36);

*/