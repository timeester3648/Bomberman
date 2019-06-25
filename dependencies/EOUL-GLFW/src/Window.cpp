#include <EOUL-GLFW\Window.h>

#define SET_EOUL_BUTTON_TRUE(value, button) (value |= 0x1 << button)
#define SET_EOUL_BUTTON_FALSE(value, button) (value &= ~((unsigned char) 0x1 << button))

#define GET_EOUL_BUTTON(value, button) ((value >> button) & 0x1)

namespace EOUL {

	namespace GL {

		Window::Window(unsigned int width, unsigned int height, std::string title) : title(std::move(title)) {

			this->width = width;
			this->height = height;
			this->aspect_ratio = (float) this->width / (float) this->height;

		}

		Window::~Window() {

			this->close();

		}

		bool Window::init() {

			bool b = glfwInit();

			if (!b) {

				this->close();

			}

			return b;

		}

		void Window::show() {

			if (this->showed) {

				return;

			} else {

				this->showed = true;

			}

			this->init();

			if (!this->icons.empty()) {

				this->images = new GLFWimage[this->icons.size()];

				size_t i = 0;
				for (auto& path : this->icons) {

					int numComponents = 0;

					this->images[i].pixels = dependencies::stbi_load(path.u8string().c_str(), &this->images[i].width, &this->images[i].height, &numComponents, 0);

					i++;

				}

			}

			glfwWindowHint(GLFW_SAMPLES, this->samples);
			glfwWindowHint(GLFW_RESIZABLE, this->resizable);

			this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);

			if (!this->icons.empty()) {

				glfwSetWindowIcon(this->window, (int) this->icons.size(), this->images);

			}

			glfwMakeContextCurrent(this->window);
			glfwSetWindowUserPointer(this->window, this);

			glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS) {

					SET_EOUL_BUTTON_TRUE(wnd->buttons, button);

				} else if (action == GLFW_RELEASE) {

					SET_EOUL_BUTTON_FALSE(wnd->buttons, button);

				}

			});

			glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double x, double y) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				wnd->mouseX = x;
				wnd->mouseY = y;

			});

			glfwSetWindowSizeCallback(this->window, [](GLFWwindow* window, int width, int height) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				wnd->width = (unsigned int) width;
				wnd->height = (unsigned int) height;

			});

			glfwSwapInterval(this->swap_interval);

		}

		GLFWwindow* Window::getWindow() const {

			return this->window;

		}

		void Window::onScroll(std::function<void (double, double)> callback) {

			this->onScrollCallback = callback;

			glfwSetScrollCallback(this->window, [](GLFWwindow* window, double xoffset, double yoffset) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				wnd->onScrollCallback(xoffset, yoffset);

			});

		}

		void Window::onMouseInput(std::function<void (int, int, int)> callback) {

			this->onMouseInputCallback = callback;

			glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS) {

					SET_EOUL_BUTTON_TRUE(wnd->buttons, button);

				} else if (action == GLFW_RELEASE) {

					SET_EOUL_BUTTON_FALSE(wnd->buttons, button);

				}

				wnd->onMouseInputCallback(button, action, mods);

			});

		}

		void Window::onResize(std::function<void (int, int)> callback) {

			this->onResizeCallback = callback;

			glfwSetWindowSizeCallback(this->window, [](GLFWwindow* window, int width, int height) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				wnd->width = (unsigned int) width;
				wnd->height = (unsigned int) height;

				wnd->onResizeCallback(width, height);

			});

		}

		void Window::onError(std::function<void (int, const char*)> callback) {

			this->onErrorCallback = callback;

			glfwSetErrorCallback(callback.target<void (int, const char*)>());

		}

		void Window::onMouseMove(std::function<void (double, double)> callback) {

			this->onMouseMoveCallback = callback;

			glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double x, double y) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				wnd->mouseX = x;
				wnd->mouseY = y;

				wnd->onMouseMoveCallback(x, y);

			});

		}

		void Window::onCursorEnter(std::function<void (int)> callback) {

			this->onCursorEnterCallback = callback;

			glfwSetCursorEnterCallback(this->window, [](GLFWwindow* window, int entered) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				wnd->onCursorEnterCallback(entered);

			});

		}

		void Window::onDrop(std::function<void (int, const char**)> callback) {

			this->onDropCallback = callback;

			glfwSetDropCallback(window, [](GLFWwindow* window, int count, const char** paths) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				wnd->onDropCallback(count, paths);

			});

		}

		void Window::onKeyInput(std::function<void (int, int, int, int)> callback) {

			this->onKeyInputCallback = callback;

			glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {

				Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));

				wnd->onKeyInputCallback(key, scancode, action, mods);

			});

		}

		void Window::addIcon(std::filesystem::path path) {

			this->icons.emplace_back(std::move(path));

		}

		void Window::addIcon(const EOUL::IO::Image& image) {

			this->addIcon(std::move(std::filesystem::path(image.getAbsolutePath())));

		}

		void Window::addIcons(const std::vector<std::filesystem::path>& paths) {

			for (const auto& str : paths) {

				this->addIcon(str);

			}

		}

		void Window::addIcons(const std::vector<EOUL::IO::Image>& images) {

			for (const auto& image : images) {

				this->addIcon(image);

			}

		}

		void Window::close() {

			if (this->closed) {

				return;

			}

			this->cleanUp();

			this->closed = true;

			glfwSetWindowShouldClose(this->window, true);

		}

		void Window::swapBuffers() const {

			glfwSwapBuffers(this->window);

		}

		void Window::poll() const {

			glfwPollEvents();

		}

		void Window::cleanUp() {

			delete[] this->images;

		}

		double Window::getMouseX() const {

			return this->mouseX;

		}

		double Window::getMouseY() const {

			return this->mouseY;

		}

		std::pair<double, double> Window::getMousePos() const {

			return { this->mouseX, this->mouseY };

		}

		Window* Window::setMaxWidth(unsigned int width) {

			this->max_width = width;

			this->updateMinMax();

			return this;

		}

		Window* Window::setMaxHeight(unsigned int height) {

			this->max_height = height;

			this->updateMinMax();

			return this;

		}

		Window* Window::setMinWidth(unsigned int width) {

			this->min_width = width;

			this->updateMinMax();

			return this;

		}

		Window* Window::setMinHeight(unsigned int height) {

			this->min_height = height;

			this->updateMinMax();

			return this;

		}

		Window* Window::setResizable(bool resizable) {

			this->resizable = resizable;

			return this;

		}

		Window* Window::setSwapInterval(int interval) {

			this->swap_interval = interval;

			return this;

		}

		Window* Window::setSamples(int samples) {

			this->samples = samples;

			return this;

		}

		Window* Window::setCursor(GLFWcursor* cursor) {

			glfwSetCursor(window, cursor);

			return this;

		}

		Window* Window::setInputMode(int mode, int value) {

			glfwSetInputMode(glfwGetCurrentContext(), mode, value);

			return this;

		}

		Window* Window::setCursorPos(double x, double y) {

			glfwSetCursorPos(this->window, x, y);

			return this;

		}

		Window* Window::setWidth(unsigned int width) {

			this->width = width;

			glfwSetWindowSize(this->window, Window::width, Window::height);

			this->updateAspectRatio();

			return this;

		}

		Window* Window::setHeight(unsigned int height) {

			this->height = height;

			glfwSetWindowSize(this->window, Window::width, Window::height);

			this->updateAspectRatio();

			return this;

		}

		bool Window::isResizable() const {

			return this->resizable;

		}

		bool Window::isMouseDown(int button) const {

			return GET_EOUL_BUTTON(this->buttons, button);

		}

		bool Window::isMouseUp(int button) const {

			return !this->isMouseDown(button);

		}

		bool Window::isKeyDown(int key) const {

			return (glfwGetKey(this->window, key));

		}

		bool Window::isKeyUp(int key) const {

			return !this->isKeyDown(key);

		}

		bool Window::shouldClose() const {

			return (bool)glfwWindowShouldClose(this->window);

		}

		bool Window::isDecorated() const {

			return this->decorated;

		}

		bool Window::isMaximized() const {

			return this->maximized;

		}

		bool Window::isMinimized() const {

			return this->minimized;

		}

		std::pair<int, int> Window::getWindowPosition() const {

			int x, y;

			glfwGetWindowPos(this->window, &x, &y);

			return { x, y };

		}

		const std::string& Window::getTitle() const {

			return this->title;

		}

		unsigned int Window::getWidth() const {

			return this->width;

		}

		unsigned int Window::getHeight() const {

			return this->height;

		}

		int Window::getInputMode(int mode) const {

			return glfwGetInputMode(this->window, mode);

		}

		void Window::center() {

			int sx = 0, sy = 0;
			int px = 0, py = 0;
			int mx = 0, my = 0;
			int monitor_count = 0;
			int best_area = 0;
			int final_x = 0, final_y = 0;

			glfwGetWindowSize(this->window, &sx, &sy);
			glfwGetWindowPos(this->window, &px, &py);

			GLFWmonitor** m = glfwGetMonitors(&monitor_count);

			if (!m) {

				return;

			}

			for (int j = 0; j < monitor_count; j++) {

				glfwGetMonitorPos(m[j], &mx, &my);

				const GLFWvidmode * mode = glfwGetVideoMode(m[j]);

				if (!mode) {

					continue;

				}

				int minX = (int) fmaxf((float) mx, (float) px);
				int minY = (int) fmaxf((float) my, (float) py);
				int maxX = (int) fminf((float) (mx + mode->width), (float) (px + sx));
				int maxY = (int) fminf((float) (my + mode->height), (float) (py + sy));
				int area = (int) fmaxf((float) (maxX - minX), 0.0f) * (int) fmaxf((float)(maxY - minY), 0.0f);

				if (area > best_area) {

					final_x = mx + (mode->width - sx) / 2;
					final_y = my + (mode->height - sy) / 2;

					best_area = area;

				}

			}

			if (best_area) {

				glfwSetWindowPos(window, final_x, final_y);

			} else {

				GLFWmonitor* primary = glfwGetPrimaryMonitor();

				if (primary) {

					const GLFWvidmode* desktop = glfwGetVideoMode(primary);

					if (desktop) {

						glfwSetWindowPos(this->window, (desktop->width - sx) / 2, (desktop->height - sy) / 2);

					} else {

						return;
					}

				} else {

					return;

				}

			}

		}

		Window* Window::setMaximized(bool maximize, bool decorated) {

			if (!this->maximized && maximize) {

				this->hadDecorated = this->decorated;

				if (decorated) {

					glfwSetWindowAttrib(window, GLFW_DECORATED, decorated);
					glfwMaximizeWindow(this->window);

				} else {

					GLFWmonitor* monitor = this->getBestMonitor();
					const GLFWvidmode* mode = glfwGetVideoMode(monitor);

					int x, y;

					glfwGetWindowPos(this->window, &x, &y);

					this->old[0] = x;
					this->old[1] = y;
					this->old[2] = this->width;
					this->old[3] = this->height;

					glfwSetWindowMonitor(this->window, monitor, 0, 0, mode->width, mode->height, 0);

				}

				this->maximized = true;

				glfwGetWindowSize(this->window, (int*)&this->width, (int*)&this->height);

				this->onResizeCallback(this->width, this->height);

			} else if (this->maximized && !maximize) {

				if (glfwGetWindowMonitor(this->window) == nullptr) {

					glfwSetWindowAttrib(window, GLFW_DECORATED, this->hadDecorated);
					glfwRestoreWindow(this->window);

				} else {

					glfwSetWindowMonitor(this->window, nullptr, this->old[0], this->old[1], this->old[2], this->old[3], 0);

				}

				this->maximized = false;

			}

			return this;

		}

		Window* Window::setMinimized(bool minimize) {

			if (!this->minimized && minimize) {

				glfwIconifyWindow(this->window);

				this->minimized = true;

			} else if (this->minimized && !minimize) {

				glfwRestoreWindow(window);

				this->minimized = false;

			}

			return this;

		}

		Window* Window::setDecorated(bool decorated) {

			this->decorated = decorated;

			glfwSetWindowAttrib(window, GLFW_DECORATED, decorated);

			return this;

		}

		Window* Window::setWindowHint(int hint, int value) {

			glfwWindowHint(hint, value);

			return this;

		}

		float Window::getAspectRatio() const {

			return this->aspect_ratio;

		}

		void Window::updateAspectRatio() {

			this->aspect_ratio = (float) width / (float) height;

		}

		void Window::updateMinMax() {

			glfwSetWindowSizeLimits(this->window, this->min_width, this->min_height, this->max_width, this->max_height);

		}

		GLFWmonitor* Window::getBestMonitor() {

			int best_area = 0;
			int sx = 0, sy = 0;
			int px = 0, py = 0;
			int mx = 0, my = 0;
			int monitor_count = 0;
			int final_x = 0, final_y = 0;

			glfwGetWindowSize(this->window, &sx, &sy);
			glfwGetWindowPos(this->window, &px, &py);

			GLFWmonitor** m = glfwGetMonitors(&monitor_count);
			int best = -1;

			if (!m) {

				return glfwGetPrimaryMonitor();

			}

			for (int j = 0; j < monitor_count; j++) {

				glfwGetMonitorPos(m[j], &mx, &my);

				const GLFWvidmode* mode = glfwGetVideoMode(m[j]);

				if (!mode) {

					continue;

				}

				int minX = (int) fmaxf((float) mx, (float) px);
				int minY = (int) fmaxf((float) my, (float) py);
				int maxX = (int) fminf((float) (mx + mode->width), (float) (px + sx));
				int maxY = (int) fminf((float) (my + mode->height), (float) (py + sy));
				int area = (int) fmaxf((float) (maxX - minX), 0.0f) * (int) fmaxf((float) (maxY - minY), 0.0f);

				if (area > best_area) {

					final_x = mx + (mode->width - sx) / 2;
					final_y = my + (mode->height - sy) / 2;

					best_area = area;

					best = j;

				}

			}

			if (best_area) {

				return (best == -1 ? glfwGetPrimaryMonitor() : m[best]);

			} else {

				return glfwGetPrimaryMonitor();

			}

		}

	}

}