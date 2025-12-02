# Sistema de Cadastro de Produtos

**Nome:** Thiago Gonçalves De Souza
**Matrícula:** 252014958

## Sobre o Projeto

Este repositório contém a implementação de um sistema de gerenciamento de estoque simples (CRUD), desenvolvido em linguagem C. O projeto foi criado para aplicar e consolidar conhecimentos fundamentais de lógica de programação e estruturação de dados.

O objetivo principal foi criar uma aplicação de console que permitisse a persistência de dados em memória durante a execução, utilizando:

* **Structs:** Para definição da entidade "Produto".
* **Manipulação de Strings:** Uso de funções como `fgets`, `sscanf` e `strncpy`.
* **Ponteiros:** Para manipulação de contadores e passagem de parâmetros.
* **Modularização:** Código dividido em funções específicas (Single Responsibility Principle).
* **Interface de Usuário:** Uso de cores ANSI para melhor experiência no terminal.

## Funcionalidades

* **Cadastrar Produto:** Permite a inserção de novos itens com validação de tipos de dados (Inteiro/Float).
* **Listar Produtos:** Exibe todos os produtos cadastrados com formatação organizada.
* **Consultar por Código:** Busca linear para encontrar um produto específico pelo seu ID único.
* **Editar Produto:** Permite alterar dados de um produto existente (Nome, Preço ou Quantidade), mantendo os dados antigos caso o usuário deixe o campo em branco.
* **Excluir Produto:** Remove um item do vetor e reorganiza a lista para evitar "buracos" no array.

## Tecnologias Utilizadas

* **Linguagem:** C
* **Compilador:** GCC
* **IDE Recomendada:** Visual Studio Code

## Como Compilar e Executar

### Pré-requisitos

Certifique-se de ter um compilador C instalado (como o GCC).
