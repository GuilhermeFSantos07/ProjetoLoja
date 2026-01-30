//Proejto Loja
//Autor: Guilherme Farias dos Santos
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class ItemComercial { //Classe abstrata
protected:
    //Atributos para as classes filhas
    int id, qtdVendas; 
    string nome; 
    float preco; 

public:
    //Construtor
    ItemComercial(int id, string nome, float preco, int qtdVendas) 
        : id(id), nome(nome), preco(preco), qtdVendas(qtdVendas) {} 

    virtual ~ItemComercial() {} //Desconstrutor
    
    int getId() const { return id; } //Pega o valor do ID
    int getQtdVendas() const { return qtdVendas; } //Pega o numero de vendas
    string getNome() const { return nome; } //Pega o nome
    float getPreco() const { return preco; } //Pega o preço

    void setQtdVendas(int q) { qtdVendas = q; } //Armazena o numero de vendas
    void setNome(string n) { nome = n; } //Armazena o nome
    void setPreco(float p) { preco = p; } //Armazena o preço

    virtual void exibirDetalhes() const = 0; //Função para exibir os dados
    virtual string getTipo() const = 0; //Função para o tipo (serviço ou produto)
};

class Produto : public ItemComercial { //Classe derivada: Produto
private:
    int estoque; //Variavel para a quantidade de estoque (exclusivo da classe produto)

public:
    //Construtor
    Produto (int id, string nome, float preco, int qtd, int qtdVendas) 
        : ItemComercial (id, nome, preco, qtdVendas), estoque (qtd){}

    int getEstoque() const { return estoque; } //Pega o valor de estoque
    void setEstoque(int qtd) { estoque = qtd; } //Armazena o valor de estoque

    //Função: exibir detalhes dos produtos
    void exibirDetalhes() const override {
        cout << "[PRODUTO] ID: " << id
            << " | Nome: " << nome
            << " | Preco: R$ " << preco
            << " | Estoque: " << estoque << " unid"
            << " | Vendas: " << qtdVendas << endl;
    }

    string getTipo() const override { return "Produto"; } //Pega o tipo (nesse caso Produto)
};

class Servico : public ItemComercial {//Classe derivada: Serviço
public:
    //Construtor
    Servico (int id, string nome, float preco, int qtdVendas) 
        : ItemComercial (id, nome, preco, qtdVendas){}

    //Função: exibir detalhes dos Serviços
    void exibirDetalhes() const override {
        cout << "[SERVICO] ID: " << id
            << " | Nome: " << nome
            << " | Preco: " << preco
            << " | Vendas: " << qtdVendas << endl;
    }

    string getTipo() const override { return "Servico"; } //Pega o tipo (nesse caso serviço)
};

class ControleEstoque { //Classe para controle
private:
    //Usando Vector para armazenamento
    vector<ItemComercial*> listaItens;
    int proxId = 1; //Variavel para os IDs

public: 
    //Função que adiciona um produto
    void adicionarProduto(string nome, float preco, int qtd, int qtdVendas) {
        listaItens.push_back(new Produto(proxId++, nome, preco, qtd, qtdVendas));
        cout << "Produto cadastrado" << endl;
    }
    //Função que adiciona um serviço
    void adicionarServico(string nome, float preco, int qtdVendas) {
        listaItens.push_back(new Servico(proxId++, nome, preco, qtdVendas));
    }
    //Função que mostra todos os itens cadastrados
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
    //Realiza a busca por ID
    ItemComercial* buscaPorId(int id) {
        for (auto* item : listaItens) {
            if (item->getId() == id) {
                return item;
            }
        }
        return nullptr;
    }
    //Função para realizar a venda
    void vendaItem(int id) {
        ItemComercial* item = buscaPorId(id);
        if (item == nullptr) {//Caso não encontre o ID
            cout << "Item nao encontrado" << endl;
            return;
        }

        item->exibirDetalhes(); //exibe os detalhes
        int vendas, qtdVendas;
        qtdVendas = item->getQtdVendas();

        cout << "Numero de vendas: "; //solicita a quantidade vendida
        cin >> vendas;
        qtdVendas += vendas; 
        item->setQtdVendas(qtdVendas);

        //Acessa os metodos que só existem em produtos
        Produto* prod = dynamic_cast<Produto*>(item);

        if (prod != nullptr) { //Se passar é porque é um produto, se não é um serviço
            int estoque = prod->getEstoque();
            if (estoque < vendas) {
                cout << "Estoque insuficiente" << endl;
                return;
            }
            estoque -= vendas; //Retira do estoque
            prod->setEstoque(estoque);
        }

        cout << "Venda relizada" << endl;

    }
    //Função para atualizar o item
    void atualizarItem(int id) {
        ItemComercial* item = buscaPorId(id);//Busca pelo ID
        if (item == nullptr) {//Caso não encontre o ID
            cout << "Item nao encontrado" << endl;
            return;
        }

        cout << "Editando: " << item->getNome() << endl;

        float novoPreco;

        cout << "Novo preco: ";
        cin >> novoPreco; //Solicita o novo preco

        item->setPreco(novoPreco);//Atualiza o preço

        //Acessa os metodos que só existem em produtos
        Produto* prod = dynamic_cast<Produto*>(item);

        if (prod != nullptr) { //Se passar é porque é um produto
            int novaQtd;
            int opcao;

            cout << "Nova quantidade: ";
            cin >> novaQtd;
            //Leve flexibilização
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
    //Função para remover um item
    void removerItem(int id) {
        for (auto it = listaItens.begin(); it != listaItens.end(); ++it) {
            if ((*it)->getId() == id) {//Caso encontre o ID
                delete* it;
                listaItens.erase(it);
                cout << "Item removido" << endl;
                return;
            }
        }
        cout << "Item nao encontrado" << endl;
    }

    //Descontrutor para limpar a memoria
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