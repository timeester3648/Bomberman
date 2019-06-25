#pragma once

#include <EOUL\Image.hpp>
#include <GLFW\glfw3.h>
#include <functional>
#include <string>
#include <vector>

namespace EOUL {

	namespace GL {

		class Window final {

			private:

				unsigned char buttons = 0;

				double mouseX = 0.0;
				double mouseY = 0.0;

				unsigned int width, height, min_width = GLFW_DONT_CARE, min_height = GLFW_DONT_CARE, max_width = GLFW_DONT_CARE, max_height = GLFW_DONT_CARE;
				float aspect_ratio;

				std::function<void (double, double)> onScrollCallback;
				std::function<void (int, int, int)> onMouseInputCallback;
				std::function<void (int, int)> onResizeCallback;
				std::function<void (int, const char*)> onErrorCallback;
				std::function<void (double, double)> onMouseMoveCallback;
				std::function<void (int)> onCursorEnterCallback;
				std::function<void (int, const char**)> onDropCallback;
				std::function<void (int, int, int, int)> onKeyInputCallback;

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
				std::vector<std::filesystem::path> icons;

			public:

				Window(unsigned int width, unsigned int height, std::string title);
				~Window();

				Window(const Window& other) = delete;
				Window(Window&&) = delete;

			public:

				/* returns the windows title */
				const std::string& getTitle() const;

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

				/* returns mouse position [0 - width] and [0 - height] */
				std::pair<double, double> getMousePos() const;

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
				/* returns if glfw initialized, tries to initialize glfw when noet already done. resets window hints. */
				bool init();

				/* returns the window position */
				std::pair<int, int> getWindowPosition() const;

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
				/* set window hint. needs to be called before show(). returns itself for convenience */
				Window* setWindowHint(int hint, int value);

				/* 

					returns the GLFWwindow pointer.
					changing certain properties/callbacks could resolve into errors.

				*/
				GLFWwindow* getWindow() const;

				/* initializes GLFW if not already initialized and shows/creates the window */
				void show();
				/* closes the window */
				void close();
				/* swaps buffers, only works with an OpenGL/OpenGL ES context */
				void swapBuffers() const;
				/* updates the window (polls the events) */
				void poll() const;
				/* centers the window */
				void center();

				/* adds an icon */
				void addIcon(std::filesystem::path path);
				/* adds an icon */
				void addIcon(const IO::Image& image);
				/* adds an vector of icons */
				void addIcons(const std::vector<std::filesystem::path>& paths);
				/* adds an vector of icons */
				void addIcons(const std::vector<IO::Image>& images);

				/* adds a scroll event handler */
				void onScroll(std::function<void (double, double)> callback);
				/* adds a mouse input event handler */
				void onMouseInput(std::function<void (int, int, int)> callback);
				/* adds a resize event handler */
				void onResize(std::function<void (int, int)> callback);
				/* adds an error event handler */
				void onError(std::function<void (int, const char*)> callback);
				/* adds an mouse move event handler */
				void onMouseMove(std::function<void (double, double)> callback);
				/* adds a cursor enter event handler */
				void onCursorEnter(std::function<void (int)> callback);
				/* adds a drop event handler */
				void onDrop(std::function<void (int, const char**)> callback);
				/* adds a key input event handler */
				void onKeyInput(std::function<void (int, int, int, int)> callback);

			private:

				void cleanUp();
				void updateAspectRatio();
				void updateMinMax();

				GLFWmonitor* getBestMonitor();

		};

	}

}