#include "visualizar.hpp"





void callbackMenuVoltarVisualizar(Fl_Widget *widget, void *data) {
    Visualizar* cad = static_cast<Visualizar*>(data);
    cad->fecharJanela();
    exit(0);
}


Visualizar::Visualizar(int largura, int altura, const char* titulo){
    windows = new Fl_Window(largura, altura, titulo);

    labelTitulo = new Fl_Box(20, 01, largura-40, 50, "Visualizar");
    labelTitulo->box(FL_NO_BOX);
    labelTitulo->labelfont(FL_BOLD+FL_ITALIC);
    labelTitulo->labelsize(20);
    labelTitulo->labeltype(FL_SHADOW_LABEL);
}




Visualizar::~Visualizar() {
    delete windows;
}

void Visualizar::fecharJanela(){
    windows->hide();
}

void Visualizar::mostrar(int argc, char **argv) {
    windows->show(argc, argv);
    Fl::run();
}