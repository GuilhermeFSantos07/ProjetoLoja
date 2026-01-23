//Proejto Loja
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class ItemComercial {
protected:
    int id, qtdVendas;
    string nome;
    float preco;

public:
    ItemComercial(int id, string nome, float preco, int qtdVendas) : id(id), nome(nome), preco(preco), qtdVendas(qtdVendas) {}

    virtual ~ItemComercial() {}
    
    int getId() const { return id; }
    int getQtdVendas() const { return qtdVendas; }
    string getNome() const { return nome; }
    float getPreco() const { return preco; }

    void setQtdVendas(int q) { qtdVendas = q; }
    void setNome(string n) { nome = n; }
    void setPreco(float p) { preco = p; }

    virtual void exibirDetalhes() const = 0;
    virtual string getTipo() const = 0;
};

class Produto : public ItemComercial {
private:
    int estoque;

public:
    Produto (int id, string nome, float preco, int qtd, int qtdVendas) : ItemComercial (id, nome, preco, qtdVendas), estoque (qtd){}

    int getEstoque() const { return estoque; }
    void setEstoque(int qtd) { estoque = qtd; }

    void exibirDetalhes() const override {
        cout << "[PRODUTO] ID: " << id
            << " | Nome: " << nome
            << " | Preco: R$ " << preco
            << " | Estoque: " << estoque << " unid"
            << " | Vendas: " << qtdVendas << endl;
    }

    string getTipo() const override { return "Produto"; }
};

class Servico : public ItemComercial {
public:
    Servico (int id, string nome, float preco, int qtdVendas) : ItemComercial (id, nome, preco, qtdVendas){}

    void exibirDetalhes() const override {
        cout << "[SERVICO] ID: " << id
            << " | Nome: " << nome
            << " | Preco: " << preco
            << " | Vendas: " << qtdVendas << endl;
    }

    string getTipo() const override { return "Servico"; }
};

class ControleEstoque {
private:
    vector<ItemComercial*> listaItens;
    int proxId = 1;

public: 
    void adicionarProduto(string nome, float preco, int qtd, int qtdVendas) {
        listaItens.push_back(new Produto(proxId++, nome, preco, qtd, qtdVendas));
        cout << "Produto cadastrado" << endl;
    }

    void adicionarServico(string nome, float preco, int qtdVendas) {
        listaItens.push_back(new Servico(proxId++, nome, preco, qtdVendas));
    }

    void listarTudo() {
        if (listaItens.empty()) {
            cout << "Nenhum item cadastrado" << endl;
            return;
        }
        cout << "\n--- LISTA DE ITENS ---" << endl;
        for (auto* item : listaItens) {
            item->exibirDetalhes();
        }
    }

    ItemComercial* buscaPorId(int id) {
        for (auto* item : listaItens) {
            if (item->getId() == id) {
                return item;
            }
        }
        return nullptr;
    }

    void vendaItem(int id) {
        ItemComercial* item = buscaPorId(id);
        if (item == nullptr) {
            cout << "Item nao encontrado" << endl;
            return;
        }

        item->exibirDetalhes();
        int vendas, qtdVendas;
        qtdVendas = item->getQtdVendas();

        cout << "Numero de vendas: ";
        cin >> vendas;
        qtdVendas += vendas;
        item->setQtdVendas(qtdVendas);

        Produto* prod = dynamic_cast<Produto*>(item);

        if (prod != nullptr) {
            int estoque = prod->getEstoque();
            if (estoque < vendas) {
                cout << "Estoque insuficiente" << endl;
                return;
            }
            estoque -= vendas;
            prod->setEstoque(estoque);
        }

        cout << "Venda relizada" << endl;

    }

