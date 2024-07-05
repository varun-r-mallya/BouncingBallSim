#include <iostream>
#include<SDL2/SDL.h>  
 
float x = 0, y = 0;

float g = 0.008;
float velocity_y = 0;
float damper = 0.09;
float velocity_x = 0.3;

void moveBall(){
    if(x > 640)
    x = 0;
    if(y < 430)
    { 

        velocity_y += g;
        y = y + velocity_y;
        x = x + velocity_x;

    }
    else {
            if(velocity_y > 0)
            {
                velocity_y = (-(velocity_y - damper));
                y = y + velocity_y;
            }
        }
}



void DrawBall(SDL_Renderer* renderer, float x0, float y0, float radius) {
	float x = radius;
	float y = 0;
	float xChange = 1 - (radius * 2);
	float yChange = 0;
	int radiusError = 0;

	while (x >= y) {
		for (int i = x0 - x; i < x0 + x; i++) {
			SDL_RenderDrawPoint(renderer, i, y0 + y);
			SDL_RenderDrawPoint(renderer, i, y0 - y);
		}
		for (int i = x0 - y; i <= x0 + y; i++) {
			SDL_RenderDrawPoint(renderer, i, y0 + x);
			SDL_RenderDrawPoint(renderer, i, y0 - x);
		}
		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0) {
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
        
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
 
    while (!quit)
    {

        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            y -= 300;
            x = 320;
            velocity_y = 0;
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		DrawBall(renderer, x, y, 50);

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        moveBall();
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
 
    SDL_Quit();
 
    return 0;
}
