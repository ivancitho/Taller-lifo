/*
Oscar Andres Mosquera Hinestroza
Ivan Alonso Hernandez Hernandez
*/


#include <iostream>


using namespace std;

struct Vehiculo {
    int tipo;
    int costoParqueada;
    int costoMovimiento;
    int pin;
    struct Vehiculo* sig;
};

int agregarVehiculo(Vehiculo** top, int tipo, int costoParqueada, int costoMovimiento, int pin) {
    Vehiculo* nuevoVehiculo = (Vehiculo*)malloc(sizeof(Vehiculo));
    if(nuevoVehiculo == NULL) {
        return 0;
    }
    nuevoVehiculo->tipo = tipo;
    nuevoVehiculo->costoParqueada = costoParqueada;
    nuevoVehiculo->costoMovimiento = costoMovimiento;
    nuevoVehiculo->pin = pin;
    nuevoVehiculo->sig = NULL;

    if (*top == NULL) {
        *top = nuevoVehiculo;
    } else {
        Vehiculo* aux = *top;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevoVehiculo;
    }
    return 1;
}

int mostrarVehiculos(Vehiculo* top) {
    if (top != NULL) {
        cout << "Vehiculos en el parqueadero:" << endl;
        while (top != NULL) {
            cout<<"----------------------------------"<<endl;
            cout <<" Tipo: " << (top->tipo == 1 ? "Auto" : "Moto") <<endl;
            cout<< " Costo de parqueo: " << top->costoParqueada <<endl;
            cout<< " Costo de movimiento: " << top->costoMovimiento <<endl;
            cout<< " PIN: " << top->pin << endl;
            cout<<"----------------------------------"<<endl;
            top = top->sig;
        }
    } else {
        cout << "El parqueadero esta vacio." << endl;
    }
}

int moverVehiculo(Vehiculo** top, int& dineroParqueo, int& dineroMovimiento) {
    if (*top != NULL) {
        int pin;
        cout << "Ingrese el PIN del vehiculo a mover: ";
        cin >> pin;
        cout<<"----------------------------------"<<endl<<endl;
        cout<<"Vehiculo movido."<<endl<<endl;

        Vehiculo* temp = *top;
        Vehiculo* prev = NULL;
        while (temp != NULL && temp->pin != pin) {
            prev = temp;
            temp = temp->sig;
        }

        if (temp == NULL) {
            cout << "No se encontro un vehiculo con ese PIN en el parqueadero." << endl;
            return 0;
        }

        if (prev == NULL) {
            *top = temp->sig;
        } else {
            prev->sig = temp->sig;
        }

        if (temp->tipo == 1) {
            dineroParqueo += 5000;
            dineroMovimiento += 1000;
        } else if (temp->tipo == 2) {
            dineroParqueo += 2500;
            dineroMovimiento += 500;
        }
        free(temp);
        return 1;
    } else {
        cout << "El parqueadero esta vacio." << endl;
        return 0; 
    }
}

int main() {
    Vehiculo* top = NULL;
    int dineroParqueo = 0;
    int dineroMovimiento = 0;
    int opc;

    do {
        cout<<endl<<"----------------------------------"<<endl;
        cout << "Menu:" << endl;
        cout << "1. Agregar vehiculos." << endl;
        cout << "2. Mostrar vehiculos." << endl;
        cout << "3. Mover vehiculos." << endl;
        cout << "5. Salir" << endl;
        cout<<"----------------------------------"<<endl;
        cout<<"Ingrese una opcion: "; cin >> opc;
        cout<<"----------------------------------"<<endl<<endl;
 
        switch (opc) {
            case 1: {
                int tipo, pin;
                cout << "Ingrese el tipo de vehiculo (1 para auto, 2 para moto): ";
                cin >> tipo;
                if (tipo != 1 && tipo != 2) {
                    cout << "Tipo de vehiculo no valido." << endl;
                    break;
                }
                cout << "Ingrese el PIN del vehiculo: ";
                cin >> pin;
                if (!agregarVehiculo(&top, tipo, (tipo == 1 ? 5000 : 2500), (tipo == 1 ? 1000 : 500), pin)) {
                    cout << "Error: no se pudo agregar el vehiculo." << endl;
                }
                break; 
            }
            case 2: { 
                mostrarVehiculos(top);
                break;
            }
            case 3: {
                if (!moverVehiculo(&top, dineroParqueo, dineroMovimiento)) {
                    cout << "No se pudo mover el vehiculo." << endl;
                }
                break;
            }
            case 5: {
                break;
            }
            default: {
                cout << "Opcion no valida." << endl;
                break;
            }
        }
    } while (opc != 5);

    cout<<"----------------------------------"<<endl;
    cout << "Dinero obtenido por parqueo: " << dineroParqueo << endl;
    cout << "Dinero obtenido por movimientos: " << dineroMovimiento << endl;
    cout<<"----------------------------------"<<endl;
}


