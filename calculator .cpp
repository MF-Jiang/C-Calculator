// 20320552 ssysj1 Shujun JIANG

#include <iostream>
#include <cmath>
#include <stack>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

const long double PI = 3.141592653589793;
const long double e = 2.718281828459045;

// define a BaseCalculator class
class BaseCalculator {
public:
    // define a pure virtual function printResult
    virtual void printResult() = 0;
};

template<typename T>
// define a Calculator class that inherits from BaseCalculator
class Calculator : public BaseCalculator {
private:
    string CalculateMode; // which to calculate
    stack<string> Operations; // store operator
    stack<T> Numbers; // store numbers
    long double result; // cal result

    // First compute ^ and! Then *, /, %, and finally +-, from left to right
    int priority(string Place) {
        // Place: placeholder when reading at operator like +\-\*\/...
        if (Place == "+" || Place == "-") {
            return 1;
        } else if (Place == "*" || Place == "/" || Place == "%") {
            return 2;
        } else if (Place == "^" || Place == "!") {
            return 3;
        } else if (Place == "!" || Place == "abs" || Place == "sin" || Place == "cos" || Place == "tan" ||
                   Place == "asin" || Place == "acos" || Place == "atan" || Place == "exp" || Place == "ln" ||
                   Place == "log") {
            return 4;
        } else {
            return 0;
        }
    }

    // Evaluate the single operators like + and -, which has two elements
    T compute(char operation, T x, T y) {
        if (operation == '+') {
            return x + y;
        } else if (operation == '-') {
            return x - y;
        } else if (operation == '*') {
            return x * y;
        } else if (operation == '/') {
            if (y == 0) {
                cout << "invalid";
                std::exit(EXIT_SUCCESS);
            }
            return x / y;
        } else if (operation == '%') {
            if (y == 0) {
                cout << "invalid";
                std::exit(EXIT_SUCCESS);
            }
            if (fmod(x, 1) != 0 || fmod(y, 1) != 0) {
                cout << "invalid";
                std::exit(EXIT_SUCCESS);
            }
            if (x > 0 && y > 0) {
                return (int) x % (int) y;
            } else if (x < 0 && y > 0) {
                for (int k = 0; k < y; k++) {
                    if (fmod((abs(x) + k), y) == 0) {
                        return k;
                    }
                }
            } else if (x > 0 && y < 0) {
                for (int k = 0; k < abs(y); k++) {
                    if (fmod((abs(x) + k), abs(y)) == 0) {
                        return -k;
                    }
                }
            }
            return (int) x % (int) y;

        } else if (operation == '^') {
            return pow(x, y);
        } else {
            cout << "invalid";
            std::exit(EXIT_SUCCESS);
        }
    }

    // Calculate sin\cos these computations that take up more than one place, and which has one element
    T compute(string operation, T num) {
        if (operation == "abs") {
            return abs(num);
        } else if (operation == "!") {
            long double intpart;
            if (modf(num, &intpart) != 0.0) {
                cout << "invalid";
                std::exit(EXIT_SUCCESS);
            }
            if (num == 1) { return 1; }
            if (num == 0) {
                return 1;
            }
            if (num < 0) {
                cout << "invalid";
                std::exit(EXIT_SUCCESS);
            }
            return num * compute("!", num - 1);
        } else if (operation == "sin") {
            if (sin(num) == 0) {
                return sin(num) + 0.000000000000000001;
            }
            return sin(num);
        } else if (operation == "cos") {
            if (cos(num) == 0) {
                return cos(num) + 0.000000000000000001;
            }
            return cos(num);
        } else if (operation == "tan") {
            if (tan(num) == 0) {
                return tan(num) + 0.000000000000000001;
            }
            return tan(num);
        } else if (operation == "asin") {
            if (asin(num) == 0) {
                return asin(num) + 0.000000000000000001;
            }
            return asin(num);
        } else if (operation == "acos") {
            if (acos(num) == 0) {
                return acos(num) + 0.000000000000000001;
            }
            return acos(num);
        } else if (operation == "atan") {
            if (atan(num) == 0) {
                return atan(num) + 0.000000000000000001;
            }
            return atan(num);
        } else if (operation == "exp") {
            return exp(num);
        } else if (operation == "log") {
            if (num <= 0) {
                cout << "invalid";
                std::exit(EXIT_SUCCESS);
            }
            if (log10(num) == 0) {
                return log10(num) + 0.000000000000000001;
            }
            return log10(num);
        } else if (operation == "ln") {
            if (num <= 0) {
                cout << "invalid";
                std::exit(EXIT_SUCCESS);
            }
            if (log(num) == 0) {
                return log(num) + 0.000000000000000001;
            }
            return log(num);
        } else {
            cout << "invalid";
            std::exit(EXIT_SUCCESS);
        }
    }

