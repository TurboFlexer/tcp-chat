//
// Created by Igor on 2/9/2018.
//

#include "../../application.hpp"
#include "configwindowcomponents.hpp"
#include "../components/button.hpp"
#include "../components/textfield.hpp"
#include "../components/label.hpp"

ui::ConfigWindowComponents::ConfigWindowComponents(Application *app, Window *parent) : Components(app, parent) {
	HWND pHwnd = parent->getHwnd();

	add("saveButton", new Button(L"Save", {20, 190}, {120, 20}, pHwnd, 1));
	add("closeButton", new Button(L"Close", {20, 220}, {120, 20}, pHwnd, 2));

	add("ipLabel", new Label(L"IP", {20, 10}, {120, 20}, pHwnd, 3));
	add("portLabel", new Label(L"Port", {20, 65}, {120, 20}, pHwnd, 4));
	add("nameLabel", new Label(L"Name", {20, 120}, {120, 20}, pHwnd, 5));

	add("textFieldIP", new TextField({20, 30}, {120, 20}, pHwnd, 6));
	add("textFieldPort", new TextField({20, 85}, {120, 20}, pHwnd, 0, DEFAULT_EDIT_STYLE | ES_NUMBER));
	add("textFieldName", new TextField({20, 140}, {120, 20}, pHwnd, 0));
}

void ui::ConfigWindowComponents::input(WPARAM wParam) {
	switch (LOWORD(wParam)) {
		case 1: {
			std::wstring wideIp = ((TextField &) get("textFieldIP")).getText();

			std::string ip(wideIp.begin(), wideIp.end());
			uint16_t port = (uint16_t) std::stoi(((TextField &) get("textFieldPort")).getText());
			std::wstring name = ((TextField &) get("textFieldName")).getText();

			if (inet_addr(ip.c_str()) == INADDR_NONE) {
				MessageBox(parent->getHwnd(), L"Invalid ip address", L"Error", MB_OK | MB_ICONERROR);
				return;
			}

			Config config;
			config.name = name;
			config.ip = ip;
			config.port = port;

			Config::save(config);

			app->shouldClose(false);
			break;
		}
		case 2:
			if (app->shouldClose()) {
				MessageBeep(1);
				if (MessageBox(parent->getHwnd(), L"You did not save the settings.\nDo you really want to exit?",
				               L"Chatillo", MB_OKCANCEL | MB_ICONQUESTION) == IDOK) {
					DestroyWindow(parent->getHwnd());
				}
				break;
			}
			BringWindowToTop(app->getMainWindow().getHwnd());
			EnableWindow(app->getMainWindow().getHwnd(), TRUE);
			parent->setShowCommand(SW_HIDE);
			break;

		case 6:
			break;
		case 0:
			break;
		default:
			break;
	}
}

void ui::ConfigWindowComponents::onCreate() {
	if (!app->shouldClose()) {
		std::wstring w_ip(gConfig.ip.size(), L'#');
		mbstowcs(&w_ip[0], gConfig.ip.c_str(), gConfig.ip.size());

		((TextField &) get("textFieldName")).setText(gConfig.name);
		((TextField &) get("textFieldIP")).setText(w_ip);
		((TextField &) get("textFieldPort")).setText(std::to_wstring(gConfig.port));
	}

	auto flag = (WPARAM) app->getClient()->connected();

	EnableWindow(((Button &) get("saveButton")).getHwnd(), !flag);

	SendMessage(((TextField &) get("textFieldIP")).getHwnd(), EM_SETREADONLY, flag, 0);
	SendMessage(((TextField &) get("textFieldPort")).getHwnd(), EM_SETREADONLY, flag, 0);
	SendMessage(((TextField &) get("textFieldName")).getHwnd(), EM_SETREADONLY, flag, 0);
}
