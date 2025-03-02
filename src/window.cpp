#include "window.h"
#include "calc.h"
#include "gdk/gdkkeysyms.h"
#include "gdkmm/enums.h"
#include "glib.h"
#include "glibmm/ustring.h"
#include "gtkmm/button.h"
#include "gtkmm/entry.h"
#include "sigc++/functors/mem_fun.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

MainWindow::MainWindow() 
{
    set_title("Calculator App");
    set_default_size(300, 300);

    // Unicode Symbol for Backspace and Division
    backSpace = "\u232B";
    divisionSymbol = "\u00F7";

    // Initialize Layout
    m_VBox.set_margin(10);
    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    // Initialize TextBox
    m_Text_Box.set_visibility(true);
    m_Text_Box.set_hexpand(true);
    m_Text_Box.grab_focus();

    // Disable Entry Widget, only use as display
    m_Text_View.set_hexpand(true);
    m_Text_View.set_can_focus(false);

    // Initialize vector of Buttons
    m_Buttons = {
        &m_Button0, &m_Button1, &m_Button2, &m_Button3,
        &m_Button4, &m_Button5, &m_Button6, &m_Button6,
        &m_Button7, &m_Button8, &m_Button9, &m_Button_Add,
        &m_Button_Subtract, &m_Button_Multiply, &m_Button_Divide,
        &m_Button_Coma, &m_Button_LParen, &m_Button_RParen,
        &m_Button_Period, &m_Button_Del,
    };

    // Disable focus on buttons
    for ( auto button : m_Buttons )
    {
        button->set_can_focus(false);
    }

    setButtonLabels();

    // Attatch widgets to Grid Layout
    attachToGrid();

    // Add controller for key press events
    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(sigc::mem_fun(*this, &MainWindow::onKeyPressed), true);
    add_controller(controller);
    attachSignalHandlers();

    // Append Grid to VBox        
    m_VBox.append(m_Grid);
    // Set Vbox as child of window
    set_child(m_VBox);
}

void MainWindow::setButtonLabels()
{
    // Set labels for numbers
    m_Button0.set_label("0");
    m_Button1.set_label("1");
    m_Button2.set_label("2");
    m_Button3.set_label("3");
    m_Button4.set_label("4");
    m_Button5.set_label("5");
    m_Button6.set_label("6");
    m_Button7.set_label("7");
    m_Button8.set_label("8");
    m_Button9.set_label("9");   

    // Set labels for operands and symbols
    m_Button_Add.set_label("+");
    m_Button_Subtract.set_label("-");
    m_Button_Multiply.set_label("x");
    m_Button_Divide.set_label(divisionSymbol);
    m_Button_Del.set_label(backSpace);
    m_Button_LParen.set_label("(");
    m_Button_RParen.set_label(")");
    m_Button_Period.set_label(".");
    m_Button_Equal.set_label("=");
}

void MainWindow::attachToGrid()
{
    m_Grid.attach(m_Text_View, 0, 0, 4, 1);
    m_Grid.attach(m_Text_Box, 0, 1, 4, 1);
    m_Grid.attach(m_Button_Del, 0, 2);
    m_Grid.attach(m_Button_LParen, 1, 2);
    m_Grid.attach(m_Button_RParen, 2, 2);
    m_Grid.attach(m_Button7, 0, 3);
    m_Grid.attach(m_Button8, 1, 3);
    m_Grid.attach(m_Button9, 2, 3);
    m_Grid.attach(m_Button4, 0, 4);
    m_Grid.attach(m_Button5, 1, 4);
    m_Grid.attach(m_Button6, 2, 4);
    m_Grid.attach(m_Button1, 0, 5);
    m_Grid.attach(m_Button2, 1, 5);
    m_Grid.attach(m_Button3, 2, 5);
    m_Grid.attach(m_Button0, 0, 6);
    m_Grid.attach(m_Button_Period, 1, 6);
    m_Grid.attach(m_Button_Add, 3, 3);
    m_Grid.attach(m_Button_Multiply, 3, 4);
    m_Grid.attach(m_Button_Subtract, 3, 5);
    m_Grid.attach(m_Button_Divide, 3, 6);
    m_Grid.attach(m_Button_Equal, 2, 6);
}

