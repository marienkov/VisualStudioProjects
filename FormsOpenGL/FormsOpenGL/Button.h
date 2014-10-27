#pragma once
#include "View.h"

class Button :
	public View
{
public:
	Button();
	virtual ~Button();

	void accept(Visitor&);
};