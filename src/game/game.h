#ifndef _GAME_H_
#define _GAME_H_

#include "core/types.h"

struct game_state;

struct game_api
{
    // Returns a fresh game state
    struct game_state *(*init)();

    // Destroys a game state
    void (*finalize)(struct game_state *state);

    // Called exactly once when the game code is loaded (or reloaded)
    void (*load)(struct game_state *state);

    // Called exactly once when the game code is about to be unloaded
    void (*unload)(struct game_state *state);

    // Called at a regular interval by the main program
    // Returns true if the program should continue running
    bool (*step)(struct game_state *state);
};

extern const struct game_api GAME_API;

#endif
