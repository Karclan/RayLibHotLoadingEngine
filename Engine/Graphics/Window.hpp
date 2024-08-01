#pragma once

namespace Graphics
{

	/// <summary>
	/// Window Dimensions struct
	/// Gives us a way to define window dimensions prior to creation of a window
	/// This structure is subject to change in the future, including the name of the strustructure tooz
	/// </summary>
	struct WindowDimensions
	{
		unsigned int m_Width { 0 };
		unsigned int m_Height { 0 };
		unsigned int m_XPosition { 0 };
		unsigned int m_YPosition { 0 };
		//Can expand this to contain flags for windowed border-less etc etc.
	};


	/// <summary>
	/// Window class
	/// Only 1 of these can exist in the project at a time due to limitations with Raylib
	/// </summary>
	class Window
	{
	public:
		static Window CreateWindow( const char * _name, WindowDimensions && _definition ); //A way of guarding we only create 1 window for the project.

		bool ShouldClose() const;

		void BeginDraw() const;

		void RenderUpdate();

		void EndDraw() const;

		void Close();

	private:
		explicit Window( const char * _name, WindowDimensions && _dimensions );

		WindowDimensions m_WindowDimensions;
		void * m_WindowHandle { nullptr };
	};
}