#include "atualizar.hpp"


pqxx::connection* Atualizar::banco() {
    try {
        return new pqxx::connection("dbname=dashboard user=postgres password=5115 host=localhost");
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return nullptr;
    }
};



void callbackMenuVoltarAtualizar(Fl_Widget *widget, void *data) {
    Atualizar* cad = static_cast<Atualizar*>(data);
    cad->fecharJanela();
    exit(0);
};



void Atualizar::atualizarRua(){
    std::string rua = ruaNovoInput->value();
    std::string cpf = cpfInputAluno->value();

    pqxx::connection* conn = banco();
    if(conn == nullptr){
        std::cerr << "Erro ao conectar ao banco de dados" << std::endl;
        return fl_message("Erro ao Conectar ao banco de dados.");
    }
    pqxx::work w(*conn);
    try{
        w.exec("UPDRATE alunos SET rua = '" + w.quote(rua) + "' WHERE cpf = '" + w.quote(cpf) + "'");
    }catch (const std::exception& e){

    }

};




Atualizar::Atualizar(int largura, int altura, const char* titulo){
    windows = new Fl_Window(largura, altura, titulo);


    labelTitulo = new Fl_Box(20, 01, largura-40, 50, "Atualizar");
    labelTitulo->box(FL_NO_BOX);
    labelTitulo->labelfont(FL_BOLD);
    labelTitulo->labelsize(20);
    labelTitulo->labeltype(FL_SHADOW_LABEL);

    grupoButton = new Fl_Group(20, 40, 500, 200);
    grupoButton->box(FL_NO_BOX);
    grupoButton->labelcolor(fl_rgb_color(0,0,0));
    labelAviso = new Fl_Box(20, 20, largura-40, 50, "Qual dados quer alterar");

    // button do bairro
    buttonBairro = new Fl_Button(20,80, 100, 30, "Bairro");
    buttonBairro->color(fl_rgb_color(3, 173, 252));
    buttonBairro->labelcolor(fl_rgb_color(255, 255, 255));
    buttonBairro->box(FL_FLAT_BOX);
    buttonBairro->callback(callbackBairro, this);

    // button do rua
    buttonRua = new Fl_Button(150, 80, 100, 30, "Rua");
    buttonRua->color(fl_rgb_color(3, 173, 252));
    buttonRua->labelcolor(fl_rgb_color(255, 255, 255));
    buttonRua->box(FL_FLAT_BOX);

    buttonEmail = new Fl_Button(20, 140, 100, 30, "Email");
    buttonEmail->color(fl_rgb_color(3, 173, 252));
    buttonEmail->labelcolor(fl_rgb_color(255, 255, 255));
    buttonEmail->box(FL_FLAT_BOX);

    grupoButton->add(buttonBairro);
    grupoButton->add(buttonRua);
    grupoButton->add(buttonEmail);
    windows->add(grupoButton);

}


void Atualizar::callbackBairro(Fl_Widget* w, void* data) {
    Atualizar* self = static_cast<Atualizar*>(data);
    self->grupoBairro();
}

void Atualizar::callbackEmail(Fl_Widget* w, void* data) {
    Atualizar* self = static_cast<Atualizar*>(data);
    self->grupoEmail();
}

void Atualizar::callbackRua(Fl_Widget* w, void* data) {
    Atualizar* self = static_cast<Atualizar*>(data);
    self->grupoRua();
}


void Atualizar::grupoBairro(){
    grupoAtualizarBairro = new Fl_Group(20, 40, 500, 200);
    tituloGrupoBairro = new Fl_Box(20, 01, 460, 50, "Atualizar Bairro");
    tituloGrupoBairro->box(FL_NO_BOX);
    tituloGrupoBairro->labelfont(FL_BOLD);
    tituloGrupoBairro->labelsize(20);
    tituloGrupoBairro->labeltype(FL_SHADOW_LABEL);

    cpfInputAluno = new Fl_Input(120, 65, 250, 30);
    cpfInputAluno->textcolor(fl_rgb_color(0, 0, 0));
    cpfInputAluno->textsize(18);
    cpfInputAluno->box(FL_FLAT_BOX);
    cpfInputAluno->size(250, 30);
    cpfInputAluno->color(fl_rgb_color(240,240,240));
    cpfInputAluno->labelcolor(FL_BLACK);

    bairroNovoInput = new Fl_Input(120, 115, 250, 30);
    bairroNovoInput->textcolor(fl_rgb_color(0, 0, 0));
    bairroNovoInput->textsize(18);
    bairroNovoInput->box(FL_FLAT_BOX);
    bairroNovoInput->size(250, 30);
    bairroNovoInput->color(fl_rgb_color(240,240,240));
    bairroNovoInput->labelcolor(FL_BLACK);
    

    buttonBairroAtualizar = new Fl_Button(150,80,100,30,"Atualizar");
    buttonBairroAtualizar->color(fl_rgb_color(3, 173, 252));
    buttonBairroAtualizar->labelcolor(fl_rgb_color(255, 255, 255));
    buttonBairroAtualizar->box(FL_FLAT_BOX);
    buttonBairroAtualizar->callback(atualizarDadosBairroCallback, this);

    //grupoAtualizarBairro->resizable(nullptr);
    grupoAtualizarBairro->add(cpfInputAluno);
}

