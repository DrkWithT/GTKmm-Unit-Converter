#ifndef APPWINDOW_HPP
#define APPWINDOW_HPP

#include <glibmm/ustring.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/dialog.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/checkbutton.h>
#include <gtkmm-3.0/gtkmm/radiobutton.h>
#include <gtkmm-3.0/gtkmm/grid.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/label.h>

#include "utils/converter.hpp"

namespace demoapp::app
{
    using MyConverter = demoapp::utils::LengthConverter;
    using MyEntry = demoapp::utils::LengthEntry;
    using MyUnit = demoapp::utils::LengthUnit;

    class AppWindow : public Gtk::Window
    {
    private:
        Gtk::Grid grid;
        Gtk::Entry start_input;
        Gtk::Entry end_input;
        Gtk::Label start_label;
        Gtk::Label end_label;
        Gtk::Button enter_btn;
        Gtk::Button adjust_btn;

        Gtk::Dialog adjust_dialog; // use get_content_area(), etc.
        Gtk::VBox dbox;
        Gtk::CheckButton start_cbtn;
        Gtk::RadioButton km_rbtn;
        Gtk::RadioButton m_rbtn;
        Gtk::RadioButton cm_rbtn;
        Gtk::RadioButton mm_rbtn;
        Gtk::RadioButton in_rbtn;
        Gtk::RadioButton ft_rbtn;
        Gtk::RadioButton yd_rbtn;
        Gtk::RadioButton mi_rbtn;
        Gtk::Button accept_dbtn;
        Gtk::Button cancel_dbtn;

        MyConverter converter;
        MyUnit start_unit;
        MyUnit end_unit;

        const std::string& getUnitName(MyUnit unit);
        void updateStartUnit(MyUnit start);
        void updateEndUnit(MyUnit end);

    public:
        AppWindow();
        virtual ~AppWindow() = default;

        void onEnterBtnClick();
        void onAdjustBtnClick();
        void onDialogAccept();
        void onDialogCancel();
    };
}

#endif