#include <iostream>
#include <string>
#include <fstream>

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
  string editora;
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
  int livrosEmprestados[10];
  int numLivrosEmprestados = 0;
};

struct Editora {
  int matricula;
  string nome;
  string endereco;
  int anoFundacao;
};

template < typename T >
struct No {
    T item;
    No * proximo;
};

int funcaoHash(int matricula) {
    return matricula % TAMANHO_TABELA_HASH;
}

template < typename T >
No < T > * tabelaHash[TAMANHO_TABELA_HASH];

template < typename T >
void inicializarTabela() {
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
      tabelaHash < T > [i] = nullptr;
    }
}

// Função para inserir um novo item
template < typename T >
void inserirItem(T novoItem) {
    int indice = funcaoHash(novoItem.matricula);
    No < T > * novoNo = new No < T > ;
    novoNo -> item = novoItem;
    novoNo -> proximo = tabelaHash < T > [indice];
    tabelaHash < T > [indice] = novoNo;
}

// Função para buscar um item pela matricula
template < typename T >
T * buscarItem(int matricula) {
    int indice = funcaoHash(matricula);
    No < T > * aux = tabelaHash < T > [indice];

    while (aux != nullptr) {
        if (aux -> item.matricula == matricula) {
            return & aux -> item;
        }
        aux = aux -> proximo;
    }

    return nullptr;
  }

// Função para remover um item
template < typename T >
bool removerItem(int matricula) {
    int indice = funcaoHash(matricula);
    No < T > * auxP = tabelaHash < T > [indice];
    No < T > * auxA = nullptr;

    while (auxP != nullptr) {
        if (auxP -> item.matricula == matricula) {
            if (auxA == nullptr) {
                tabelaHash < T > [indice] = auxP -> proximo;
            } else {
                auxA -> proximo = auxP -> proximo;
            }
            delete auxP;
            return true;
      }
      auxA = auxP;
      auxP = auxP -> proximo;
    }

    return false;
  }

// Função para alterar informações
void alterarLivro(int matricula, string novoTitulo, int novoAno, string novoGenero) {
    Livro * livro = buscarItem < Livro > (matricula);
    if (livro != nullptr) {
        livro -> titulo = novoTitulo;
        livro -> ano = novoAno;
        livro -> genero = novoGenero;
        cout << "Livro atualizado com sucesso." << endl;
    } else {
    cout << "Livro nao encontrado." << endl;
  }
}

// Função para alterar informações
void alterarRevista(int matricula, string novoTitulo, int novoAno, int novaEdicao) {
    Revista * revista = buscarItem < Revista > (matricula);
    if (revista != nullptr) {
        revista -> titulo = novoTitulo;
        revista -> ano = novoAno;
        revista -> edicao = novaEdicao;
        cout << "Revista atualizada com sucesso." << endl;
    } else {
        cout << "Revista nao encontrada." << endl;
    }
}

// Função para adicionar autor a um livro
bool adicionarAutorAoLivro(int matriculaLivro, Autor novoAutor) {
    Livro * livro = buscarItem < Livro > (matriculaLivro);
    if (livro != nullptr) {
        if (livro -> numAutores < 3) {
            livro -> autores[livro -> numAutores] = novoAutor;
            livro -> numAutores++;
            cout << "Autor adicionado ao livro." << endl;
            return true;
        } else {
            cout << "Esse livro ja possui 3 autores." << endl;
            return false;
        }
    } else {
        cout << "Livro nao encontrado." << endl;
        return false;
    }
}

void listarLivros() {
    cout << "Lista de Livros:" << endl;
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            cout << "Matricula: " << aux -> item.matricula << ", Titulo: " << aux -> item.titulo << endl;
            aux = aux -> proximo;
        }
    }
}

//Pesquisar pelo Titulo
void pesquisarLivroTitulo(string & titulo) {
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            if (aux -> item.titulo == titulo) {
                cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << " autor: " << aux -> item.autores << endl;
                return;
            }
            aux = aux -> proximo;
        }
    }
    cout << "Livro nao encontrado." << endl;
}

//Pesquisar pela Matricula
void pesquisarMatricula(int matricula) {
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            if (aux -> item.matricula == matricula) {
                cout << "Livro encontrado: " << aux -> item.titulo << endl;
                return;
            }
            aux = aux -> proximo;
        }
    }
    cout << "Livro nao encontrado." << endl;
}

