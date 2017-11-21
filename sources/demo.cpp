#include "stack.h"
#include <string>
#include <chrono>

void producer(stack<int> &Stack)
{
    for (int i = 0; i < 10; ++i)
    {
        Stack.push(std::rand() % 100);
        std::cout << "\t" << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer(stack<int> &Stack)
{
    for (int i = 0; i < 10; ++i)
    {

        Stack.pop();
        std::cout << "\t" << i << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


int main()
{
    stack<int> _stack;
    /*
    string arg;
    cout << "Add an element: + {element}\nShow the stack: =\nPop the element: -\nShow the last element: ?\nExit the programm: E\n";
    while (arg != "E")
    {
    getline(cin, arg);
    switch (arg[0])
    {
    case '+':
    try
    {
    if (arg[1] != ' ')
    {
    throw 1;
    }
    for (int i = 2; i < arg.length(); i++)
    if (!(arg[i] >= '0' && arg[i] <= '9')) {
    throw 1;

    }
    MOSSIV.push(stoi(arg.substr(2, arg.length() - 2)));


    }
    catch (int i)
    {
    cout << "An error has occurred while reading arguments\n";
    }
    break;
    case '?':
    try
    {
    if (arg[1])
    {
    throw 1;
    }
    MOSSIV.last();

    }
    catch (int i)
    {
    cout << "An error has occurred while reading arguments\n";
    }

    break;
    case '=':
    try
    {
    if (arg[1])
    {
    throw 1;
    }
    print(cout, MOSSIV);
    }
    catch (int i)
    {
    cout << "An error has occurred while reading arguments\n";
    }

    break;
    case '-':
    try
    {
    if (arg[1])
    {
    throw 1;
    }
    MOSSIV.pop();
    }
    catch (int i)
    {
    cout << "An error has occurred while reading arguments\n";
    }


    break;
    }
    }
    */
    std::thread prod1(producer, std::ref(_stack));
    std::thread cons1(consumer, std::ref(_stack));
//	std::thread prod2(producer, std::ref(_stack));
    std::thread cons2(consumer, std::ref(_stack));
    //std::thread prod3(producer, std::ref(_stack));
    std::thread cons3(consumer, std::ref(_stack));
    prod1.join();
    cons1.join();
    //prod2.join();
    cons2.join();
//	prod3.join();
    cons3.join();
    return 0;
}