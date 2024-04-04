/**
 * @file main.cpp
 * @author DrkWithT
 * @brief Implements main demo code.
 * @version 0.0.1
 * @date 2024-04-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <gtkmm-3.0/gtkmm/application.h>
#include "app/appwindow.hpp"

using MyAppWindow = demoapp::app::AppWindow;

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "com.derktauto.demoapp.main");

    MyAppWindow window {};

    return app->run(window);
}