//Pesquisar pelo Autor
void pesquisarAutor(string autor) {
    bool encontrado = false;
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            for (int j = 0; j < aux -> item.numAutores; j++) {
                if (aux -> item.autores[j].nome == autor) {
                    cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << endl;
                    encontrado = true;
                    break;
                }
            }
            aux = aux -> proximo;
        }
    }
    if (!encontrado) {
        cout << "Autor nao encontrado." << endl;
    }
}

//Pesquisar pela Editora
void pesquisarEditora(string editora) {
    bool encontrado = false;
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            if (aux -> item.editora == editora) {
                cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << endl;
                encontrado = true;
            }
            aux = aux -> proximo;
        }
    }
    if (!encontrado) {
        cout << "Editora nao encontrada." << endl;
    }
}

//Pesquisar pelo Genero
void pesquisarGenero(string genero) {
    bool encontrado = false;
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            if (aux -> item.genero == genero) {
                cout << "Livro encontrado: " << aux -> item.titulo <<
                ", Ano: " << aux -> item.ano <<
                ", Matricula: " << aux -> item.matricula << endl;
                encontrado = true;
            }
        aux = aux -> proximo;
        }
    }
    if (!encontrado) {
        cout << "Nenhum livro encontrado com o genero: " << genero << endl;
    }
}

//Cadastrando Autores
void cadastrarAutor() {
      Autor novoAutor;
      cout << "Digite a matricula do autor: ";
      cin >> novoAutor.matricula;
      cin.ignore();
      cout << "Digite o nome do autor: ";
      getline(cin, novoAutor.nome);
      cout << "Digite a quantidade de livros do autor: ";
      cin >> novoAutor.quantdLivros;

      inserirItem(novoAutor);
      cout << "Autor cadastrado com sucesso!" << endl;
}

//Cadastrando Livro
void cadastrarLivro() {
      Livro novoLivro;
      cout << "Digite a matricula do livro: ";
      cin >> novoLivro.matricula;
      cin.ignore();

      cout << "Digite o titulo do livro: ";
      getline(cin, novoLivro.titulo);

      cout << "Digite o ano de publicação: ";
      cin >> novoLivro.ano;
      cin.ignore();

      cout << "Digite o genero do livro: ";
      getline(cin, novoLivro.genero);

      cout << "Digite o nome da editora: ";
      getline(cin, novoLivro.editora);

      novoLivro.numAutores = 0;

      inserirItem(novoLivro);
      cout << "Livro cadastrado com sucesso!" << endl;
}

void cadastrarRevista() {
      Revista novaRevista;
      cout << "Digite a matricula da revista: ";
      cin >> novaRevista.matricula;
      cin.ignore();

      cout << "Digite o titulo da revista: ";
      getline(cin, novaRevista.titulo);

      cout << "Digite o ano de publicação: ";
      cin >> novaRevista.ano;

      cout << "Digite a edição da revista: ";
      cin >> novaRevista.edicao;

      inserirItem(novaRevista);
      cout << "Revista cadastrada com sucesso!" << endl;
}

void cadastrarEditora() {
      Editora novaEditora;
      cout << "Digite a matricula da editora: ";
      cin >> novaEditora.matricula;
      cin.ignore();

      cout << "Digite o nome da editora: ";
      getline(cin, novaEditora.nome);

      cout << "Digite o endereco da editora: ";
      getline(cin, novaEditora.endereco);

      cout << "Digite o ano de fundacao da editora: ";
      cin >> novaEditora.anoFundacao;

      inserirItem(novaEditora);
      cout << "Editora cadastrada com sucesso!" << endl;
}

void cadastrarUsuario() {
      Usuario novoUsuario;
      cout << "Digite a matricula do usuario: ";
      cin >> novoUsuario.matricula;
      cin.ignore();

      cout << "Digite o nome do usuario: ";
      getline(cin, novoUsuario.nome);

      cout << "Digite o email do usuario: ";
      getline(cin, novoUsuario.email);

      cout << "Digite o tempo de devolucao (dias): ";
      cin >> novoUsuario.devolucao;

      novoUsuario.numLivrosEmprestados = 0;

      inserirItem(novoUsuario);
      cout << "Usuario cadastrado com sucesso!" << endl;
}

