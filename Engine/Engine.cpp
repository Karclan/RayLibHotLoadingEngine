#include "Graphics/Window.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main( int argc, char * argv[] )
{
	Graphics::Window window = Graphics::Window::CreateWindow( "Basic window", { 800, 450, 0, 0 } );
	
	// Main game loop
	while ( !window.ShouldClose() )    // Detect window close button or ESC key
	{
		//TODO: Fixed update

		window.BeginDraw();

		window.RenderUpdate();

		window.EndDraw();
		
	}

	window.Close();

	return 0;
}