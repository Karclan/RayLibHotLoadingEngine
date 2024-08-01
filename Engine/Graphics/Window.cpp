#include "Window.hpp"

#include <raylib.h>
#include <utility>

#include "../Utility/Assert.hpp"

namespace Graphics
{
	namespace
	{
		static bool s_bCreatedWindow = false;
	} 

	Window Window::CreateWindow( const char * _name,  WindowDimensions && _dimensions )
	{
		if ( s_bCreatedWindow )
		{
			HL_CORE_ASSERT( false, "Trying to create a 2nd window within this " );
		}
		s_bCreatedWindow = true;
		Utils::Log( LogType::Info, "Window Created!" );
		return Window( _name, std::forward<WindowDimensions>(_dimensions) );
	}

	bool Window::ShouldClose() const
	{
		return WindowShouldClose();
	}

	void Window::BeginDraw() const
	{
		BeginDrawing();
	}

	void Window::RenderUpdate()
	{
		ClearBackground( RAYWHITE );
		DrawText( "Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY );
		//Render update, we'll be doing the drawing within here
	}

	void Window::EndDraw() const
	{
		EndDrawing();
	}

	void Window::Close()
	{
		CloseWindow();
	}

	Window::Window( const char * _name, WindowDimensions && _dimensions )
		: m_WindowDimensions( _dimensions )
	{
		InitWindow( m_WindowDimensions.m_Width, m_WindowDimensions.m_Height, _name );
		SetTargetFPS( 60 );// Set our game to run at 60 frames-per-second
		SetWindowPosition( m_WindowDimensions.m_Width, m_WindowDimensions.m_Height );
		m_WindowHandle = GetWindowHandle();
	}
}