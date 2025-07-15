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




class Visualizar{
private:
    Fl_Window* windows;
    Fl_Box* labelTitulo;

public:
    Visualizar(int largura, int altura, const char* titulo);
    ~Visualizar();
    void mostrar(int argc, char **argv);
    void fecharJanela();
};
