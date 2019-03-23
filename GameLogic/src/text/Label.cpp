#include "../../header/text/Label.h"
#include "../../header/display/render/TextRenderer.h"

Label::Label(std::string text, Vec2 position, const Font* font, Vec4 color, TextRenderer::Alignment alignment) : text(text), position(position), font(font), color(color), alignment(alignment) {

}