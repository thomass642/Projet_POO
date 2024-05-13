#include "MAPfonction.h"

bool isClickInsideImage(int clickX, int clickY, int imageX, int imageY, int imageWidth, int imageHeight) {
    return (clickX >= imageX && clickX <= imageX + imageWidth && clickY >= imageY && clickY <= imageY + imageHeight);
}

void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int w = 0; w < 8; ++w) {
        int x = radius - 1 - w;
        int y = 0 + w;
        int tx = 1;
        int ty = 1;
        int error = tx - (radius << 1);

        while (x >= y) {
            SDL_RenderDrawPoint(renderer, centerX + x , centerY - y);
            SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
            SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
            SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

            if (error <= 0) {
                ++y;
                error += ty;
                ty += 2;
            }
            if (error > 0) {
                --x;
                tx += 2;
                error += tx - (radius << 1);
            }
        }
    }
}


