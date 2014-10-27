#include "Button.h"
#include "Visitor.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::accept(Visitor& visitor) {
	visitor.visit(this);
}