bool removerAutorDoLivro(int matriculaLivro, int matriculaAutor) {
    Livro * livro = buscarItem < Livro > (matriculaLivro);
    if (livro != nullptr) {
        for (int i = 0; i < livro -> numAutores; ++i) {
            if (livro -> autores[i].matricula == matriculaAutor) {
                for (int j = i; j < livro -> numAutores - 1; ++j) {
                    livro -> autores[j] = livro -> autores[j + 1];
                }
                livro -> numAutores--;
                cout << "Autor removido do livro." << endl;
                return true;
            }
        }
        cout << "Autor nao encontrado no livro." << endl;
    } else {
        cout << "Livro nao encontrado." << endl;
    }
    return false;
}

bool removerEditora(int matricula) {
    int indice = funcaoHash(matricula);
    No < Editora > * auxP = tabelaHash < Editora > [indice];
    No < Editora > * auxA = nullptr;

    while (auxP != nullptr) {
        if (auxP -> item.matricula == matricula) {
            if (auxA == nullptr) {
                tabelaHash < Editora > [indice] = auxP -> proximo;
            } else {
                auxA -> proximo = auxP -> proximo;
            }
            delete auxP;
            cout << "Editora removida com sucesso." << endl;
            return true;
        }
        auxA = auxP;
        auxP = auxP -> proximo;
    }

    cout << "Editora nao encontrada." << endl;
    return false;
}

void alterarAutor(int matricula, string novoNome, int novaQuantidadeLivros) {
    Autor * autor = buscarItem < Autor > (matricula);
    if (autor != nullptr) {
        autor -> nome = novoNome;
        autor -> quantdLivros = novaQuantidadeLivros;
        cout << "Autor atualizado com sucesso." << endl;
    } else {
        cout << "Autor nao encontrado." << endl;
    }
}

void alterarEditora(int matricula) {
    Editora * editora = buscarItem < Editora > (matricula);
    if (editora != nullptr) {
        cout << "Novo nome (atual: " << editora -> nome << "): ";
        string novoNome;
        getline(cin, novoNome);
        if (!novoNome.empty()) editora -> nome = novoNome;

        cout << "Novo endereco (atual: " << editora -> endereco << "): ";
        string novoEndereco;
        getline(cin, novoEndereco);
        if (!novoEndereco.empty()) editora -> endereco = novoEndereco;

        cout << "Novo ano de fundacao (atual: " << editora -> anoFundacao << "): ";
        int novoAnoFundacao;
        cin >> novoAnoFundacao;
        if (novoAnoFundacao > 0) editora -> anoFundacao = novoAnoFundacao;
        cin.ignore();

        cout << "Editora atualizada com sucesso." << endl;
    } else {
        cout << "Editora nao encontrada." << endl;
    }
}

void relatorioLivrosPorAutor(string autorNome) {
    cout << "Relatorio de Livros por Autor: " << autorNome << endl;
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            for (int j = 0; j < aux -> item.numAutores; j++) {
                if (aux -> item.autores[j].nome == autorNome) {
                    cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << endl;
                }
            }
        aux = aux -> proximo;
        }
    }
}

void relatorioLivrosPorEditora(string editoraNome) {
    cout << "Relatorio de Livros por Editora: " << editoraNome << endl;
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            if (aux -> item.editora == editoraNome) {
                cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << endl;
            }
        aux = aux -> proximo;
        }
    }
}

void relatorioLivrosPorGenero(string genero) {
    cout << "Relatorio de Livros por Gênero: " << genero << endl;
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            if (aux -> item.genero == genero) {
                cout << "Livro encontrado: " << aux -> item.titulo << ", Ano: " << aux -> item.ano << ", Matricula: " << aux -> item.matricula << endl;
            }
        aux = aux -> proximo;
        }
    }
}

void historicoRetiradas(int matriculaUsuario) {
    Usuario * usuario = buscarItem < Usuario > (matriculaUsuario);
    if (usuario != nullptr) {
        cout << "Historico de Retiradas para o usuario: " << usuario -> nome << endl;
        for (int i = 0; i < usuario -> numLivrosEmprestados; i++) {
            Livro * livro = buscarItem < Livro > (usuario -> livrosEmprestados[i]);
            if (livro != nullptr) {
                cout << "Livro: " << livro -> titulo << ", Ano: " << livro -> ano << ", Matricula: " << livro -> matricula << endl;
            }
        }
    } else {
        cout << "Usuário nao encontrado." << endl;
    }
}

