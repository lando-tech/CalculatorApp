#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gdkmm/enums.h"
#include "glib.h"
#include "gtkmm/button.h"
#include <gtkmm.h>
#include <string>
#include <vector>

class MainWindow : public Gtk::Window
{
    public:
        MainWindow();
        // Setters
        void setButtonLabels();
        void setEntryText(char x);
        void setEntryOperand(char operand);
        void setEntryOperand(std::string operand);

        // Attach Handlers/Objects
        void attachSignalHandlers();
        void attachToGrid();
        void handleDeletionButton();

        // Handle key presses and events
        bool onKeyPressed(guint keyval, guint, Gdk::ModifierType state);
        void handleEnterPress();

        // Evaluate expression        
        std::vector<std::string> getExpression(const std::string& expr, char delimiter);
        void getResult(char delimiter);

        // Format expression and output
        void printFormat(long double calculation);
        std::string convertToString(long double x);
        std::string convertToString(double x);
        std::string convertToString(float x);
        std::string convertToString(int x); 

        // Clear entry text
        void resetTextBox();
        virtual ~MainWindow();

    private:
        std::vector<Gtk::Button*> m_Buttons;
        std::string divisionSymbol{};
        std::string backSpace{};

    protected:
        Gtk::Box m_VBox;
        Gtk::Entry m_Text_Box;
        Gtk::Grid m_Grid;
        Gtk::Entry m_Text_View;
        // Numbers
        Gtk::Button m_Button0;
        Gtk::Button m_Button1;
        Gtk::Button m_Button2;
        Gtk::Button m_Button3;
        Gtk::Button m_Button4;
        Gtk::Button m_Button5;
        Gtk::Button m_Button6;
        Gtk::Button m_Button7;
        Gtk::Button m_Button8;
        Gtk::Button m_Button9;
        // Operands and Symbols
        Gtk::Button m_Button_Del;
        Gtk::Button m_Button_Period;
        Gtk::Button m_Button_Coma;
        Gtk::Button m_Button_Add;
        Gtk::Button m_Button_Subtract;
        Gtk::Button m_Button_Divide;
        Gtk::Button m_Button_Multiply;
        Gtk::Button m_Button_LParen;
        Gtk::Button m_Button_RParen;
        Gtk::Button m_Button_Equal;
};

#endif
