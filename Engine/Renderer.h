#pragma once
#include <SDL3/SDL.h>
namespace nu {
	class Renderer
	{
	public:
		~Renderer();
		bool Initialize(const char* name, int width, int height);
		void Quit();
		void SetColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255) const;
		void SetColorFloat(float red, float green, float blue, float alpha = 1.0f) const;
		void Clear();
		void RenderPresent() const;
		void RenderPoint(float x, float y) const;
		void RenderLine(float x1, float y1, float x2, float y2) const;
		void RenderRect(float x, float y, float width, float height, bool fill) const;
	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
}