void relatorioLivrosAtrasados() {
    cout << "Relatorio de Livros em Atraso:" << endl;
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Usuario > * auxUsuario = tabelaHash < Usuario > [i];
        while (auxUsuario != nullptr) {
            for (int j = 0; j < auxUsuario -> item.numLivrosEmprestados; j++) {
                if (auxUsuario -> item.devolucao < 0) {
                    cout << "Livro matricula: " << auxUsuario -> item.livrosEmprestados[j] << " esta atrasado." << endl;
                }
            }
        auxUsuario = auxUsuario -> proximo;
        }
    }
}

void salvarAutores() {
    ofstream arquivo("autores.txt");
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Autor > * aux = tabelaHash < Autor > [i];
        while (aux != nullptr) {
            arquivo << aux -> item.matricula << ";" << endl;
            arquivo << aux -> item.nome << ";" << endl;
            arquivo << aux -> item.quantdLivros << endl;
            aux = aux -> proximo;
        }
    }
    arquivo.close();
}

void salvarLivros() {
    ofstream arquivo("livros.txt");
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Livro > * aux = tabelaHash < Livro > [i];
        while (aux != nullptr) {
            arquivo << aux -> item.matricula << ";" << endl;
            arquivo << aux -> item.titulo << ";" << endl;
            arquivo << aux -> item.ano << ";" << endl;
            arquivo << aux -> item.genero << ";" << endl;
            arquivo << aux -> item.editora << ";" << endl;
            arquivo << aux -> item.numAutores;
            for (int j = 0; j < aux -> item.numAutores; j++) {
                arquivo << ";" << aux -> item.autores[j].matricula << endl;
                arquivo << ";" << aux -> item.autores[j].nome << endl;
                arquivo << ";" << aux -> item.autores[j].quantdLivros;
            }
            arquivo << endl;
            aux = aux -> proximo;
        }
    }
arquivo.close();
}

void salvarRevistas() {
    ofstream arquivo("revistas.txt");
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Revista > * aux = tabelaHash < Revista > [i];
        while (aux != nullptr) {
            arquivo << aux -> item.matricula << ";" << endl;
            arquivo << aux -> item.titulo << ";" << endl;
            arquivo << aux -> item.ano << ";" << endl;
            arquivo << aux -> item.edicao << endl;
            aux = aux -> proximo;
        }
    }
    arquivo.close();
}

void salvarUsuarios() {
    ofstream arquivo("usuarios.txt");
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Usuario > * aux = tabelaHash < Usuario > [i];
        while (aux != nullptr) {
            arquivo << aux -> item.matricula << ";" << endl;
            arquivo << aux -> item.nome << ";" << endl;
            arquivo << aux -> item.email << ";" << endl;
            arquivo << aux -> item.devolucao << ";" << endl;
            arquivo << aux -> item.numLivrosEmprestados << endl;
            for (int j = 0; j < aux -> item.numLivrosEmprestados; j++) {
                arquivo << ";" << aux -> item.livrosEmprestados[j] << endl;
            }
            arquivo << endl;
            aux = aux -> proximo;
        }
    }
    arquivo.close();
}

void salvarEditoras() {
    ofstream arquivo("editoras.txt");
    for (int i = 0; i < TAMANHO_TABELA_HASH; i++) {
        No < Editora > * aux = tabelaHash < Editora > [i];
        while (aux != nullptr) {
            arquivo << aux -> item.matricula << ";" << endl;
            arquivo << aux -> item.nome << ";" << endl;
            arquivo << aux -> item.endereco << ";" << endl;
            arquivo << aux -> item.anoFundacao << endl;
            aux = aux -> proximo;
        }
    }
    arquivo.close();
}

bool usuarioExiste(int matricula) {
    ifstream arquivo("usuarios.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usuários." << endl;
        return false;
    }

    int matriculaUsuario;
    string nome, email;
    int devolucao, numLivrosEmprestados;

    while (arquivo >> matriculaUsuario) {
        arquivo.ignore(); // Ignora o delimitador
        getline(arquivo, nome, ';');
        getline(arquivo, email, ';');
        arquivo >> devolucao >> numLivrosEmprestados;

        if (matriculaUsuario == matricula) {
            arquivo.close();
            return true; // Usuário encontrado
        }
    }

    arquivo.close();
    cout << "Usuario nao encontrado." << endl;
    return false;
}