void Atualizar::grupoEmail(){
    grupoAtualizarEmail = new Fl_Group(20, 40, 500, 200);
    tituloGrupoEmail = new Fl_Box(20, 01, 460, 50, "Atualizar Email");
    tituloGrupoEmail->box(FL_NO_BOX);
    tituloGrupoEmail->labelfont(FL_BOLD);
    tituloGrupoEmail->labelsize(20);
    tituloGrupoEmail->labeltype(FL_SHADOW_LABEL);

    cpfInputAluno = new Fl_Input(120, 65, 250, 30);
    cpfInputAluno->textcolor(fl_rgb_color(0, 0, 0));
    cpfInputAluno->textsize(18);
    cpfInputAluno->box(FL_FLAT_BOX);
    cpfInputAluno->size(250, 30);
    cpfInputAluno->color(fl_rgb_color(240,240,240));
    cpfInputAluno->labelcolor(FL_BLACK);

    emailNovoInput = new Fl_Input(120, 115, 250, 30);
    emailNovoInput->textcolor(fl_rgb_color(0, 0, 0));
    emailNovoInput->textsize(18);
    emailNovoInput->box(FL_FLAT_BOX);
    emailNovoInput->size(250, 30);
    emailNovoInput->color(fl_rgb_color(240,240,240));
    emailNovoInput->labelcolor(FL_BLACK);
    

    buttonEmailAtualizar = new Fl_Button(150,80,100,30,"Atualizar");
    buttonEmailAtualizar->color(fl_rgb_color(3, 173, 252));
    buttonEmailAtualizar->labelcolor(fl_rgb_color(255, 255, 255));
    buttonEmailAtualizar->box(FL_FLAT_BOX);
    buttonEmailAtualizar->callback(atualizarDadosEmailCallback, this);
}

void Atualizar::grupoRua(){
    grupoAtualizarRua = new Fl_Group(20, 40, 500, 200);
    tituloGrupoRua = new Fl_Box(20, 01, 460, 50, "Atualizar Email");
    tituloGrupoRua->box(FL_NO_BOX);
    tituloGrupoRua->labelfont(FL_BOLD);
    tituloGrupoRua->labelsize(20);
    tituloGrupoRua->labeltype(FL_SHADOW_LABEL);

    cpfInputAluno = new Fl_Input(120, 65, 250, 30);
    cpfInputAluno->textcolor(fl_rgb_color(0, 0, 0));
    cpfInputAluno->textsize(18);
    cpfInputAluno->box(FL_FLAT_BOX);
    cpfInputAluno->size(250, 30);
    cpfInputAluno->color(fl_rgb_color(240,240,240));
    cpfInputAluno->labelcolor(FL_BLACK);

    ruaNovoInput = new Fl_Input(120, 115, 250, 30);
    ruaNovoInput->textcolor(fl_rgb_color(0, 0, 0));
    ruaNovoInput->textsize(18);
    ruaNovoInput->box(FL_FLAT_BOX);
    ruaNovoInput->size(250, 30);
    ruaNovoInput->color(fl_rgb_color(240,240,240));
    ruaNovoInput->labelcolor(FL_BLACK);
    

    buttonRuaAtualizar = new Fl_Button(150,80,100,30,"Atualizar");
    buttonRuaAtualizar->color(fl_rgb_color(3, 173, 252));
    buttonRuaAtualizar->labelcolor(fl_rgb_color(255, 255, 255));
    buttonRuaAtualizar->box(FL_FLAT_BOX);
    buttonRuaAtualizar->callback(atualizarDadosEmailCallback, this);
}


void Atualizar::atualizarDadosBairroCallback(Fl_Widget* w, void* data){
    Atualizar* self = static_cast<Atualizar*>(data);
    self->atualizarBairro();
}
void Atualizar::atualizarDadosEmailCallback(Fl_Widget* w, void* data){
    Atualizar* self = static_cast<Atualizar*>(data);
    self->atualizarEmail();
}
void Atualizar::atualizarDadosRuaCallback(Fl_Widget* w, void* data){
    Atualizar* self = static_cast<Atualizar*>(data);
    self->atualizarRua();
}

void Atualizar::atualizarBairro(){
    std::string bairro = bairroNovoInput->value();
    std::string cpf = cpfInputAluno->value();

    pqxx::connection* conn = banco();
    if(conn == nullptr){
        std::cerr << "Erro ao conectar ao banco de dados" << std::endl;
        return fl_message("Erro ao Conectar ao banco de dados.");
    }
    pqxx::work w(*conn);
    try{
        w.exec("UPDRATE alunos SET bairro = '" + w.quote(bairro) + "' WHERE cpf = '" + w.quote(cpf) + "'");
        w.commit();
    }catch (const std::exception& e){
        return fl_message("Não foi possivel atualizar o Bairro");
    }

};

void Atualizar::atualizarEmail(){
    std::string email = emailNovoInput->value();
    std::string cpf = cpfInputAluno->value();

    pqxx::connection* conn = banco();
    if(conn == nullptr){
        std::cerr << "Erro ao conectar ao banco de dados" << std::endl;
        return fl_message("Erro ao Conectar ao banco de dados.");
    }
    pqxx::work w(*conn);
    try{
        w.exec("UPDRATE alunos SET email = '" + w.quote(email) + "' WHERE cpf = '" + w.quote(cpf) + "'");
    }catch (const std::exception& e){

    }

};


Atualizar::~Atualizar() {
    delete windows;
    delete conn;
}

void Atualizar::fecharJanela(){
    windows->hide();
}


void Atualizar::mostrar(int argc, char **argv) {
    windows->show(argc, argv);
    Fl::run();
}