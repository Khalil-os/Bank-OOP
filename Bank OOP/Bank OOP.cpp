#include <iostream>
#include "clsLoginScreen.h"

// Important : ( User : Admin / Password : 1234 )

using namespace std;

int main()
{
    while (ON)
    {
        if (!clsLoginScreen::ShowLoginScreen())
            break;
    }
    cout << endl << endl;
    cout << setw(37) << left << "";
    system("pause");
    return 0;
    
}