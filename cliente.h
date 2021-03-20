#include <iostream>

using namespace std;

class Cliente {
    private:
        int id;
        string data_nascimento;
        bool validaNome();
    public:
        string nome_cliente;
        int insereCliente();
        bool validate();
};

int Cliente::insereCliente() {
    cout << "Nome completo: " << "\n";
    std::getline(std::cin >> std::ws, this->nome_cliente);

    cout << "Data de nascimento (dia/mes/ano): " << "\n";
    std::getline(std::cin >> std::ws, this->data_nascimento);

    if ( validate() ) {

        return 1;

    } else {
        cout << "Dados invalidos" << "\n";
        // Gera o log
    }
}

bool Cliente::validate() {
    bool valido = true;

    if ( ! validaNome() )
        valido = false;
}

bool Cliente::validaNome() {

    if ( this->nome_cliente.length() > 0 ) {
        return true;
    }

    return false;
}