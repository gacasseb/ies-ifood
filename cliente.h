#include <iostream>
#include <string>

using namespace std;

class Cliente {
    private:
        bool validaNome();
    public:
        int id;
        string nome_cliente;
        string data_nascimento;
        int insereCliente();
        bool idExists(Cliente *model_cliente);
        bool validate();
};

int Cliente::insereCliente() {

    string res;
    cout << "Voce deseja inserir o ID? Digite 1 caso queira, 0 caso nao queira (Caso nao, sera inserido automaticamente)" << "\n";
    std::getline(std::cin >> std::ws, res);

    if ( res == "1" ) {
        cout << "Digita um ID usando apenas digitos" << "\n";
        cin >> this->id;
    }

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

bool Cliente::idExists(Cliente *clientes) {

    int i;

    for (i=0; i < 50; i++) {
        if ( this->id == clientes[i].id ) {
            return true;
        }
    }

    return false;
}