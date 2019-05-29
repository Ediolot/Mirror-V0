//
// Created by jsier on 02/05/2019.
//

#include "Colors.h"

Colors::Colors()
    : colors()
{}

bool Colors::load() {
    colors[EMPTY]         = al_map_rgba(0, 0, 0, 255);
    // BASIC
    colors[WHITE]         = al_map_rgb(255, 255, 255);
    colors[BLACK]         = al_map_rgb(  0,   0,   0);
    // YELLOWS
    colors[GOLDEN_YELLOW] = al_map_rgb(255, 222,   0);
    colors[KOURNIKOVA]    = al_map_rgb(251, 197,  88);
    colors[APACHE]        = al_map_rgb(213, 173,  78);
    colors[GOLDEN_TAINOI] = al_map_rgb(254, 201,  87);
    colors[ROB_ROY]       = al_map_rgb(215, 170,  77);
    // BLUES
    colors[CYAN]          = al_map_rgb(  0, 176, 246);
    colors[SUMMER_SKY]    = al_map_rgb( 40, 168, 223);
    colors[PELOROUS]      = al_map_rgb( 39, 146, 192);
    colors[BERMUDA]       = al_map_rgb(129, 206, 196);
    colors[TRADE_WIND]    = al_map_rgb(113, 174, 166);
    colors[JELLY_BEAN]    = al_map_rgb( 68, 121, 142);
    colors[VICKING]       = al_map_rgb( 55, 169, 206);
    // GRAYS
    colors[CASPER]        = al_map_rgb(185, 189, 192);
    colors[SPUN_PEARL]    = al_map_rgb(162, 162, 164);
    colors[GREY]          = al_map_rgb( 50,  50,  50);
    // RED
    colors[RUBY]          = al_map_rgb(223,  24,  91);
    colors[CARDINAL]      = al_map_rgb(184,  29,  81);
    // BROWN
    colors[FALLOW]        = al_map_rgb(196, 153, 108);
    colors[MEDIUM_WOOD]   = al_map_rgb(167, 132,  94);
    colors[PALE_TAUPE]    = al_map_rgb(184, 148, 111);

    return true;
}
