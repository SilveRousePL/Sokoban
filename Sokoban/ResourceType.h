#ifndef RESOURCETYPE_H_
#define RESOURCETYPE_H_

enum TEXTURE_ID
{
    NONE = 0,
    FLOOR = 1,
    FLOOR_TRIGGER = 2,
    WALL = 3,
    PLAYER_SPAWN = 4,
    PLAYER = 5,
    OBJECT = 6,
    OBJECT_GLOW = 7,
    UI_BACKGROUND = 8,
    BTN_BG = 9,
    BTN_ACTIVE = 10
};

#define MAP_ELEMENT TEXTURE_ID

#endif // RESOURCETYPE_H_
