#include "pch.h"
#include "Renderer.h"
#include <iostream>

namespace nu
{
    void Renderer::Quit()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
    bool Renderer::Initialize(const char* name, int width, int height)
    {
        SDL_Init(SDL_INIT_VIDEO);

        m_window = SDL_CreateWindow(name, width, height, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        SDL_SetRenderVSync(m_renderer, 1);

        return true;
    }
    void Renderer::SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) const
    {
        SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
    }
    void Renderer::SetColorFloat(float red, float green, float blue, float alpha) const
    {
        SDL_SetRenderDrawColorFloat(m_renderer, red, green, blue, alpha);
    }
    void Renderer::Clear() {
        SDL_RenderClear(m_renderer);
    }
    void Renderer::RenderPresent() const
    { 
        SDL_RenderPresent(m_renderer);
    }
    void Renderer::RenderPoint(float x, float y) const
    {
        SDL_RenderPoint(m_renderer, x, y);
    }
    void Renderer::RenderLine(float x1, float y1, float x2, float y2) const
    {
        SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }
    void Renderer::RenderRect(float x, float y, float width, float height, bool fill = true) const
    {
        SDL_FRect rect{ x, y, width, height };
        (fill) ? SDL_RenderFillRect(m_renderer, &rect) : SDL_RenderRect(m_renderer, &rect);
    }
    Renderer::~Renderer()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }
};