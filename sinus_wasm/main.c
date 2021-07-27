#include <stdio.h>
#include <SDL.h>
#include <math.h>
#include <emscripten.h>

void game();
void initUI(SDL_Renderer *renderer);

int HEIGHT = 800;
int WIDTH = 1200;
int quit = 0;
int amplitude = 400;
int frequency = 200;
int yCalc = 0, oldX = 0, oldY = 0;
double offset = 0;
int mouseX = 0, mouseY = 0;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_Event event;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	SDL_SetWindowResizable(window, SDL_TRUE);
	initUI(renderer);

	emscripten_set_main_loop(game, 0, 1);
	// emscripten_request_animation_frame_loop(game, 0);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void initUI(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 225, 0, 255);
	SDL_RenderDrawLine(renderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);
	SDL_RenderDrawLine(renderer, WIDTH / 2, 0, WIDTH / 2, HEIGHT);
}

void game()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			SDL_GL_GetDrawableSize(window, &WIDTH, &HEIGHT);
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
			frequency -= 50;
		else
			frequency += 50;
	case SDL_MOUSEWHEEL:
		if (event.wheel.y < 0)
			frequency -= 5;
		else if (event.wheel.y > 0)
			frequency += 5;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 200, 0, 50, 255);
		for (int i = 0; i < WIDTH; i++)
		{
			amplitude = -((HEIGHT / 2) - mouseY);
			offset = ((double)-mouseX * 2 * M_PI / frequency);
			yCalc = HEIGHT / 2 - (int)(amplitude * sin((2 * M_PI / frequency * i) + offset));
			if (i != 0) // on the first x location, you cant draw a line to the previous one
				SDL_RenderDrawLine(renderer, oldX, oldY, i, yCalc);
			oldX = i;
			oldY = yCalc;
		}
		initUI(renderer);
		SDL_RenderPresent(renderer);
		break;
	case SDL_QUIT:
		quit = 1;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			quit = 1;
			break;
		}
	}
}