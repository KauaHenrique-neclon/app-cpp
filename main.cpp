#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <algorithm>
#include <pqxx/pqxx>
#include <iostream>
#include "cadastrar/cadastrar.hpp"
#include "visualizar/visualizar.hpp"
#include "atualizar/atualizar.hpp"



class Janela {
public:
    Janela(int largura, int altura, const char* titulo);
    ~Janela();

    void mostrar(int argc, char **argv);
    pqxx::connection* banco();


private:
    Fl_Window *window;
    Fl_Box *labalInicial;
    Fl_Button *botaoCadastrar, *botaoVisualizar;
    Fl_Button *botaoAtualizar;
    Fl_Box *tituloTotal, *totalAluno;
    Fl_Group *grupo;
    pqxx::connection* conn;
    static void botaoCadastrarCallback(Fl_Widget *widget, void *data);
    static void botaoVisualizarCallback(Fl_Widget *widget, void *data);
    static void botaoAtualizarCallback(Fl_Widget *widget, void *data);
};


pqxx::connection* Janela::banco() {
    try {
        return new pqxx::connection("dbname=dashboard user=postgres password=5115 host=localhost");
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return nullptr;
    }
};

/*
void Janela::botaoCadastrarCallback(Fl_Widget *widget, void *data) {
    Janela* janelaAtual = static_cast<Janela*>(data);
    CadastrarDados *janelaCadastro = new CadastrarDados(500, 400, "Cadastro");
    janelaCadastro->mostrar(0, nullptr);
    delete janelaAtual->window;
    //exit(0);
}
*/

void Janela::botaoCadastrarCallback(Fl_Widget *widget, void *data) {
    Janela* janelaAtual = static_cast<Janela*>(data);
    janelaAtual->window->hide();
    CadastrarDados *janelaCadastro = new CadastrarDados(500, 400, "Cadastro");
    janelaCadastro->mostrar(0, nullptr);
    janelaAtual->window->show();
}


void Janela::botaoVisualizarCallback(Fl_Widget *widget, void *data) {
    Janela* janelaAtual = static_cast<Janela*>(data);
    janelaAtual->window->hide();
    Visualizar *janelaVisualizar = new Visualizar(500, 400, "Visualizar");
    janelaVisualizar->mostrar(0, nullptr);
    janelaAtual->window->show();
}

void Janela::botaoAtualizarCallback(Fl_Widget *widget, void *data){
    Janela* janelaAtual = static_cast<Janela*>(data);
    janelaAtual->window->hide();
    Atualizar *janelaAtualizar = new Atualizar(500, 400, "Atualizar");
    janelaAtual->mostrar(0, nullptr);
    janelaAtual->window->show();
}




Janela::Janela(int largura, int altura, const char* titulo) {
    window = new Fl_Window(largura, altura, titulo);
    // box = new Fl_Box(x, y, largura, altura, "Menu Cadastro");
    labalInicial = new Fl_Box(20, 01, largura-40, 50, "Menu Cadastro");
    labalInicial->box(FL_NO_BOX);
    labalInicial->labelfont(FL_BOLD+FL_ITALIC);
    labalInicial->labelsize(20);
    labalInicial->labeltype(FL_SHADOW_LABEL);

    // criando o botão
    botaoCadastrar = new Fl_Button(20,80, 100, 30, "Cadastrar");
    botaoCadastrar->color(fl_rgb_color(3, 173, 252));
    botaoCadastrar->labelcolor(fl_rgb_color(255, 255, 255));
    botaoCadastrar->box(FL_FLAT_BOX);
    botaoCadastrar->callback(botaoCadastrarCallback, this);


    botaoVisualizar = new Fl_Button(150,80,100,30, "Visualizar");
    botaoVisualizar->color(fl_rgb_color(3, 173, 252));
    botaoVisualizar->labelcolor(fl_rgb_color(255, 255, 255));
    botaoVisualizar->box(FL_ROUND_UP_BOX);
    botaoVisualizar->callback(botaoVisualizarCallback, this);


    botaoVisualizar = new Fl_Button(150,80,100,30, "Visualizar");
    botaoVisualizar->color(fl_rgb_color(3, 173, 252));
    botaoVisualizar->labelcolor(fl_rgb_color(255, 255, 255));
    botaoVisualizar->box(FL_ROUND_UP_BOX);
    botaoVisualizar->callback(botaoVisualizarCallback, this);


    botaoAtualizar = new Fl_Button(150,80,100,30, "Visualizar");
    botaoAtualizar->color(fl_rgb_color(3, 173, 252));
    botaoAtualizar->labelcolor(fl_rgb_color(255, 255, 255));
    botaoAtualizar->box(FL_ROUND_UP_BOX);
    botaoAtualizar->callback(botaoAtualizarCallback, this);
   


    // graficos
    conn = banco();
    if (conn != nullptr) {
        pqxx::work w(*conn);
        pqxx::result resul = w.exec("SELECT COUNT(*) FROM alunos");
        int totalAlunos = resul[0][0].as<int>();
        int* dados = new int[1];
        dados[0] = totalAlunos;
        grupo = new Fl_Group(20, 130, 180, 80);
        grupo->box(FL_FLAT_BOX);
        grupo->color(fl_rgb_color(135,206,250));
        grupo->labelcolor(fl_rgb_color(0,0,0));
        //grupo->box(FL_)

        tituloTotal = new Fl_Box(27, 140, 180, 20, "Total Alunos");
        totalAluno = new Fl_Box(27, 170, 180, 20, std::to_string(totalAlunos).c_str());
        grupo->add(tituloTotal);
        grupo->add(totalAluno);
    } else {
        int* dados = new int[1];
        grupo = new Fl_Group(20, 130, 200, 150);
        grupo->box(FL_ENGRAVED_FRAME);
        tituloTotal = new Fl_Box(30, 140, 180, 20, "Total Alunos");
        totalAluno = new Fl_Box(30, 170, 180, 20,"None");
        grupo->add(tituloTotal);
        grupo->add(totalAluno);
    }





    window->color(fl_rgb_color(255, 255, 255));
    window->resizable(window);
    window->add(labalInicial);
    window->add(botaoCadastrar);
    window->add(botaoVisualizar);
    window->add(grupo);
    window->end();
};



Janela::~Janela() {
    delete window;
    delete conn;
}

void Janela::mostrar(int argc, char **argv) {
    window->show(argc, argv);
    Fl::run();
}

int main(int argc, char **argv) {
    Janela janela(500, 400, "Menu");
    janela.mostrar(argc, argv);
    return 0;
}


// g++ main.cpp cadastrar/cadastrar.cpp visualizar/visualizar.cpp atualizar/atualizar.cpp dashboard/dashboard.cpp -o main.exe -mwindows -lfltk -lfltk_images -lpng -ljpeg -lpqxx -lpq