#ifndef _color_h
#define _color_h
#include <stdbool.h>
#include <stdint.h>

typedef union Color {
    struct {
#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
#else
        uint8_t a;
        uint8_t b;
        uint8_t g;
        uint8_t r;
#endif
    };
    uint32_t full;
} Color;

#define WHITE       0xFFFFFFFF
#define BLACK       0x000000FF
#define RED         0xFF0000FF
#define BLUE        0x0000FFFF
#define CYAN        0x00FFFFFF
#define GRAY        0x808080FF
#define LIGHT_GRAY  0xD3D3D3FF
#define DARK_GRAY   0x696969FF
#define GREEN       0x00FF00FF
#define MAGENTA     0xFF00FFFF
#define ORANGE      0xFFA500FF
#define PINK        0xFF1493FF
#define YELLOW      0xFFFF00FF

bool mapStringColor(char const *str, Color *col);
const char *mapColorString(Color col);
#endif
