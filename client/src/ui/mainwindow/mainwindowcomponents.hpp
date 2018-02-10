//
// Created by Igor on 2/9/2018.
//

#ifndef TCP_CHAT_MAINWINDOWCOMPONENTS_HPP
#define TCP_CHAT_MAINWINDOWCOMPONENTS_HPP


#include "../components.hpp"
#include "../components/button.hpp"
#include "../components/textarea.hpp"
#include "../components/textfield.hpp"

namespace ui {

	class MainWindowComponents : public Components {
	public:
		explicit MainWindowComponents(Application *app, Window *parent);

		void input(WPARAM wParam) override;

	private:
		void sendMessage();
	};

}


#endif //TCP_CHAT_MAINWINDOWCOMPONENTS_HPP
