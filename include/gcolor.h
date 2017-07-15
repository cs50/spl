#ifndef _color_h
#define _color_h
#include <stdbool.h>
#include <stdint.h>

typedef union {
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
} GColor;

#define WHITE       ((GColor) {.full = 0xFFFFFFFFu})
#define BLACK       ((GColor) {.full = 0x000000FFu})
#define RED         ((GColor) {.full = 0xFF0000FFu})
#define BLUE        ((GColor) {.full = 0x0000FFFFu})
#define CYAN        ((GColor) {.full = 0x00FFFFFFu})
#define GRAY        ((GColor) {.full = 0x808080FFu})
#define LIGHT_GRAY  ((GColor) {.full = 0xD3D3D3FFu})
#define DARK_GRAY   ((GColor) {.full = 0x696969FFu})
#define GREEN       ((GColor) {.full = 0x00FF00FFu})
#define MAGENTA     ((GColor) {.full = 0xFF00FFFFu})
#define ORANGE      ((GColor) {.full = 0xFFA500FFu})
#define PINK        ((GColor) {.full = 0xFF1493FFu})
#define YELLOW      ((GColor) {.full = 0xFFFF00FFu})

#endif
