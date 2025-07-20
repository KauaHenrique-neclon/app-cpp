#include "dashboard.hpp"


pqxx::connection* Dashboard::banco() {
    try {
        return new pqxx::connection("dbname=dashboard user=postgres password=5115 host=localhost");
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return nullptr;
    }
};


Dashboard::Dashboard(int largura, int altura, const char* titulo) {
    windows = new Fl_Window(largura, altura, titulo);
    
    labelTitulo = new Fl_Box( 20, 01, largura-40, 50, "Dashboard");
    labelTitulo->box(FL_NO_BOX);
    labelTitulo->labelfont(FL_BOLD);
    labelTitulo->labelsize(20);
    labelTitulo->labeltype(FL_SHADOW_LABEL);

    dashtotal = new Fl_Group(20, 60, 460, 400);
    dashtotal->box(FL_NO_BOX);
    dashtotal->color(fl_rgb_color(255,255,255));
    dashtotal->labelcolor(fl_rgb_color(0,0,0));

    // frame do adicionar adm
    adicionarAdm = new Fl_Group(20,70, 10, 20);
    adicionarAdm->box(FL_NO_BOX);
    adicionarAdm->color(fl_rgb_color(255,255,255));
    adicionarAdm->labelcolor(fl_rgb_color(0,0,0));
    tituloAddAdm = new Fl_Box(50, 01, 400, 30);
    tituloAddAdm->box(FL_NO_BOX);
    tituloAddAdm->labelfont(FL_BOLD);
    tituloAddAdm->labelsize(20);
    tituloAddAdm->labeltype(FL_SHADOW_LABEL);

    usuarioInput = new Fl_Input(30, 10, 250, 30);
    usuarioInput->textsize(18);
    usuarioInput->size(250, 30);
    usuarioInput->box(FL_FLAT_BOX);
    usuarioInput->textcolor(fl_rgb_color(0, 0, 0));
    usuarioInput->color(fl_rgb_color(240,240,240));
    usuarioInput->labelcolor(FL_BLACK);

    senhaInput = new Fl_Input(30, 50, 250, 30);
    senhaInput->textsize(18);
    senhaInput->size(250, 30);
    senhaInput->box(FL_FLAT_BOX);
    senhaInput->textcolor(fl_rgb_color(0, 0, 0));
    senhaInput->color(fl_rgb_color(240,240,240));
    senhaInput->labelcolor(FL_BLACK);

    cadastrarAdm = new Fl_Button(180, 110, 50, 30, "Cadastrar");
    cadastrarAdm->color(fl_rgb_color(3, 173, 252));
    cadastrarAdm->labelcolor(fl_rgb_color(255, 255, 255));
    cadastrarAdm->box(FL_FLAT_BOX);
    cadastrarAdm->callback(cadastrarAdmCallback, this);


    adicionarAdm->add(tituloAddAdm);
    adicionarAdm->add(usuarioInput);
    adicionarAdm->add(senhaInput);
    adicionarAdm->add(cadastrarAdm);
    adicionarAdm->end();

    dashtotal->add(adicionarAdm);

}


void Dashboard::cadastrarAdmCallback(Fl_Widget* w, void* data) {
    Dashboard* self = static_cast<Dashboard*>(data);
    self->cadastrarAdmBanco();
}

void Dashboard::cadastrarAdmBanco() {
    std::string usuario = usuarioInput->value();
    std::string senha = senhaInput->value();

    pqxx::connection* conn = banco();
    if (conn != nullptr) {
        try {
            pqxx::work w(*conn);
            w.exec("INSERT INTO administradores (usuario, senha) VALUES ('" + w.quote(usuario) + "', '" + w.quote(senha) + "')");
            w.commit();
            std::cout << "Administrador cadastrado com sucesso!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Erro ao cadastrar administrador: " << e.what() << std::endl;
        }
    }
}


Dashboard::~Dashboard() {
    delete windows;
    delete conn;
}

void Dashboard::fecharJanelaDash(){
    windows->hide();
}

void Dashboard::mostrar(int argc, char **argv) {
    windows->show(argc, argv);
    Fl::run();
}