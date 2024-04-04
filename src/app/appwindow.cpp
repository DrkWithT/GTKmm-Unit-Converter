/**
 * @file appwindow.cpp
 * @author DrkWithT
 * @brief Implements app window class.
 * @date 2024-04-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <functional>
#include <initializer_list>
#include "app/appwindow.hpp"

namespace demoapp::app
{
    std::initializer_list<MyEntry> metrics = {
        {"km", MyUnit::metric_km, 1000.0},
        {"m", MyUnit::metric_m, 1.0},
        {"cm", MyUnit::metric_cm, 0.01},
        {"mm", MyUnit::metric_mm, 0.001}
    };

    std::initializer_list<MyEntry> imperials = {
        {"in.", MyUnit::imperial_in, 0.0833},
        {"ft", MyUnit::imperial_foot, 1.0},
        {"yd", MyUnit::imperial_yard, 3.0},
        {"mi", MyUnit::imperial_mile, 5280.0}
    };

    const std::string& AppWindow::getUnitName(MyUnit unit)
    {
        return converter.getUnitEntry(unit).viewName();
    }

    void AppWindow::updateStartUnit(MyUnit start)
    {
        start_unit = start;
        start_label.set_text(getUnitName(start_unit));
    }

    void AppWindow::updateEndUnit(MyUnit end)
    {
        end_unit = end;
        end_label.set_text(getUnitName(end_unit));
    }

    AppWindow::AppWindow()
    : Gtk::Window(), grid {}, start_input {}, end_input {}, start_label {"m"}, end_label {"m"}, enter_btn {"Convert"}, adjust_btn {"Adjust"}, adjust_dialog {"Adjust Units", true}, dbox {Gtk::Orientation::ORIENTATION_VERTICAL}, start_cbtn {"Start?"}, km_rbtn {"km"}, m_rbtn {"m"}, cm_rbtn {"cm"}, mm_rbtn {"mm"}, in_rbtn {"in."}, ft_rbtn {"ft"}, yd_rbtn {"yd"}, mi_rbtn {"mi"}, accept_dbtn {"Apply"}, cancel_dbtn {"Cancel"}, converter {metrics, imperials}, start_unit {MyUnit::metric_m}, end_unit {MyUnit::metric_m}
    {
        start_input.set_text("0.0");
        end_input.set_text("0.0");

        yd_rbtn.join_group(mi_rbtn);
        ft_rbtn.join_group(yd_rbtn);
        in_rbtn.join_group(ft_rbtn);
        mm_rbtn.join_group(in_rbtn);
        cm_rbtn.join_group(mm_rbtn);
        m_rbtn.join_group(cm_rbtn);
        m_rbtn.set_active();
        km_rbtn.join_group(m_rbtn);

        grid.set_row_homogeneous(true);
        grid.set_column_homogeneous(true);
        grid.attach(start_label, 0, 0);
        grid.attach(start_input, 1, 0);
        grid.attach(end_label, 0, 1);
        grid.attach(end_input, 1, 1);
        grid.attach(enter_btn, 0, 2);
        grid.attach(adjust_btn, 1, 2);

        dbox.add(start_cbtn);
        dbox.add(km_rbtn);
        dbox.add(m_rbtn);
        dbox.add(cm_rbtn);
        dbox.add(mm_rbtn);
        dbox.add(in_rbtn);
        dbox.add(ft_rbtn);
        dbox.add(yd_rbtn);
        dbox.add(mi_rbtn);

        Gtk::Box dialog_hbox {Gtk::Orientation::ORIENTATION_HORIZONTAL, 16};
        dialog_hbox.add(accept_dbtn);
        dialog_hbox.add(cancel_dbtn);
        dbox.add(dialog_hbox);
        adjust_dialog.add(dbox);

        enter_btn.signal_clicked().connect(sigc::mem_fun(*this, &AppWindow::onEnterBtnClick));
        adjust_btn.signal_clicked().connect(sigc::mem_fun(*this, &AppWindow::onAdjustBtnClick));
        accept_dbtn.signal_clicked().connect(sigc::mem_fun(*this, &AppWindow::onDialogAccept));
        cancel_dbtn.signal_clicked().connect(sigc::mem_fun(*this, &AppWindow::onDialogCancel));

        show_all_children();
    }

    void AppWindow::onEnterBtnClick()
    {
        double start_num = std::atof(start_input.get_text().c_str());
        double result_num = converter.convertLength(start_num, start_unit, end_unit);

        end_input.set_text(std::to_string(result_num));
    }

    void AppWindow::onAdjustBtnClick()
    {
        adjust_dialog.show();
    }

    void AppWindow::onDialogAccept()
    {
        bool adjust_start_unit = start_cbtn.get_active();
        MyUnit unit_code = MyUnit::metric_m;

        if (km_rbtn.get_active())
            unit_code = MyUnit::metric_km;
        else if (m_rbtn.get_active())
            unit_code = MyUnit::metric_m;
        else if (cm_rbtn.get_active())
            unit_code = MyUnit::metric_cm;
        else if (mm_rbtn.get_active())
            unit_code = MyUnit::metric_mm;
        else if (in_rbtn.get_active())
            unit_code = MyUnit::imperial_in;
        else if (ft_rbtn.get_active())
            unit_code = MyUnit::imperial_foot;
        else if (yd_rbtn.get_active())
            unit_code = MyUnit::imperial_yard;
        else if (mi_rbtn.get_active())
            unit_code = MyUnit::imperial_mile;

        if (adjust_start_unit)
            updateStartUnit(unit_code);
        else
            updateEndUnit(unit_code);
    }

    void AppWindow::onDialogCancel()
    {
        adjust_dialog.hide();
    }
}