bool livroExiste(int matricula) {
    ifstream arquivo("livros.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de livros." << endl;
        return false;
    }

    int matriculaLivro;
    string titulo;
    int ano;
    string genero;
    string editora;
    int numAutores;

    while (arquivo >> matriculaLivro) {
        arquivo.ignore(); // Ignora o delimitador
        getline(arquivo, titulo, ';');
        arquivo >> ano;
        arquivo.ignore(); // Ignora o delimitador
        getline(arquivo, genero, ';');
        getline(arquivo, editora, ';');
        arquivo >> numAutores;

        if (matriculaLivro == matricula) {
            arquivo.close();
            return true; // Livro encontrado
        }

        // Ignora autores
        for (int i = 0; i < numAutores; i++) {
            int matriculaAutor;
            string nomeAutor;
            int quantdLivros;
            arquivo >> matriculaAutor;
            arquivo.ignore();
            getline(arquivo, nomeAutor, ';');
            arquivo >> quantdLivros;
        }
    }

    arquivo.close();
    return false; // Livro não encontrado
}
void emprestarLivro(int matriculaUsuario, int matriculaLivro) {
    if (!usuarioExiste(matriculaUsuario)) {
        cout << "Usuário não encontrado." << endl;
        return;
    }

    if (!livroExiste(matriculaLivro)) {
        cout << "Livro não encontrado." << endl;
        return;
    }

    Usuario* usuario = buscarItem<Usuario>(matriculaUsuario);
    Livro* livro = buscarItem<Livro>(matriculaLivro);

    if (usuario->numLivrosEmprestados >= 10) {
        cout << "Limite de livros emprestados alcançado." << endl;
        return;
    }

    usuario->livrosEmprestados[usuario->numLivrosEmprestados] = matriculaLivro;
    usuario->numLivrosEmprestados++;
    cout << "Livro emprestado com sucesso!" << endl;
}
void menu() {
    int opcao;
    do {
        system("cls");
        cout << "\n--- ---MENU--- ---" << endl;
        cout << "Escolha uma opcaoo: " << endl;
        cout << "1. Cadastrar (autores e itens)" << endl;
        cout << "2. Buscar" << endl;
        cout << "3. Remover" << endl;
        cout << "4. Alterar" << endl;
        cout << "5. emprestar" << endl;
        cout << "6. relatorios" << endl;
        cout << "0. Sair" << endl;
        cin >> opcao;
        cin.ignore();

        switch (opcao) {
            case 1: {
                cout << "1 - Incluir novos autores" << endl;
                cout << "2 - Cadastrar novo livro" << endl;
                cout << "3 - Cadastrar nova revista" << endl;
                cout << "4 - Cadastrar editora" << endl;
                cout << "5 - Cadastrar usuario" << endl;

                int escolha;
                cout << "Escolha uma opcao: ";
                cin >> escolha;

                switch (escolha) {
                    case 1:
                        cadastrarAutor();
                        salvarAutores();
                        break;
                    case 2:
                        cadastrarLivro();
                        salvarLivros();
                        break;
                    case 3:
                        cadastrarRevista();
                        salvarRevistas();
                        break;
                    case 4:
                        cadastrarEditora();
                        salvarEditoras();
                        break;
                    case 5:
                        cadastrarUsuario();
                        salvarUsuarios();
                        break;
                    default:
                        cout << "Opcao invalida! Tente novamente." << endl;
                }
                break;
            }
            case 2: {
                cout << "1 - Buscar por matricula" << endl;
                cout << "2 - Buscar por titulo" << endl;
                cout << "3 - Buscar por autor" << endl;
                cout << "4 - Buscar por editora" << endl;
                cout << "5 - Buscar por genero" << endl;

                int buscaEscolha;
                cout << "Escolha uma opcao: ";
                cin >> buscaEscolha;
                cin.ignore();

                switch (buscaEscolha) {
                    case 1: {
                        int matricula;
                        cout << "Digite a matricula do livro: " << endl;
                        cin >> matricula;
                        pesquisarMatricula(matricula);
                        system("pause");

                        break;
                    }
                    case 2: {
                        string titulo;

                        cout << "Digite o titulo do livro: " << endl;
                        getline(cin, titulo);

                        pesquisarLivroTitulo(titulo);
                        system("pause");
                        break;
                    }
                    case 3: {
                        string autor;
                        cout << "Digite o nome do autor: " << endl;
                        getline(cin, autor);
                        pesquisarAutor(autor);
                        system("pause");
                        break;
                    }
                    case 4: {
                        string editora;
                        cout << "Digite o nome da editora: " << endl;
                        getline(cin, editora);
                        pesquisarEditora(editora);
                        system("pause");
                        break;
                    }
                    case 5: {
                        string genero;
                        cout << "Digite o genero do livro: " << endl;
                        getline(cin, genero);
                        pesquisarGenero(genero);
                        system("pause");
                        break;
                    }
                }
                break;
            }
        case 3: {
            cout << "1 - Remover autor de um livro" << endl;
            cout << "2 - Remover editora" << endl;

            int removerEscolha;
            cout << "Escolha uma opcao: ";
            cin >> removerEscolha;

            switch (removerEscolha) {
                case 1: {
                    int matriculaLivro, matriculaAutor;
                    cout << "Digite a matricula do livro: ";
                    cin >> matriculaLivro;
                    cout << "Digite a matricula do autor a ser removido: ";
                    cin >> matriculaAutor;
                    removerAutorDoLivro(matriculaLivro, matriculaAutor);
                    system("pause");
                    break;
                }
                case 2: {
                    int matriculaEditora;
                    cout << "Digite a matricula da editora a ser removida: ";
                    cin >> matriculaEditora;
                    removerEditora(matriculaEditora);
                    system("pause");
                    break;
                }
            }
            break;
        }
        case 4: {
            cout << "1 - Alterar autor" << endl;
            cout << "2 - Alterar editora" << endl;

            int alterarEscolha;
            cout << "Escolha uma opcao: ";
            cin >> alterarEscolha;
            switch (alterarEscolha) {
                case 1: {
                    int matricula;
                    string novoNome;
                    int novaQuantidadeLivros;

                    cout << "Digite a matricula do autor: ";
                    cin >> matricula;
                    cin.ignore();
                    cout << "Novo nome: ";
                    getline(cin, novoNome);
                    cout << "Nova quantidade de livros: ";
                    cin >> novaQuantidadeLivros;

                    alterarAutor(matricula, novoNome, novaQuantidadeLivros);
                    break;
                }
                case 2: {
                    int matricula;
                    cout << "Digite a matricula da editora: ";
                    cin >> matricula;
                    cin.ignore();
                    alterarEditora(matricula);
                    break;
                }
            }
        break;
        }
    case 5: {
        int matriculaUsuario, matriculaLivro;
        cout << "Digite a matricula do usuario: ";
        cin >> matriculaUsuario;
        cout << "Digite a matricula do livro: ";
        cin >> matriculaLivro;
        emprestarLivro(matriculaUsuario, matriculaLivro);
        break;
    }
    case 6: {
        cout << "1 - Relatorio de Livros por Autor" << endl;
        cout << "2 - Relatorio de Livros por Editora" << endl;
        cout << "3 - Relatorio de Livros por Genero" << endl;
        cout << "4 - Historico de Retiradas de um Usuario" << endl;
        cout << "5 - livros e revistas em atraso" << endl;
        int relatorioEscolha;
        cin >> relatorioEscolha;
        cin.ignore();
        switch (relatorioEscolha) {
            case 1: {
                string autor;
                cout << "Digite o nome do autor: ";
                getline(cin, autor);
                relatorioLivrosPorAutor(autor);
                system("pause");
            break;
            }
            case 2: {
                string editora;
                cout << "Digite o nome da editora: ";
                getline(cin, editora);
                relatorioLivrosPorEditora(editora);
                system("pause");
            break;
            }
            case 3: {
                string genero;
                cout << "Digite o genero do livro: ";
                getline(cin, genero);
                relatorioLivrosPorGenero(genero);
                system("pause");
            break;
            }
            case 4: {
                int matriculaUsuario;
                cout << "Digite a matricula do usuario: ";
                cin >> matriculaUsuario;
                historicoRetiradas(matriculaUsuario);
                system("pause");
                break;
            }
            case 5: {
                relatorioLivrosAtrasados();
                system("pause");
            break;
            }

      }

      break;
    }
        case 0:
            cout << "..." << endl;

        return;
    default:
      cout << "Opcao invalida! Tente novamente." << endl;
    }
  } while (true);
}

int main() {
  inicializarTabela < Livro > ();
  menu();

  return 0;
}
