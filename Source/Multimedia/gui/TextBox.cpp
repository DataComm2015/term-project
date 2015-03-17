#include "TextBox.h"

namespace GUI
{
	TextBox::TextBox()
	{
		selected = false;
	}
	
	TextBox::~TextBox(){}
	
	void TextBox::toggleSelected(bool s)
	{
		selected = s;
	}
	
	void TextBox::process(sf::Event& e)
	{
		if(selected && e.type == sf::Event::KeyPressed)
		{
			setText(getText() + "g");
		}
	}
	
	std::string TextBox::getText()
	{
		return this->operator()().getString();
	}
	
	void TextBox::setText(std::string s)
	{
		this->operator()().setString(s);
	}
}
