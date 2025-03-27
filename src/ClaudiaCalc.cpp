#include "ClaudiaCalc.h"

#include <sys/types.h>

#include <iostream>

#include "spdlog/spdlog.h"

using namespace std;

namespace claudia_calc
{

    /*
     * utility functions
     */

    inline bool is_register(char const ch) { return tolower(ch) >= 'a' && ch <= 'd'; }

    inline bool is_register(string const str) { return str.size() != 0 && is_register(str[0]); }

    inline reg_name to_reg_name(char const ch)
    {
        assert(is_register(ch));
        return static_cast<reg_name>(tolower(ch) - 'a');
    }

    inline reg_name to_reg_name(string const str)
    {
        assert(is_register(str));
        return to_reg_name(str[0]);
    }

    inline char to_char(reg_name rn) { return static_cast<char>(rn + 'a'); }

    /*
     * calculator functions
     */

    double registers[4] = {0, 0, 0, 0}; // registers for A, B, C, D

    inline void print_line() { cout << std::string(MENU_WIDTH, '-') << endl; }

    inline void print_title(string const title) { cout << fmt::format("{:^{}}", title, MENU_WIDTH) << endl; }

    void print_menu()
    {
        print_line();
        print_title("ClaudiaCalc");
        print_line();
        cout << "+\tAdd" << endl;
        cout << "-\tSubtract" << endl;
        cout << "*\tMultiply" << endl;
        cout << "/\tDivide" << endl;
        cout << "a-d\tEnter a number or string for A,B,C,D" << endl;
        cout << "1-4\tClear register A,B,C,D" << endl;
        cout << "m\tPrints the menu" << endl;
        cout << "p\tPrints the registers" << endl;
        cout << "q\tQuits the app" << endl;
        print_line();
    }

    // Added print_registers() for printing the values in the Array
    void print_registers()
    {
        cout << "Registers:" << endl;
        cout << "A: " << registers[0] << ", B: " << registers[1]
             << ", C: " << registers[2] << ", D: " << registers[3] << endl;
    }

    void execute(string const cmd)
    {
        // validate command size
        if (cmd.size() == 0)
        {
            spdlog::error("Empty command");
            return;
        }
        // lower annd get first char of command
        char const cmd_ch = std::tolower(cmd[0]);

        // defines the value of a b c d
        if (is_register(cmd_ch))
        {
            cout << "Enter value for a register " << cmd_ch << ": ";
            double value;
            cin >> value;
            registers[to_reg_name(cmd_ch)] = value;
            spdlog::info("Set {} = {}", cmd_ch, value);
            return;
        }

        switch (cmd_ch)
        {
        case '+':
        {
            // ask for left and right registers
            cout << "Enter the left register: ";
            char left_reg;
            cin >> left_reg;
            cout << "Enter the right register: ";
            char right_reg;
            cin >> right_reg;

            // making sure valid register input
            if (is_register(left_reg) && is_register(right_reg))
            {
                double left_val = registers[to_reg_name(left_reg)];
                double right_val = registers[to_reg_name(right_reg)];
                registers[0] = left_val + right_val;
                spdlog::info("A = {} + {} -> A = {}", left_val, right_val, registers[0]);
                cout << "Result: A = " << registers[0] << endl;
            }
            else
            {
                spdlog::error("Invalid register input");
            }
            break;
        }
        case '-':
        {
            // ask for left and right registers
            cout << "Enter the left register: ";
            char left_reg;
            cin >> left_reg;
            cout << "Enter the right register: ";
            char right_reg;
            cin >> right_reg;

            if (is_register(left_reg) && is_register(right_reg))
            {
                double left_val = registers[to_reg_name(left_reg)];
                double right_val = registers[to_reg_name(right_reg)];
                registers[0] = left_val - right_val;
                spdlog::info("A = {} - {} -> A = {}", left_val, right_val, registers[0]);
                cout << "Result: A = " << registers[0] << endl;
            }
            else
            {
                spdlog::error("Invalid register input");
            }
            break;
        }
        case '*':
        {
            // ask for left and right registers
            cout << "Enter the left register: ";
            char left_reg;
            cin >> left_reg;
            cout << "Enter the right register: ";
            char right_reg;
            cin >> right_reg;

            if (is_register(left_reg) && is_register(right_reg))
            {
                double left_val = registers[to_reg_name(left_reg)];
                double right_val = registers[to_reg_name(right_reg)];
                registers[0] = left_val * right_val;
                spdlog::info("A = {} * {} -> A = {}", left_val, right_val, registers[0]);
                cout << "Result: A = " << registers[0] << endl;
            }
            else
            {
                spdlog::error("Invalid register input");
            }
            break;
        }
        case '/':
        {
            // ask for left and right registers
            cout << "Enter the left register: ";
            char left_reg;
            cin >> left_reg;
            cout << "Enter the right register: ";
            char right_reg;
            cin >> right_reg;

            if (is_register(left_reg) && is_register(right_reg))
            {
                double left_val = registers[to_reg_name(left_reg)];
                double right_val = registers[to_reg_name(right_reg)];
                if (right_val != 0)
                {
                    registers[0] = left_val / right_val;
                    spdlog::info("A = {} / {} -> A = {}", left_val, right_val, registers[0]);
                    cout << "Result: A = " << registers[0] << endl;
                }
                else
                {
                    spdlog::error("Division by zero is not allowed");
                }
            }
            else
            {
                spdlog::error("Invalid register input");
            }
            break;
        }
        case '1':
        case '2':
        case '3':
        case '4':
            registers[cmd_ch - '1'] = 0;
            spdlog::info("Cleared register {}", cmd_ch - '1' + 'A');
            break;
        case 'm':
            print_menu();
            break;
        case 'p':
            print_registers();
            break;
        case 'q':
            spdlog::info("Exiting ClaudiaCalc...");
            break;
        default:
            spdlog::error("{} is an unknown command", cmd_ch);
            break;
        }
    }

    // start the calculator
    void start()
    {
        string cmd = "";
        // print menu
        print_menu();
        while (cmd != "q")
        {
            cout << "Enter a command: ";
            cin >> cmd;
            spdlog::debug("cmd={}", cmd);
            execute(cmd);
        }
    }
} // namespace claudia_calc

using namespace claudia_calc;

int main()
{
    spdlog::set_level(spdlog::level::debug);
    start();

    return 0;
}