    // To determine whether a placeholder is a number, "." also counts
    bool is_digit(char c) {
        return isdigit(c) || c == '.';
    }

public:
    Calculator(const string &string1) : CalculateMode(string1) {}

    // turn calculation into an inverse Polish expression
    string Inverse_Polish() {
        string polish = "";
        int i = 0;
        int len = CalculateMode.length();
        while (i < len) {
            if (is_digit(CalculateMode[i])) {
                if(CalculateMode[i]=='.'){
                    cout << "invalid";
                    std::exit(EXIT_SUCCESS);
                }
                string temp = "";
                while (is_digit(CalculateMode[i])) {
                    temp += CalculateMode[i];
                    i++;
                }
                polish += temp + " ";
            } else if (CalculateMode[i] == 'P' && CalculateMode[i + 1] == 'I') {
                polish += to_string(PI) + " ";
                i += 2;
            } else if (CalculateMode[i] == 'e' && CalculateMode[i + 1] != 'x') {
                polish += to_string(e) + " ";
                i++;
            } else if (CalculateMode[i] == ' ') {
                if (i != 0 && is_digit(CalculateMode[i - 1]) && i + 1 <= len &&
                    is_digit(CalculateMode[i + 1])) {
                    cout << "invalid";
                    std::exit(EXIT_SUCCESS);
                }
                if (i != 0 && isalpha(CalculateMode[i - 1]) && i + 1 <= len &&
                    isalpha(CalculateMode[i + 1])) {
                    cout << "invalid";
                    std::exit(EXIT_SUCCESS);
                }
                i++;
            } else if ((CalculateMode[i] == '+' || CalculateMode[i] == '-') &&
                       (CalculateMode[i - 1] == '(' || i == 0)) {
                if (CalculateMode[i] == '-') {
                    polish += "(-1) ";
                    i++;
                    Operations.push("*");
                } else {
                    // polish += "1 ";
                    // i++;
                    // Operations.push("*");
                    cout << "invalid";
                    std::exit(EXIT_SUCCESS);
                }
            } else if (CalculateMode[i] == '(') {
                Operations.push(std::string(1, CalculateMode[i]));
                i++;
            } else if (CalculateMode[i] == ')') {
                while (!Operations.empty() && Operations.top() != "(") {
                    polish += Operations.top() + " ";
                    Operations.pop();
                }
                if (Operations.empty() || Operations.top() != "(") {
                    cout << "invalid";
                    std::exit(EXIT_SUCCESS);
                }
                Operations.pop();

                if (!Operations.empty()) {
                    string temptop = Operations.top();
                    temptop.erase(remove_if(temptop.begin(), temptop.end(), ::isspace), temptop.end());
                    if (priority(temptop) == 4) {
                        polish += Operations.top() + " ";
                        Operations.pop();
                    }
                }
                i++;
            } else if (isalpha(CalculateMode[i])) {
                string tempoperation = "";
                while (isalpha(CalculateMode[i])) {
                    tempoperation += CalculateMode[i];
                    i++;
                }
                if (tempoperation.length() > 0 &&
                    !(tempoperation == "abs" || tempoperation == "sin" || tempoperation == "cos" ||
                      tempoperation == "tan" || tempoperation == "asin" || tempoperation == "acos" ||
                      tempoperation == "atan" || tempoperation == "exp" || tempoperation == "ln" ||
                      tempoperation == "log")) {
                    cout << "invalid";
                    std::exit(EXIT_SUCCESS);
                }

                while (!Operations.empty() && priority(Operations.top()) >= priority(tempoperation)) {
                    polish += Operations.top() + " ";
                    Operations.pop();
                }
                Operations.push(tempoperation);
            } else {
                if (CalculateMode[i] == '^') {
                    while (!Operations.empty() &&
                           priority(Operations.top()) > priority(std::string(1, CalculateMode[i]))) {
                        polish += Operations.top() + " ";
                        Operations.pop();
                    }
                } else {
                    while (!Operations.empty() &&
                           priority(Operations.top()) >= priority(std::string(1, CalculateMode[i]))) {
                        polish += Operations.top() + " ";
                        Operations.pop();
                    }
                }
                Operations.push(std::string(1, CalculateMode[i]));
                i++;
            }
        }
        while (!Operations.empty()) {
            polish += Operations.top() + " ";
            Operations.pop();
        }
        return polish;
    }

