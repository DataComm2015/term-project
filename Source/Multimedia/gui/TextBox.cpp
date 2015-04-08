#include "TextBox.h"

namespace GUI
{
	/**
	* Initializes a textbox.
	*
	* @date         2015-02-27
	*
	* @revisions	
	*
	* @designer     Lewis Scott
	*
	* @programmer   Lewis Scott
	*
	* @parameter	std::function c:	The callback function
	* @parameter	void * data:		The data to initialize the textbox with
	* @parameter	unsigned int l:		The maximum length (in characters) of the text box				
	*
	* @return       initializer
	*/
	TextBox::TextBox(std::function<void(void *)> c, void * data, unsigned int l)
	{
		selected = false;
		complete = c;
		usrDataOnComplete = data;
		limit = l;
	}

	/**
	* Destroys a textbox.
	*
	* @date         2015-02-27
	*
	* @revisions	
	*
	* @designer     Lewis Scott
	*
	* @programmer   Lewis Scott			
	*
	* @return       destructor
	*/
	TextBox::~TextBox(){}

	/**
	* Toggles the enabled status of the textbox.
	*
	* @date         2015-02-27
	*
	* @revisions	
	*
	* @designer     Lewis Scott
	*
	* @programmer   Lewis Scott
	*
	* @parameter	bool s:		Whether or not the textbox should be enabled			
	*
	* @return       void
	*/
	void TextBox::toggleSelected(bool s)
	{
		selected = s;
	}

	/**
	* Event catcher for the texbox. Catches and processes key input events
	*
	* @date         2015-02-27
	*
	* @revisions	
	*
	* @designer     Lewis Scott
	*
	* @programmer   Lewis Scott
	*
	* @parameter	sf::Event& e:	The event that occurred			
	*
	* @return       void
	*/
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

	/**
	* Returns the contents.
	*
	* @date         2015-02-27
	*
	* @revisions	
	*
	* @designer     Lewis Scott
	*
	* @programmer   Lewis Scott
	*			
	*
	* @return       std::string:	The text currently in the textbox
	*/
	std::string TextBox::getText()
	{
		return this->text().getString();
	}

	/**
	* Sets the text in the textbox manually
	*
	* @date         2015-02-27
	*
	* @revisions	
	*
	* @designer     Lewis Scott
	*
	* @programmer   Lewis Scott
	*
	* @parameter	std::string s:	The string to apply to the textbox				
	*
	* @return       void
	*/
	void TextBox::setText(std::string s)
	{
		this->text().setString(s);
	}

	/**
	* Returns whether or not the textbox is selected (active)
	*
	* @date         2015-02-27
	*
	* @revisions	
	*
	* @designer     Lewis Scott
	*
	* @programmer   Lewis Scott
	*			
	*
	* @return       bool:	Whether or not the textbox is currently selected
	*/
	bool TextBox::getSelected()
	{
		return this->selected;
	}
}
