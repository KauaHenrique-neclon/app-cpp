#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Input.H>
#include <FL/fl_message.H>
#include <FL/Fl_Group.H>
#include <algorithm>
#include <pqxx/pqxx>
#include <iostream>



class Dashboard {

private:
    Fl_Window* windows;
    Fl_Box* labelTitulo;
    pqxx::connection* conn;

    Fl_Group* dashtotal;
    Fl_Group* adicionarAdm;
    Fl_Group* totalAdm;
    Fl_Group* totalAlunos;

    Fl_Box* tituloAddAdm;
    Fl_Input* usuarioInput;
    Fl_Input* senhaInput;
    Fl_Button* cadastrarAdm;

public:
   Dashboard(int largura, int altura, const char* titulo);
   ~Dashboard();
   pqxx::connection* banco();
   void fecharJanelaDash();
   static void cadastrarAdmCallback(Fl_Widget* w, void* data);
   void cadastrarAdmBanco();
   void mostrarDash(int argc, char **argv);
};