    // define a function to calculate the result from an inverse Polish expression
    T calculate(string Polish) {
        int i = 0;
        int len = Polish.length();
        while (i < len) {
            if (is_digit(Polish[i])) {
                string temp = "";
                int pointcheck = 0;
                while (is_digit(Polish[i])) {
                    if (Polish[i] == '.') {
                        if (!isdigit(Polish[i + 1])) {
                            cout << "invalid";
                            std::exit(EXIT_SUCCESS);
                        }
                        pointcheck += 1;
                        if (pointcheck >= 2) {
                            cout << "invalid";
                            std::exit(EXIT_SUCCESS);
                        }
                    }
                    temp += Polish[i];
                    i++;
                }
                Numbers.push(stod(temp));
            } else if (Polish[i] == ' ') {
                i++;
            } else if (Polish[i] == '(' && Polish[i + 1] == '-' && Polish[i + 2] == '1' && Polish[i + 3] == ')') {
                Numbers.push(-1);
                i += 4;
            } else {
                string op = "";

                while (isalpha(Polish[i])) {
                    op += Polish[i];
                    i++;
                }

                if (op == "") {
                    op = Polish[i];
                    i++;
                }

                if (op == "!" || op == "abs" || op == "sin" || op == "cos" || op == "tan" || op == "asin" ||
                    op == "acos" || op == "atan" || op == "exp" || op == "ln" || op == "log") {
                    if (Numbers.empty()) {
                        cout << "invalid";
                        std::exit(EXIT_SUCCESS);
                    }
                    if (op == "!") {
                        int space_count = 0;
                        for (int j = i; j >= 0; j--) {
                            if (Polish[j] == ' ') {
                                space_count += 1;
                                if (space_count >= 3) {
                                    break;
                                }
                            }
                            if (Polish[j] == '.') {
                                cout << "invalid";
                                std::exit(EXIT_SUCCESS);
                            }
                        }
                    }
                    T x = Numbers.top();
                    Numbers.pop();
                    Numbers.push(compute(op, x));
                } else if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "^") {
                    if (Numbers.empty()) {
                        cout << "invalid";
                        std::exit(EXIT_SUCCESS);
                    }
                    if (op == "%") {
                        int space_count = 0;
                        for (int j = i; j >= 0; j--) {
                            if (Polish[j] == ' ') {
                                space_count += 1;
                                if (space_count >= 4) {
                                    break;
                                }
                            }
                            if (Polish[j] == '.') {
                                cout << "invalid";
                                std::exit(EXIT_SUCCESS);
                            }
                        }
                    }
                    T y = Numbers.top();
                    Numbers.pop();
                    if (Numbers.empty()) {
                        cout << "invalid";
                        std::exit(EXIT_SUCCESS);
                    }
                    T x = Numbers.top();
                    Numbers.pop();
                    Numbers.push(compute(op[0], x, y));

                } else {
                    cout << "invalid";
                    std::exit(EXIT_SUCCESS);
                }
            }
        }
        T output = Numbers.top();
        //cout<<output;
        return output;
    }

    // define a function to run the calculator
    void run() {
        string polish = Inverse_Polish();
        //cout << "Polish is: " << polish ;
        result = calculate(polish);
    }

    // override the printResult function
    void printResult() override {
        long double intpart;
        if (modf(result, &intpart) == 0.0) {
            std::cout << result;
        } else {
            std::cout << fixed << setprecision(8) << result;
        }
    }
};

int main() {
    string calculatormode = "";
    //get input
    std::getline(cin, calculatormode);

    //cout << calculatormode ;
    //Some tests to see if the input is valid
    if (calculatormode.find(' ') != string::npos || calculatormode.empty()) {
        cout << "invalid";
        return 0;
    }
    int len = calculatormode.length() - 1;
    for (int i = 0; i < len; i++) {
        if (((isdigit(calculatormode[i]) || calculatormode[i] == '!') && isalpha(calculatormode[i + 1])) ||
            (calculatormode[i] == '!' &&
             isdigit(calculatormode[i + 1]))) {
            cout << "invalid";
            return 0;
        }
    }

    //put input calculator to cal
    Calculator<long double> cal(calculatormode);
    cal.run();
    cal.printResult();

    return 0;
}