    void atualizarItem(int id) {
        ItemComercial* item = buscaPorId(id);
        if (item == nullptr) {
            cout << "Item nao encontrado" << endl;
            return;
        }

        cout << "Editando: " << item->getNome() << endl;

        float novoPreco;

        cout << "Novo preco: ";
        cin >> novoPreco;

        item->setPreco(novoPreco);

        Produto* prod = dynamic_cast<Produto*>(item);

        if (prod != nullptr) {
            int novaQtd;
            int opcao;

            cout << "Nova quantidade: ";
            cin >> novaQtd;
            cout << "1. Atualizar" << endl;
            cout << "2. Adicionar" << endl;
            cout << "3. Remover" << endl;
            cout << "Selecione a opcao: ";
            cin >> opcao;
            switch (opcao){
                case 1: {
                    prod->setEstoque(novaQtd);
                    break;
                }
                case 2: {
                    int estoque;
                    estoque = prod->getEstoque();
                    estoque += novaQtd;
                    prod->setEstoque(estoque);
                    break;
                }
                case 3: {
                    int estoque;
                    estoque = prod->getEstoque();
                    estoque -= novaQtd;
                    prod->setEstoque(estoque);
                    break;
                }
                default:
                    cout << "Opcao invalida" << endl;
                    break;
                }
            
        }

        cout << "Produto atualizado" << endl;
    }

    void removerItem(int id) {
        for (auto it = listaItens.begin(); it != listaItens.end(); ++it) {
            if ((*it)->getId() == id) {
                delete* it;
                listaItens.erase(it);
                cout << "Item removido" << endl;
                return;
            }
        }
        cout << "Item nao encontrado" << endl;
    }

    ~ControleEstoque() {
        for (auto* item : listaItens) {
            delete item;
        }
        listaItens.clear();
    }
};

void mostrarMenu() {
    cout << "\n=== SISTEMA DA LOJA ===" << endl;
    cout << "1. Realizar venda" << endl;
    cout << "2. Cadastro de produtos" << endl;
    cout << "3. Listar tudo" << endl;
    cout << "4. Atualizar produto" << endl;
    cout << "5. Remover produto" << endl;
    cout << "0. Sair" << endl;
    cout << "Digite a opcao: ";
}

int main()
{
    ControleEstoque sistema;
    int opcao;

    do {
        mostrarMenu();
        cin >> opcao;

        switch (opcao) {
            case 1: {
                int id;
                cout << "Digite o ID do produto: ";
                cin >> id;
                sistema.vendaItem(id);
                break;
            }
            case 2: {
                int op;
                cout << "1. Cadastrar produto" << endl;
                cout << "2. Cadastrar servico" << endl;
                cout << "Digite a opcao: ";
                cin >> op;

                switch (op) {
                    case 1: {
                        string nome;
                        float preco;
                        int qtd;

                        cout << "Nome do produto: ";
                        cin.ignore();
                        getline(cin, nome);

                        cout << "Digite o preco: ";
                        cin >> preco;

                        cout << "Digite a quantidade: ";
                        cin >> qtd;

                        sistema.adicionarProduto(nome, preco, qtd, 0);
                        break;
                    }
                    case 2: {
                        string nome;
                        float preco;

                        cout << "Digite o nome: ";
                        cin.ignore();
                        getline(cin, nome);

                        cout << "Digite o preco: ";
                        cin >> preco;

                        sistema.adicionarServico(nome, preco, 0);
                        break;
                    }
                    default:
                        cout << "Opcao invalida" << endl;
                        break;
                }
                break;
            }
            case 3: {
                sistema.listarTudo();
                break;
            }
            case 4: {
                int id;
                cout << "Digite o ID para editar: ";
                cin >> id;
                sistema.atualizarItem(id);
                break;
            }
            case 5: {
                int id;
                cout << "Digite o ID para remover: ";
                cin >> id;
                sistema.removerItem(id);
                break;
            }
            case 0:
                cout << "Encerrando" << endl;
                break;
            default:
                cout << "Opcao Invalida" << endl;
        }
    } while (opcao != 0);
    return 0;
}