void MainWindow::attachSignalHandlers()
{
    // Add handlers for numbers
    m_Button0.signal_clicked().connect([this] {setEntryText('0');});
    m_Button1.signal_clicked().connect([this] {setEntryText('1');});
    m_Button2.signal_clicked().connect([this] {setEntryText('2');});
    m_Button3.signal_clicked().connect([this] {setEntryText('3');});
    m_Button4.signal_clicked().connect([this] {setEntryText('4');});
    m_Button5.signal_clicked().connect([this] {setEntryText('5');});
    m_Button6.signal_clicked().connect([this] {setEntryText('6');});
    m_Button7.signal_clicked().connect([this] {setEntryText('7');});
    m_Button8.signal_clicked().connect([this] {setEntryText('8');});
    m_Button9.signal_clicked().connect([this] {setEntryText('9');});
    m_Button_Period.signal_clicked().connect([this] {setEntryText('.');});

    // Attach handlers for parenthesis and operands
    m_Button_LParen.signal_clicked().connect([this] {setEntryText('(');});
    m_Button_RParen.signal_clicked().connect([this] {setEntryText(')');});
    m_Button_Add.signal_clicked().connect([this] {setEntryOperand('+');});
    m_Button_Subtract.signal_clicked().connect([this] {setEntryOperand('-');});
    m_Button_Multiply.signal_clicked().connect([this] {setEntryOperand('x');});
    m_Button_Divide.signal_clicked().connect([this] {setEntryOperand('/');});

    m_Text_Box.signal_activate().connect([this] {handleEnterPress();});
    m_Button_Equal.signal_clicked().connect([this] {handleEnterPress();});
    m_Button_Del.signal_clicked().connect([this] {handleDeletionButton();});

}

void MainWindow::handleDeletionButton()
{
    // m_Text_Box.grab_focus();
    std::string eText{m_Text_Box.get_text()};

    if ( eText.empty() )
    {
        return;
    }
    else
    {
        eText.pop_back();
        m_Text_Box.set_text(eText);
        m_Text_Box.set_position(m_Text_Box.get_text_length() + 1);
    }
}

void MainWindow::setEntryText(char x)
{
    std::string eText = m_Text_Box.get_text();
    eText.push_back(x);
    m_Text_Box.set_text(eText);
    m_Text_Box.set_position(m_Text_Box.get_text_length() + 1);
}

void MainWindow::setEntryOperand(char operand)
{
    std::string eText = m_Text_Box.get_text();
    if ( eText.empty() )
    {
        eText.push_back(operand);
        m_Text_Box.set_text(eText);
        m_Text_Box.set_position(m_Text_Box.get_text_length() + 1);
    }
    else
    {
        eText.push_back(' ');
        eText.push_back(operand);
        eText.push_back(' ');
        m_Text_Box.set_text(eText);
        m_Text_Box.set_position(m_Text_Box.get_text_length() + 1);
    }
}

bool MainWindow::onKeyPressed(guint keval, guint, Gdk::ModifierType state)
{
    if ( keval == GDK_KEY_Return )
    {
        handleEnterPress();
        return true;
    }
    else if ( keval == GDK_KEY_Delete )
    {
        
        return true;
    }

    return false;
}

void MainWindow::handleEnterPress()
{
    Calculator calc;
    std::string eText = m_Text_Box.get_text();
    for ( char i : m_Text_Box.get_text() )
    {
        if ( i == '+' )
        {
            getResult('+');
        }
        else if ( i == '-' )
        {
            getResult('-');
        }
        else if ( i == '/')
        {
            getResult('/');
        }
        else if ( i == 'x')
        {
            getResult('x');
        }
    }
}

std::vector<std::string> MainWindow::getExpression(const std::string& expr, char delimiter)
{
    std::vector<std::string> tokens{};
    std::stringstream ss{expr};
    std::string token{};

    while ( std::getline(ss, token, delimiter) )
    {
        tokens.push_back(token);
    }

    return tokens;
}

void MainWindow::getResult(char delimiter)
{
    Calculator calc;
    std::vector<std::string> numbers{getExpression(m_Text_Box.get_text(), delimiter)};
    long double numOne = std::stod(numbers[0]);
    long double numTwo = std::stod(numbers[1]);

    if ( delimiter == '+' )
    {
        printFormat(calc.add(numOne, numTwo));
    }
    else if ( delimiter == '-' )
    {
        printFormat(calc.subtract(numOne, numTwo));
    }
    else if ( delimiter == 'x')
    {
        printFormat(calc.multiply(numOne, numTwo));
    }
    else if ( delimiter == '/')
    {
        printFormat(calc.divide(numOne, numTwo));
    }
}

void MainWindow::printFormat(long double calculation)
{
    m_Text_View.set_text(convertToString(calculation));
    resetTextBox();
}

std::string MainWindow::convertToString(long double x)
{
    std::ostringstream converted{};
    converted << x;
    std::string convertedCalculation{converted.str()};
    return m_Text_Box.get_text() + " = " + convertedCalculation; 
}

void MainWindow::resetTextBox()
{
    m_Text_Box.set_text("");
    m_Text_Box.grab_focus();
}

MainWindow::~MainWindow(){}

