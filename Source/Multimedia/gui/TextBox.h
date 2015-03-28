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
			TextBox(std::function<void(void *)> c = NULL, void * data = NULL);
			virtual ~TextBox();
			void toggleSelected(bool s);
			void process(sf::Event& e);
			std::string getText();
			void setText(std::string s);
		private:
			void * usrDataOnComplete;
			bool selected;
			std::function<void(void*)> complete;
	};
}

#endif
