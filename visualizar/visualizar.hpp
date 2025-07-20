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
#include <iostream>
#include <memory>
#include <vector>




class Visualizar{
private:
    Fl_Window* windows;
    Fl_Box* labelTitulo;
    Fl_Table* tabela;
    std::vector<std::vector<std::string>> dados; 

public:
    Visualizar(int largura, int altura, const char* titulo);
    ~Visualizar();
    pqxx::connection* banco();
    void mostrar(int argc, char **argv);
    void fecharJanela();
    pqxx::result buscarDados();
    void preencherTabela();
    static void drawcell(Fl_Table* table, int row, int col, int X, int Y, int W, int H, Visualizar* instance);
    static void tablecallback(Fl_Widget* w, void* data);
};
