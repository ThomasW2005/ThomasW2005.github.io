/*
Thomas Weichhart
11.06.2021
Mandelbrot Set
v3.3
*/

#include <SDL.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <string>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 400

SDL_Renderer *renderer;
SDL_Window *window;
SDL_Event event;
char title[300];
int run = 1;
int coloring = 2;
int max_iterations = 16;
//double middleX = -0.75;
//double middleY = 0;
double middleX = -1.71102468159729359520;
double middleY = -0.00451104455560013759;
double rangeX = 3.5;
double rangeY = 2;

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void decIterations()
#else
void decIterations()
#endif
    {
        int max_iterations_temp = 0;
        int max_iterations_temp2 = 0;
        max_iterations_temp = max_iterations * 0.9;
        if (max_iterations == max_iterations_temp)
            max_iterations--;
        else
            max_iterations = max_iterations_temp;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void incIterations()
#else
void incIterations()
#endif
    {
        int max_iterations_temp = 0;
        int max_iterations_temp2 = 0;
        max_iterations_temp2 = max_iterations / 0.9;
        if (max_iterations == max_iterations_temp2)
            max_iterations++;
        else
            max_iterations = max_iterations_temp2;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void changeColor()
#else
void changeColor()
#endif
    {
        coloring = coloring >= 2 ? 0 : coloring + 1;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void w()
#else
void w()
#endif
    {
        middleY -= 0.1 * rangeY;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void a()
#else
void a()
#endif
    {
        middleX -= 0.1 * rangeX;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void s()
#else
void s()
#endif
    {
        middleY += 0.1 * rangeY;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void d()
#else
void d()
#endif
    {
        middleX += 0.1 * rangeX;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void zoomPlus()
#else
void zoomPlus()
#endif
    {
        rangeX *= 0.8;
        rangeY *= 0.8;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE void zoomMinus()
#else
void zoomMinus()
#endif
    {
        rangeX /= 0.8;
        rangeY /= 0.8;
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_KEEPALIVE std::string getTitle()
#else
std::string getTitle()
#endif
    {
        char title[200] = {0};
        sprintf(title, "SPF: X s | %d Iterations | Rel = %f, Img = %f | x = %f y = %f | H for Help", max_iterations, rangeX, rangeY, middleX, middleY);
        std::string s(title);
        return s;
    }

#ifdef __cplusplus
}
#endif

double map(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (double)(x - in_min) * (out_max - out_min) / (double)(in_max - in_min) + out_min;
}

void game()
{
    int iteration;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for (int x = 0; x < WINDOW_WIDTH; x++)
        for (int y = 0; y < WINDOW_HEIGHT; y++)
        {
            iteration = 0;
            double real = 0;
            double imaginary = 0;
            double x0 = (double)x / (double)WINDOW_WIDTH;  //x prozent
            double y0 = (double)y / (double)WINDOW_HEIGHT; //y prozent
            x0 = x0 * rangeX + middleX - rangeX / 2;       //umsetzung von koordinatensystem zu pixeln
            y0 = y0 * rangeY + middleY - rangeY / 2;
            while (real * real + imaginary * imaginary <= 4 && iteration < max_iterations) // zum quadrat damit es immer positiv ist => 2hoch2=4
            {
                double temp = real * real - imaginary * imaginary + x0; //Komplexe berechnung mit normalen zahlen, temp da man in der nächsten zeile mit dem "alten" real rechnen muss
                imaginary = 2 * real * imaginary + y0;
                real = temp;
                iteration++;
            }
            switch (coloring)
            {
            case 0:
            {
                SDL_SetRenderDrawColor(renderer, 0, (iteration == max_iterations) ? 0 : (iteration * (256 / max_iterations)), 0, 0xff);
                SDL_RenderDrawPoint(renderer, x, y);
                break;
            }
            case 1:
            {
                long brightness = (iteration == max_iterations) ? 0 : map(iteration, 0, max_iterations, 0, 255);
                SDL_SetRenderDrawColor(renderer, map(brightness * brightness, 0, 6502, 0, 255), brightness, map(sqrt(brightness), 0, sqrt(255), 0, 255), 0xff);
                SDL_RenderDrawPoint(renderer, x, y);
                break;
            }
            case 2:
            {
                float n = (float)iteration;
                float a = 0.1f;
                if (iteration == max_iterations)
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                else
                    SDL_SetRenderDrawColor(renderer, map(0.5f * sin(a * n) + 0.5f, 0.0, 1.0, 0, 255), map(0.5f * sin(a * n + 2.094f) + 0.5f, 0.0, 1.0, 0, 255), map(0.5f * sin(a * n + 4.188f) + 0.5f, 0.0, 1.0, 0, 255), 0xff);
                SDL_RenderDrawPoint(renderer, x, y);
                break;
            }
            }
        }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    sprintf(title, "SPF: %f s | %d Iterations | Rel = %.20lf, Img = %.20lf | x = %.20lf y = %.20lf | H for Help", span.count(), max_iterations, rangeX, rangeY, middleX, middleY);
    std::cout << title << std::endl; //Rel = 0.00000219698560738535, Img = 0.00000125542034707734 | x = -1.71102468159729359520 y = -0.00451104455560013759
#ifdef __EMSCRIPTEN__
    EM_ASM(
        {
            document.getElementById("_spf").innerText = $0.toFixed(5);
            document.getElementById("_iterations").innerText = $1;
            document.getElementById("_rangex").innerText = $2.toFixed(10);
            document.getElementById("_rangey").innerText = $3.toFixed(10);
            document.getElementById("_middlex").innerText = $4.toFixed(10);
            document.getElementById("_middley").innerText = $5.toFixed(10);
        },
        span.count(), max_iterations, rangeX, rangeY, middleX, middleY);

#else
    SDL_SetWindowTitle(window, title);
#endif

    SDL_RenderPresent(renderer);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                w();
                break;
            case SDL_SCANCODE_A:
                a();
                break;
            case SDL_SCANCODE_S:
                s();
                break;
            case SDL_SCANCODE_D:
                d();
                break;
            case SDL_SCANCODE_Q:
                decIterations();
                break;
            case SDL_SCANCODE_E:
                incIterations();
                break;
            case SDL_SCANCODE_H:
                SDL_ShowSimpleMessageBox(0, "Help", "WASD to move around\nQ/E to change Iterations\nMousewheel to Zoom\nC to change Coloring\nX to Screenshot\nEscape to Quit", window);
                break;
            case SDL_SCANCODE_ESCAPE:
                run = 0;
                break;
            case SDL_SCANCODE_C:
                changeColor();
                break;
            case SDL_SCANCODE_X:
            {
                SDL_Surface *ss = SDL_GetWindowSurface(window);
                SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, ss->pixels, ss->pitch);
                char name[50];
                sprintf(name, "screenshots/%d %f %f.bmp", iteration, middleX, middleY);
                SDL_SaveBMP(ss, name);
                SDL_FreeSurface(ss);
            }
            break;
            }
            break;
        case SDL_MOUSEWHEEL:
            if (event.wheel.y > 0)
                zoomPlus();
            else if (event.wheel.y < 0)
                zoomMinus();
            break;
        case SDL_QUIT:
            run = 0;
            break;
        default:
            break;
        }
    }
}

int main(int argc, char **argv)
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        std::cerr << "Error\n";
        return -1;
    }
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    sprintf(title, "SPF: X s | %d Iterations | Rel = %f, Img = %f | x = %f y = %f | H for Help", max_iterations, rangeX, rangeY, middleX, middleY);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(game, 0, 1);
#else
    SDL_SetWindowTitle(window, title);
    while (run)
        game();
#endif
    SDL_Log("SDL quit after %i ticks", event.quit.timestamp);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}