#pragma once

#include <EOUL\Image.h>
#include <GLFW\glfw3.h>
#include <string>
#include <vector>

namespace EOUL {

	namespace GL {

		class Window {

			public:

				struct WindowPos {

					int x, y;

				};

			private:

				static unsigned char buttons;

				static double mouseX;
				static double mouseY;

				static unsigned int width, height, min_width, min_height, max_width, max_height;
				static float aspect_ratio;

				static void (*on_cursor_enter)(int entered);
				static void (*on_resize)(int width, int height);
				static void (*on_mouse_move)(double x, double y);
				static void (*on_drop)(int count, const char** paths);
				static void (*on_scroll)(double xoffset, double yoffset);
				static void (*on_error)(int error, const char* description);
				static void (*on_mouse_input)(int button, int action, int mods);
				static void (*on_key_input)(int key, int scancode, int action, int mods);

			private:				

				GLFWwindow* window = nullptr;
				GLFWimage* images = nullptr;

				int samples = 4;

				bool resizable;
				bool closed = false;
				bool showed = false;
				bool minimized = false;
				bool maximized = false;
				bool decorated = true;
				bool hadDecorated = true;
				int swap_interval = 1;

				int old[4];

				std::string title;
				std::vector<std::string> icons;

			public:

				Window(unsigned int width, unsigned int height, std::string title);
				~Window();

			public:

				/* returns the current width of the window */
				unsigned int getWidth() const;
				/* returns the current height of the window */
				unsigned int getHeight() const;

				/* returns the current input mode */
				int getInputMode(int mode) const;

				/* returns mouse x position [0 - width] */
				double getMouseX() const;
				/* returns mouse y position [0 - height] */
				double getMouseY() const;

				/* returns if the window is resizable */
				bool isResizable() const;
				/* returns if the mouse button is pressed */
				bool isMouseDown(int button) const;
				/* returns if the mouse button is not pressed */
				bool isMouseUp(int button) const;
				/* returns if the key is pressed */
				bool isKeyDown(int key) const;
				/* returns if the key is not pressed */
				bool isKeyUp(int key) const;
				/* returns if a close is requested */
				bool shouldClose() const;
				/* returns if window is decorated */
				bool isDecorated() const;
				/* returns if the window is maximized */
				bool isMaximized() const;
				/* returns if the window is minimized */
				bool isMinimized() const;

				/* returns the window position */
				WindowPos getWindowPosition() const;

				/* returns the current aspect ratio */
				float getAspectRatio() const;

				/* set window width. returns itself for convenience */
				Window* setWidth(unsigned int width);
				/* set window height. returns itself for convenience */
				Window* setHeight(unsigned int height);
				/* set window max width. returns itself for convenience */
				Window* setMaxWidth(unsigned int width);
				/* set window max height. returns itself for convenience */
				Window* setMaxHeight(unsigned int height);
				/* set window max width. returns itself for convenience */
				Window* setMinWidth(unsigned int width);
				/* set window max height. returns itself for convenience */
				Window* setMinHeight(unsigned int height);
				/* set if the window should be resizable, only works if show() isn't called. returns itself for convenience */
				Window* setResizable(bool resizable);
				/* set this window swap interval. returns itself for convenience */
				Window* setSwapInterval(int interval);
				/* set samples, only works if show() isn't called before. returns itself for convenience */
				Window* setSamples(int samples);
				/* set cursor. returns itself for convenience */
				Window* setCursor(GLFWcursor* cursor);
				/* set input mode. returns itself for convenience */
				Window* setInputMode(int mode, int value);
				/* set cursor pos. returns itself for convenience */
				Window* setCursorPos(double x, double y);
				/* maximizes the window. returns itself for convenience */
				Window* setMaximized(bool maximize, bool decorated = true);
				/* minimizes the window. returns itself for convenience */
				Window* setMinimized(bool minimize);
				/* set window decorated. returns itself for convenience */
				Window* setDecorated(bool decorated);

				/* initializes GLFW and GLEW and shows/creates the window */
				void show();
				/* closes the window */
				void close();
				/* update the window (should be called after every frame rendered) */
				void update() const;
				/* centers the window */
				void center();

				/* adds an icon */
				void addIcon(std::string path);
				/* adds an icon */
				void addIcon(const IO::Image& image);
				/* adds an vector of icons */
				void addIcons(const std::vector<std::string>& paths);
				/* adds an vector of icons */
				void addIcons(const std::vector<IO::Image>& images);

				/* adds a scroll event handler */
				void onScroll(void (*on_scroll)(double xoffset, double yoffset));
				/* adds a mouse input event handler */
				void onMouseInput(void (*on_mouse_input)(int button, int action, int mods));
				/* adds a resize event handler */
				void onResize(void (*on_resize)(int width, int height));
				/* adds an error event handler */
				void onError(void (*on_error)(int error, const char* description));
				/* adds an mouse move event handler */
				void onMouseMove(void (*on_mouse_move)(double x, double y));
				/* adds a cursor enter event handler */
				void onCursorEnter(void (*on_cursor_enter)(int entered));
				/* adds a drop event handler */
				void onDrop(void (*on_drop)(int count, const char** paths));
				/* adds a key input event handler */
				void onKeyInput(void (*on_key_input)(int key, int scancode, int action, int mods));

			private:

				void cleanUp();
				void updateAspectRatio();
				void updateMinMax();

				GLFWmonitor* getBestMonitor();

		};

	}

}