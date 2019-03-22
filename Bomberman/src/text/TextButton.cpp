#include "../../header/text/TextButton.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/handler/MouseHandler.h"
#include "../../header/util/MathHelper.h"
#include "../../header/handler/AudioHandler.h"

GLFWcursor* TextButton::hand;
GLFWcursor* TextButton::arrow;

TextButton::TextButton(std::string text, Vec2 position, const Font* font, Vec4 color, TextRenderer::Alignment alignment) : Label(text, position, font, color, alignment) {

	if (!arrow || !hand) {

		arrow = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);

	}

}

void TextButton::update(TextRenderer* renderer, std::vector<Label*>& labels) {

	Vec2 mouse = MathHelper::windowToGLFWCoord(MouseHandler::getMousePos());
	float width = font->getWidth(this->text);
	float height = font->getHeight(this->text);

	width = (float) map(width, 0, DisplayManager::window->getWidth(), 0, 2.0f);
	height = (float) map(height, 0, DisplayManager::window->getHeight(), 0, 2.0f);

	if (mouse.x >= MathHelper::windowToGLFWCoord({ this->position.x, 0 }).x - width * .5f && mouse.x <= MathHelper::windowToGLFWCoord({ this->position.x, 0 }).x + width * .5f && mouse.y >= MathHelper::windowToGLFWCoord({ 0, DisplayManager::window->getHeight() - this->position.y }).y - height * .15f && mouse.y <= MathHelper::windowToGLFWCoord({ 0, DisplayManager::window->getHeight() - this->position.y }).y + height && !outsideNclicked) {

		this->over = true;

		DisplayManager::window->setCursor(hand);

		if (!MouseHandler::mouseDown && this->holding) {

			this->holding = false;
			this->outsideNclicked = false;

			this->callback();

			AudioHandler::button->stop();
			AudioHandler::button->play();

		}

		if (MouseHandler::mouseDown) {

			this->holding = true;

		}

	} else {

		int buttons = 0, overs = 0;
		for (auto& label : labels) {

			if (label == this) {

				continue;

			}

			TextButton* b = dynamic_cast<TextButton*>(label);

			if (b != nullptr) {

				buttons++;

				if (!b->over) {

					overs++;

				}

			}

		}

		if (buttons == overs) {

			DisplayManager::window->setCursor(hand);

		}

		if (MouseHandler::mouseDown) {

			this->outsideNclicked = true;
			this->holding = false;

		}

		this->over = false;

	}

	if (!MouseHandler::mouseDown) {

		this->outsideNclicked = false;
		this->holding = false;

	}

}

TextButton* TextButton::setCallback(void (*callback)()) {

	this->callback = callback;

	return this;

}