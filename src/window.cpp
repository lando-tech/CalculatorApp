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
    
    // Initialize Layout
    m_VBox.set_margin(10);
    m_Grid.set_row_spacing(10);
    m_Grid.set_column_spacing(10);

    // Initialize TextBox
    m_Text_Box.set_visibility(true);
    m_Text_Box.set_hexpand(true);
    m_Text_Box.grab_focus();

    // Initialize vector of Buttons
    m_Buttons = {
        &m_Button0, &m_Button1, &m_Button2, &m_Button3,
        &m_Button4, &m_Button5, &m_Button6, &m_Button6,
        &m_Button7, &m_Button8, &m_Button9, &m_Button_Add,
        &m_Button_Subtract, &m_Button_Multiply, &m_Button_Divide,
        &m_Button_Coma, &m_Button_LParen, &m_Button_RParen,
        &m_Button_Period,
    };

    for ( auto button : m_Buttons )
    {
        button->set_can_focus(false);
    }
    
    setButtonLabels();
    attachToGrid();

    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
        sigc::mem_fun(*this, &MainWindow::onKeyPressed), true);

    add_controller(controller);

    attachSignalHandlers();
        
    m_VBox.append(m_Grid);
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
    m_Button_Divide.set_label("/");
    m_Button_Del.set_label("Bkspc");
    m_Button_LParen.set_label("(");
    m_Button_RParen.set_label(")");
    m_Button_Equal.set_label("=");
}

void MainWindow::attachToGrid()
{
    m_Grid.attach(m_Text_Box, 0, 0, 4, 1);
    m_Grid.attach(m_Button_Del, 0, 1);
    m_Grid.attach(m_Button_LParen, 1, 1);
    m_Grid.attach(m_Button_RParen, 2, 1);
    m_Grid.attach(m_Button7, 0, 2);
    m_Grid.attach(m_Button8, 1, 2);
    m_Grid.attach(m_Button9, 2, 2);
    m_Grid.attach(m_Button4, 0, 3);
    m_Grid.attach(m_Button5, 1, 3);
    m_Grid.attach(m_Button6, 2, 3);
    m_Grid.attach(m_Button1, 0, 4);
    m_Grid.attach(m_Button2, 1, 4);
    m_Grid.attach(m_Button3, 2, 4);
    m_Grid.attach(m_Button0, 0, 5);
    m_Grid.attach(m_Button_Add, 3, 2);
    m_Grid.attach(m_Button_Multiply, 3, 3);
    m_Grid.attach(m_Button_Subtract, 3, 4);
    m_Grid.attach(m_Button_Divide, 3, 5);
    m_Grid.attach(m_Button_Equal, 2, 5);
}

void MainWindow::attachSignalHandlers()
{
    // Add labels for numbers
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
    // Add labels for parenthesis
    m_Button_LParen.signal_clicked().connect([this] {setEntryText('(');});
    m_Button_RParen.signal_clicked().connect([this] {setEntryText(')');});
    // Add labels for operands
    m_Button_Add.signal_clicked().connect([this] {setEntryOperand('+');});
    m_Button_Subtract.signal_clicked().connect([this] {setEntryOperand('-');});
    m_Button_Multiply.signal_clicked().connect([this] {setEntryOperand('x');});
    m_Button_Divide.signal_clicked().connect([this] {setEntryOperand('/');});

    m_Text_Box.signal_activate().connect([this] {handleEnterPress();});
    m_Button_Equal.signal_clicked().connect([this] {handleEnterPress();});

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

    return false;
}

void MainWindow::handleEnterPress()
{
    for ( char i : m_Text_Box.get_text() )
    {
        if ( i == '+' )
        {
            printResult('+');
        }
        else if ( i == '-' )
        {
            printResult('-');
        }
        else if ( i == 'x')
        {
            printResult('x');
        }
        else if ( i == '/')
        {
            printResult('/');
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

void MainWindow::printResult(char delimiter)
{
    Calculator calc;
    std::vector<std::string> numbers{getExpression(m_Text_Box.get_text(), delimiter)};
    double numOne = std::stod(numbers[0]);
    double numTwo = std::stod(numbers[1]);

    if ( delimiter == '+' )
    {
        std::cout << calc.add(numOne, numTwo) << '\n';   
    }
    else if ( delimiter == '-' )
    {
        std::cout << calc.subtract(numOne, numTwo) << '\n';
    }
    else if ( delimiter == 'x')
    {
        std::cout << calc.multiply(numOne, numTwo) << '\n';
    }
    else if ( delimiter == '/')
    {
       std::cout << calc.divide(numOne, numTwo) << '\n'; 
    }
}

MainWindow::~MainWindow(){}

