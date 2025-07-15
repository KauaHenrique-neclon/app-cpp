#include "cadastrar.hpp"


pqxx::connection* CadastrarDados::banco() {
    try {
        return new pqxx::connection("dbname=dashboard user=postgres password=5115 host=localhost");
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return nullptr;
    }
};

void CadastrarDados::salvarDados(){
    std::string nome = inputNome->value();
    std::string email = inputEmail->value();
    std::string cpf = inputCpf->value();
    std::string dataNascimento = inputDataNascimento->value();
    std::string ruaCasa = inputRuaCasa->value();
    std::string bairro = inputBairro->value();

    pqxx::connection* conn = banco();
    if(conn == nullptr){
        std::cerr << "Erro ao conectar ao banco de dados" << std::endl;
        return fl_message("Erro ao Conectar ao banco de dados.");
    }
    pqxx::work w(*conn);
    try{
        w.exec("INSERT INTO tabela (nome, email, cpf, data_nascimento, rua, bairro) "
            "VALUES ('" + w.quote(nome) + "', '" + w.quote(email) + "', '" + w.quote(cpf) + "', '" + w.quote(dataNascimento) + "', '" + w.quote(ruaCasa) + "', '" + w.quote(bairro) + "')");
        w.commit();      
        fl_message("Dados inseridos com sucesso.");
    }catch (const std::exception& e){
        w.abort();
        fl_message("Dados não foram inseridos no banco.");
    };
    delete conn;
}

void CadastrarDados::salvarDadosCallback(Fl_Widget* w, void* data) {
    CadastrarDados* self = static_cast<CadastrarDados*>(data);
    self->salvarDados();
}


void callbackMenuVoltar(Fl_Widget *widget, void *data) {
    CadastrarDados* cad = static_cast<CadastrarDados*>(data);
    cad->fecharJanela();
    exit(0);
}



