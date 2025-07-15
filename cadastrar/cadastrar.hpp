#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Input.H>
#include <FL/fl_message.H>
#include <algorithm>
#include <pqxx/pqxx>
#include <iostream>


class CadastrarDados {

private:
    Fl_Window* windows;
    Fl_Box* labelTitulo;
    pqxx::connection* conn;
    Fl_Group* grupoInputNome;
    Fl_Group* grupoInputEmail;
    Fl_Group* grupoInputDataNascimento;
    Fl_Group* grupoInputRuaCasa;
    Fl_Group* grupoInputBairro;
    Fl_Group* grupoInputCpf;
    Fl_Input* inputNome;
    Fl_Input* inputEmail;
    Fl_Input* inputDataNascimento;
    Fl_Input* inputRuaCasa;
    Fl_Input* inputBairro;
    Fl_Input* inputCpf;
    Fl_Box* labelNome;
    Fl_Box* labelEmail;
    Fl_Box* labelDataNascimento;
    Fl_Box* labelRuaCasa;
    Fl_Box* labelBairro;
    Fl_Box* labelCpf;
    Fl_Button* Buttoncadastrar;
    Fl_Button* ButtonMenuVoltar;
public:
    CadastrarDados(int largura, int altura, const char* titulo);
    ~CadastrarDados();
    void mostrar(int argc, char **argv);
    pqxx::connection* banco();
    void salvarDados();
    void fecharJanela();
    static void salvarDadosCallback(Fl_Widget* w, void* data);
};