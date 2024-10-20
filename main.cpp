#include <iostream>
#include <string>
using namespace std;

const int TAMANHO_TABELA_HASH = 10;

struct Autor {
    int matricula;
    string nome;
    int quantdLivros;
};

struct Livro {
    int matricula;
    string titulo;
    int ano;
    string genero;
    Autor autores[3];
    int numAutores = 0;
};

struct Revista {
    int matricula;
    string titulo;
    int ano;
    int edicao;
};

struct Usuario {
    int matricula;
    int devolucao;
    string nome;
    string email;
};

struct Editora {
    int matricula;
    string nome;
    string endereco;
    int anoFundacao;
};

// Estrutura gen�rica para o n� da lista encadeada
template <typename T>
struct No {
    T item;
    No* proximo;
};

// Fun��o de Hash (mapear matr�cula ao �ndice da tabela hash)
int funcaoHash(int matricula) {
    return matricula % TAMANHO_TABELA_HASH;
}

// Tabela Hash gen�rica
template <typename T>
No<T>* tabelaHash[TAMANHO_TABELA_HASH];

// Inicializar a Tabela Hash gen�rica
template <typename T>
void inicializarTabela() {
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        tabelaHash<T>[i] = nullptr;
    }
}

// Fun��o para inserir um novo item na tabela hash gen�rica
template <typename T>
void inserirItem(T novoItem) {
    int indice = funcaoHash(novoItem.matricula);
    No<T>* novoNo = new No<T>;
    novoNo->item = novoItem;
    novoNo->proximo = tabelaHash<T>[indice];
    tabelaHash<T>[indice] = novoNo;
}

// Fun��o para buscar um item na tabela hash gen�rica
template <typename T>
T* buscarItem(int matricula) {
    int indice = funcaoHash(matricula);
    No<T>* aux = tabelaHash<T>[indice];

    while (aux != nullptr) {
        if (aux->item.matricula == matricula) {
            return &aux->item;
        }
        aux = aux->proximo;
    }

    return nullptr;
}

// Fun��o para remover um item da tabela hash gen�rica
template <typename T>
bool removerItem(int matricula) {
    int indice = funcaoHash(matricula);
    No<T>* auxP = tabelaHash<T>[indice];
    No<T>* auxA = nullptr;

    while (auxP != nullptr) {
        if (auxP->item.matricula == matricula) {
            if (auxA == nullptr) {
                tabelaHash<T>[indice] = auxP->proximo;  // Remover do in�cio
            } else {
                auxA->proximo = auxP->proximo;  // Remover do meio/fim
            }
            delete auxP;
            return true;
        }
        auxA = auxP;
        auxP = auxP->proximo;
    }

    return false;
}

// Fun��o para alterar informa��es de um livro
void alterarLivro(int matricula, string novoTitulo, int novoAno, string novoGenero) {
    Livro* livro = buscarItem<Livro>(matricula);  // Busca o livro corretamente
    if (livro != nullptr) {
        livro->titulo = novoTitulo;
        livro->ano = novoAno;
        livro->genero = novoGenero;
        cout << "Livro atualizado com sucesso." << endl;
    } else {
        cout << "Livro n�o encontrado." << endl;
    }
}

// Fun��o para alterar informa��es de uma revista
void alterarRevista(int matricula, string novoTitulo, int novoAno, int novaEdicao) {
    Revista* revista = buscarItem<Revista>(matricula);  // Busca a revista corretamente
    if (revista != nullptr) {
        revista->titulo = novoTitulo;
        revista->ano = novoAno;
        revista->edicao = novaEdicao;
        cout << "Revista atualizada com sucesso." << endl;
    } else {
        cout << "Revista n�o encontrada." << endl;
    }
}

// Fun��o para adicionar autor a um livro
bool adicionarAutorAoLivro(int matriculaLivro, Autor novoAutor) {
    Livro* livro = buscarItem<Livro>(matriculaLivro);  // Corrigir busca de livro
    if (livro != nullptr) {
        if (livro->numAutores < 3) {
            livro->autores[livro->numAutores] = novoAutor;  // Adiciona o autor
            livro->numAutores++;
            cout << "Autor adicionado ao livro." << endl;
            return true;
        } else {
            cout << "Esse livro j� possui 3 autores." << endl;
            return false;
        }
    } else {
        cout << "Livro n�o encontrado." << endl;
        return false;
    }
}

int main() {
    inicializarTabela<Livro>();

    // Inserir Livros
    Livro l1 = {101, "Como ficar rico", 2010, "Auto-Ajuda"};
    Livro l2 = {102, "Di�rio do Mar�al", 2022, "Biografia"};
    Livro l3 = {111, "Bolsonaro: o Anti-Comunista", 2018, "Fic��o"};
    inserirItem(l1);
    inserirItem(l2);
    inserirItem(l3);

    // Buscar um Livro
    Livro* resultado = buscarItem<Livro>(111);  // Deve encontrar l3
    if (resultado != nullptr) {
        cout << "Livro encontrado: " << resultado->titulo << endl;
    } else {
        cout << "Livro n�o encontrado." << endl;
    }

    // Remover um Livro
    bool removido = removerItem<Livro>(101);  // Remover "Como ficar rico"
    if (removido) {
        cout << "Livro removido." << endl;
    } else {
        cout << "Livro n�o encontrado." << endl;
    }

    // Alterar Livro
    alterarLivro(111, "Bolsonaro: Uma historia de Amor e Golden Shower", 2021, "Romance");

    // Adicionar autores ao livro
    Autor a1 = {201, "Bolsonaro", 5};
    Autor a2 = {202, "Mar�al", 61};
    Autor a3 = {203, "Primo-Rico", 6};
    adicionarAutorAoLivro(101, a3);  // N�o deve funcionar, pois foi removido
    adicionarAutorAoLivro(102, a2);
    adicionarAutorAoLivro(111, a1);

    return 0;
}
