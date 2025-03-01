/* #include <iostream> */
/* #include "calc.h" */
#include "window.h"
#include <gtkmm/application.h>


int main(int argc, char* argv[])
{
    auto app { Gtk::Application::create("org.gtkmm.examples.base")};
    /* Calculator calc; */
    /* std::cout << calc.add(25.0, 25.0)  << '\n'; */
    return app->make_window_and_run<MainWindow>(argc, argv);
}

