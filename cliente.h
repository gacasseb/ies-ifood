#include <iostream>

using namespace std;

class Cliente {
    private:
        int id;
        string nome_cliente;
        string data_nascimento;
    public:
        int insereCliente();
};

int Cliente::insereCliente() {
    cout << "Nome completo: " << "\n";
    std::getline(std::cin >> std::ws, this->nome_cliente);

    cout << "Data de nascimento (dia/mes/ano): " << "\n";
    std::getline(std::cin >> std::ws, this->data_nascimento);
}