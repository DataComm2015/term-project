#ifndef TEXTBOX
#define TEXTBOX

#include <string>
#include <functional>
#include "../graphics/object/TGO.h"

namespace GUI
{
	class TextBox : public TGO
	{
		public:
			TextBox(std::function<void()> c);
			virtual ~TextBox();
			void toggleSelected(bool s);
			void process(sf::Event& e);
			std::string getText();
			void setText(std::string s);
		private:
			bool selected;
			std::function<void()> complete;
	};
}

#endif