CadastrarDados::CadastrarDados(int largura, int altura, const char* titulo){
    windows = new Fl_Window(largura, altura, titulo);


    labelTitulo = new Fl_Box( 20, 01, largura-40, 50, "Cadastrar");
    labelTitulo->box(FL_NO_BOX);
    labelTitulo->labelfont(FL_BOLD+FL_ITALIC);
    labelTitulo->labelsize(20);
    labelTitulo->labeltype(FL_SHADOW_LABEL);

    //  input nome
    grupoInputNome = new Fl_Group(20, 60, 460, 50);
    grupoInputNome->box(FL_NO_BOX);
    grupoInputNome->labelcolor(fl_rgb_color(0,0,0));
    labelNome = new Fl_Box(30, 60, 80, 40, "Nome: ");
    labelNome->labelsize(20);
    inputNome = new Fl_Input(120, 65, 250, 30);
    inputNome->textcolor(fl_rgb_color(0, 0, 0));
    inputNome->textsize(18);
    inputNome->box(FL_FLAT_BOX);
    inputNome->size(250, 30);
    inputNome->color(fl_rgb_color(240,240,240));
    inputNome->labelcolor(FL_BLACK);
    grupoInputNome->add(labelNome);
    grupoInputNome->add(inputNome);
    grupoInputNome->end();
    
    // input de email
    grupoInputEmail = new Fl_Group(20, 110, 460, 50);
    grupoInputEmail->box(FL_NO_BOX);
    grupoInputEmail->labelcolor(fl_rgb_color(0,0,0));
    labelEmail = new Fl_Box(30, 110, 80, 40,"Email: ");
    labelEmail->labelsize(20);
    inputEmail = new Fl_Input(120, 115, 250, 30);
    inputEmail->textcolor(fl_rgb_color(0, 0, 0));
    inputEmail->box(FL_FLAT_BOX);
    inputEmail->textsize(18);
    inputEmail->color(fl_rgb_color(240,240,240));
    inputEmail->labelcolor(FL_BLACK);
    grupoInputEmail->add(labelEmail);
    grupoInputEmail->add(inputEmail);
    grupoInputEmail->end();

    // input do CPF
    grupoInputCpf = new Fl_Group(20, 160, 460, 50);
    grupoInputCpf->box(FL_NO_BOX);
    grupoInputCpf->labelcolor(fl_rgb_color(0,0,0));
    labelCpf = new Fl_Box(30, 160, 80, 40,"CPF: ");
    labelCpf->labelsize(20);
    inputCpf = new Fl_Input(120, 165, 250, 30);
    inputCpf->textsize(18);
    inputCpf->box(FL_FLAT_BOX);
    inputCpf->textcolor(fl_rgb_color(0, 0, 0));
    inputCpf->color(fl_rgb_color(240,240,240));
    inputCpf->labelcolor(FL_BLACK);
    grupoInputCpf->add(labelCpf);
    grupoInputCpf->add(inputCpf);
    grupoInputCpf->end();


    // input Data de Nascimento
    grupoInputDataNascimento = new Fl_Group(20, 210, 460, 50);
    grupoInputDataNascimento->box(FL_NO_BOX);
    grupoInputDataNascimento->labelcolor(fl_rgb_color(0,0,0));
    labelDataNascimento = new Fl_Box(28, 210, 80, 40, "Nascimento:");
    labelDataNascimento->labelsize(20);
    inputDataNascimento = new Fl_Input(120, 215, 250, 30);
    inputDataNascimento->textsize(18);
    inputDataNascimento->box(FL_FLAT_BOX);
    inputDataNascimento->textcolor(fl_rgb_color(0, 0, 0));
    inputDataNascimento->color(fl_rgb_color(240,240,240));
    inputDataNascimento->labelcolor(FL_BLACK);
    grupoInputDataNascimento->add(labelDataNascimento);
    grupoInputDataNascimento->add(inputDataNascimento);
    grupoInputDataNascimento->end();


    //input da Rua da casa
    grupoInputRuaCasa = new Fl_Group(20, 260, 460, 50);
    grupoInputRuaCasa->box(FL_NO_BOX);
    grupoInputRuaCasa->labelcolor(fl_rgb_color(0,0,0));
    labelRuaCasa = new Fl_Box(30, 260, 80, 40,"Rua: ");
    labelRuaCasa->labelsize(20);
    inputRuaCasa = new Fl_Input(120, 265, 250, 30);
    inputRuaCasa->textsize(18);
    inputRuaCasa->box(FL_FLAT_BOX);
    inputRuaCasa->textcolor(fl_rgb_color(0, 0, 0));
    inputRuaCasa->color(fl_rgb_color(240,240,240));
    inputRuaCasa->labelcolor(FL_BLACK);
    grupoInputRuaCasa->add(labelRuaCasa);
    grupoInputRuaCasa->add(inputRuaCasa);
    grupoInputRuaCasa->end();


    // input do Bairro da pessoa
    grupoInputBairro = new Fl_Group(20, 310, 460, 50);
    grupoInputBairro->box(FL_NO_BOX);
    grupoInputBairro->labelcolor(fl_rgb_color(0,0,0));
    labelBairro = new Fl_Box(30, 310, 80, 40, "Bairro: ");
    labelBairro->labelsize(20);
    inputBairro = new Fl_Input(120, 315, 250, 30);
    inputBairro->textsize(18);
    inputBairro->size(250, 30);
    inputBairro->box(FL_FLAT_BOX);
    inputBairro->textcolor(fl_rgb_color(0, 0, 0));
    inputBairro->color(fl_rgb_color(240,240,240));
    inputBairro->labelcolor(FL_BLACK);
    grupoInputBairro->add(labelBairro);
    grupoInputBairro->add(inputBairro);
    grupoInputBairro->end();


    // button cadastrar
    Buttoncadastrar = new Fl_Button(50, 365, 150, 30, "Cadastrar Dados");
    Buttoncadastrar->color(fl_rgb_color(3, 173, 252));
    Buttoncadastrar->labelcolor(fl_rgb_color(255, 255, 255));
    Buttoncadastrar->box(FL_FLAT_BOX);
    Buttoncadastrar->callback(CadastrarDados::salvarDadosCallback, this);   


    ButtonMenuVoltar = new Fl_Button(250, 365, 150, 30,"Menu");
    ButtonMenuVoltar->color(fl_rgb_color(3, 173, 252));
    ButtonMenuVoltar->labelcolor(fl_rgb_color(255, 255, 255));
    ButtonMenuVoltar->box(FL_FLAT_BOX);
    ButtonMenuVoltar->callback(callbackMenuVoltar);





    inputNome->maximum_size(30);
    inputEmail->maximum_size(30);
    inputCpf->maximum_size(30);
    inputDataNascimento->maximum_size(30);
    inputRuaCasa->maximum_size(30);
    inputBairro->maximum_size(30);



    windows->add(labelTitulo);
    windows->add(grupoInputNome);
    windows->add(grupoInputEmail);
    windows->add(grupoInputCpf);
    windows->add(grupoInputDataNascimento);
    windows->add(grupoInputRuaCasa);
    windows->add(grupoInputBairro);
    windows->add(Buttoncadastrar);
    windows->add(ButtonMenuVoltar);
    windows->color(fl_rgb_color(255, 255, 255));
    windows->resizable(windows);
    windows->size_range(500, 400, 800, 500);
    windows->end();
}


CadastrarDados::~CadastrarDados() {
    delete windows;
    delete conn;
}

void CadastrarDados::fecharJanela(){
    windows->hide();
}

void CadastrarDados::mostrar(int argc, char **argv) {
    windows->show(argc, argv);
    Fl::run();
}



/*
int chamandoJanelaCadastro(int argc, char **argv) {
    CadastrarDados* janela = new CadastrarDados(500, 400, "Menu");
    janela->mostrar(argc, argv);
    return 0;
}*/