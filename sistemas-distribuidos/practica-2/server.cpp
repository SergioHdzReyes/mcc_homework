//
// Created by sergio on 01/10/21.
//

#include "Conexion.h"

int main()
{
    Conexion con(SOCK_STREAM);

    try {
        con.setAsServer();
    } catch (MyException &e) {
        cout << "Excepcion lanzada: " << e.what() << endl;
    } catch (...) {
        cout << "Excepcion DEFAULT";
    }

    return 0;
}