/*
    RB3Enhanced - GlobalSymbols.h
    Symbols that are constructed only once, directly after plugin initialization.
*/

#include "rb3/Symbol.h"

void InitGlobalSymbols();

typedef struct _GlobalSymbols
{
    // dta functions
    Symbol print_debug;
    Symbol rb3e_change_music_speed;
    Symbol rb3e_change_track_speed;
    Symbol rb3e_get_music_speed;
    Symbol rb3e_get_track_speed;
    Symbol rb3e_set_venue;
    Symbol rb3e_is_emulator;

    // modifiers
    Symbol forceHopos;
    Symbol colorShuffle;
    Symbol mirrorMode;
    Symbol blackBackground;

    // gem widgets
    Symbol greenGem;
    Symbol redGem;
    Symbol yellowGem;
    Symbol blueGem;
    Symbol orangeGem;

    // drum gem widgets
    Symbol redDrumGem;
    Symbol yellowDrumGem;
    Symbol blueDrumGem;
    Symbol greenDrumGem;

    // drum cymbal gem widgets
    Symbol redCymbalGem;
    Symbol yellowCymbalGem;
    Symbol blueCymbalGem;
    Symbol greenCymbalGem;

    // hopo widgets
    Symbol greenHopoGem;
    Symbol redHopoGem;
    Symbol yellowHopoGem;
    Symbol blueHopoGem;
    Symbol orangeHopoGem;

    // slot colors
    Symbol green;
    Symbol red;
    Symbol yellow;
    Symbol blue;
    Symbol orange;

} GlobalSymbols;

extern GlobalSymbols globalSymbols;