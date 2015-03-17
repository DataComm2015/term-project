#ifndef TEXTBOX
#define TEXTBOX

#include <string>
#include "../graphics/object/TGO.h"

namespace GUI
{
	class TextBox : public TGO
	{
		public:
			TextBox();
			virtual ~TextBox();
			void toggleSelected(bool s);
			void process(sf::Event& e);
			std::string getText();
			void setText(std::string s);
		private:
			bool selected;
	};
}

#endif
