# Sistema de Gestão de Vendas e Estoque (C++ Console)

Este é um projeto desenvolvido para praticar conceitos fundamentais de Ciência da Computação, como **Programação Orientada a Objetos (POO)**, **Gerenciamento de Memória** e **Estruturas de Dados** em C++.

O sistema simula o backend de uma loja, permitindo gerenciar produtos físicos (com controle de estoque) e serviços (sem estoque), além de realizar vendas e emitir listagens.

## 🛠️ Tecnologias e Conceitos Utilizados

* **C++ (Standard 11+)**
* **POO Completa:**
    * **Herança:** Classe base `ItemComercial` herdada por `Produto` e `Servico`.
    * **Polimorfismo:** Uso de métodos virtuais para tratar diferentes tipos de objetos na mesma lista.
    * **Classes Abstratas:** A classe base não pode ser instanciada diretamente.
    * **Encapsulamento:** Proteção de dados sensíveis com *getters* e *setters*.
* **Gerenciamento de Memória:** Alocação dinâmica (`new`), liberação manual (`delete`) e tratamento correto de destrutores virtuais para evitar *Memory Leaks*.
* **STL (Standard Template Library):** Uso de `std::vector` para armazenamento dinâmico e `std::string`.
* **RTTI (Run-Time Type Information):** Uso de `dynamic_cast` para identificar tipos específicos de objetos em tempo de execução.

## 📋 Funcionalidades

1.  **Cadastro Híbrido:** Suporta tanto Produtos (com baixa de estoque) quanto Serviços.
2.  **Vendas:**
    * Verifica disponibilidade de estoque para produtos.
    * Incrementa contador de vendas.
3.  **Gestão de Estoque:** Atualização de preços e reposição/retirada de quantidades.
4.  **Listagem:** Exibe todos os itens cadastrados com detalhes polimórficos.
5.  **Remoção:** Exclui itens do sistema liberando a memória corretamente.

## 🚀 Como Rodar

### Pré-requisitos
* Um compilador C++ (GCC, Clang ou MSVC).
