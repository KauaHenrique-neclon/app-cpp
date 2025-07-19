#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Input.H>
#include <FL/fl_message.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Multiline_Output.H>
#include <algorithm>
#include <stdio.h>
#include <pqxx/pqxx>
#include <algorithm>
#include <iostream>




class Atualizar{

private:
    Fl_Window* windows;
    Fl_Box* labelTitulo;
    Fl_Box* labelAviso;
    pqxx::connection* conn;
    Fl_Group* grupoButton;
    Fl_Button* buttonEmail;
    Fl_Button* buttonRua;
    Fl_Button* buttonBairro;
    Fl_Button* buttonBairroAtualizar;
    Fl_Button* buttonEmailAtualizar;
    Fl_Button* buttonRuaAtualizar;
    Fl_Group* grupoAtualizarBairro;
    Fl_Box* tituloGrupoBairro;
    Fl_Box* tituloGrupoEmail;
    Fl_Box* tituloGrupoRua;
    Fl_Group* grupoAtualizarEmail;
    Fl_Group* grupoAtualizarRua;
    Fl_Input* cpfInputAluno;
    Fl_Input* bairroNovoInput;
    Fl_Input* ruaNovoInput;
    Fl_Input* emailNovoInput;

public:
    Atualizar(int largura, int altura, const char* titulo);
    ~Atualizar();
    void mostrar(int argc, char **argv);
    pqxx::connection* banco();
    void grupoBairro();
    void grupoEmail();
    void grupoRua();
    void atualizarEmail();
    void atualizarRua();
    void atualizarBairro();
    void atualizarEmail();
    void fecharJanela();

    static void callbackBairro(Fl_Widget* w, void* data);
    static void callbackEmail(Fl_Widget* w, void* data);
    static void callbackRua(Fl_Widget* w, void* data);
    //static void atualizarDadosCallback(Fl_Widget* w, void* data);
    static void atualizarDadosEmailCallback(Fl_Widget* w, void* data);
    static void atualizarDadosBairroCallback(Fl_Widget* w, void* data);
    static void atualizarDadosRuaCallback(Fl_Widget* w, void* data);
};