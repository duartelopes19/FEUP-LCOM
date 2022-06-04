#include <lcom/lcf.h>

#include "rectangle.h"


rectangle_t* (rectangle_ctor)(int16_t x, int16_t y, uint16_t w, uint16_t h){
    rectangle_t *ret = (rectangle_t*)malloc(sizeof(rectangle_t));
    if(ret == NULL) return NULL;
    ret->x = x;
    ret->y = y;
    ret->w = w;
    ret->h = h;
    ret->color = 0x00ff0000;
    return ret;
}
void (rectangle_dtor)(rectangle_t *rectangle){
    free(rectangle);
}

void (rectangle_set_pos)          (rectangle_t *p,  int16_t x,  int16_t y){ p->x = x; p->y = y; }
void (rectangle_set_size)         (rectangle_t *p, uint16_t w, uint16_t h){ p->w = w; p->h = h; }
void (rectangle_set_color)        (rectangle_t *p, uint32_t color        ){ p->color = color; }

int16_t  (rectangle_get_x)(const rectangle_t *p){ return p->x; }
int16_t  (rectangle_get_y)(const rectangle_t *p){ return p->y; }
uint16_t (rectangle_get_w)(const rectangle_t *p){ return p->w; }
uint16_t (rectangle_get_h)(const rectangle_t *p){ return p->h; }

int (rectangle_collide_point)(const rectangle_t *p, int x, int y) {
    return (x >= p->x && x <= p->x + p->w) && (y >= p->y && y <= p->y + p->h);
}

/* static void (rectangle_draw_hline)(int16_t x, int16_t y, int16_t l, uint32_t color){
    if(l < 0){ rectangle_draw_hline(x+l, y, -l, color); return; }
    for(int16_t x_ = max_16(0,x); x_ < min_16(x+l,(int16_t)graph_get_XRes()); ++x_){
        graph_set_pixel((uint16_t)x_, (uint16_t)y, color);
    }
}
static void (rectangle_draw_vline)(int16_t x, int16_t y, int16_t l, uint32_t color){
    if(l < 0){ rectangle_draw_vline(x, y+l, -l, color); return; }
    for(int16_t y_ = max_16(0,y); y_ < min_16(y+l,(int16_t)graph_get_YRes()); ++y_){
        graph_set_pixel((uint16_t)x, (uint16_t)y_, color);
    }
} */

void (rectangle_draw)(rectangle_t *p){
    vg_draw_rectangle(p->x, p->y, p->w, p->h, p->color);
}