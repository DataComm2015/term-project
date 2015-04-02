#include "TextBox.h"

namespace GUI
{
	TextBox::TextBox(std::function<void(void *)> c, void * data, unsigned int l)
	{
		selected = false;
		complete = c;
		usrDataOnComplete = data;
		limit = l;
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
			if(e.key.code == sf::Keyboard::BackSpace && !getText().empty())
			{
				std::string temp = getText();
				temp.erase(temp.end()-1);
				setText(temp);
			}
			else if(e.key.code == sf::Keyboard::Return)
			{
				selected = false;
				if(complete != NULL)
					complete(usrDataOnComplete);
			}
		}
		else if(selected && e.type == sf::Event::TextEntered && (getText().length() <= limit))
		{
			//So we don't get backspace chars in our text
			if(e.text.unicode >= ' ')
				setText(getText() + (char)e.text.unicode);
		}
	}

	std::string TextBox::getText()
	{
		return this->text().getString();
	}

	void TextBox::setText(std::string s)
	{
		this->text().setString(s);
	}

	bool TextBox::getSelected()
	{
		return this->selected;
	}
}
