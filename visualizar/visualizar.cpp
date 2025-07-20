#include "visualizar.hpp"



pqxx::connection* Visualizar::banco() {
    try {
        return new pqxx::connection("dbname=dashboard user=postgres password=5115 host=localhost");
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return nullptr;
    }
};

pqxx::result Visualizar::buscarDados(){
    pqxx::connection* conn = banco();
    if(conn == nullptr){
        std::cerr << "Erro ao conectar ao banco de dados" << std::endl;
        return pqxx::result();
    }
    pqxx::work w(*conn);
    try{
        pqxx::result dados = w.exec("SELECT * FROM alunos");
        w.commit();
        delete conn;
        return dados;
    }catch (const std::exception& e){
        w.abort();
        fl_message("Erro no banco de dados");
        delete conn;
        return pqxx::result();
    }
}


/*
void callbackMenuVoltarVisualizar(Fl_Widget *widget, void *data) {
    Visualizar* cad = static_cast<Visualizar*>(data);
    cad->fecharJanela();
    exit(0);
}
*/

void callbackMenuVoltarVisualizar(Fl_Widget *widget, void *data) {
    Visualizar* cad = static_cast<Visualizar*>(data);
    cad->fecharJanela();
}

Visualizar::Visualizar(int largura, int altura, const char* titulo) {
    windows = new Fl_Window(largura, altura, titulo);

    labelTitulo = new Fl_Box(20, 1, largura - 40, 50, "Visualizar");
    labelTitulo->box(FL_NO_BOX);
    labelTitulo->labelfont(FL_BOLD + FL_ITALIC);
    labelTitulo->labelsize(20);
    labelTitulo->labeltype(FL_SHADOW_LABEL);

    tabela = new Fl_Table(10, 10, largura - 20, altura - 50);
    tabela->rows(0);
    tabela->cols(6);
    tabela->callback(tablecallback, this);
    tabela->end();
    preencherTabela(); 
    windows->end();
}



void Visualizar::preencherTabela() {
    pqxx::result resultado = buscarDados();
    if (resultado.empty()) {
        fl_message("Nenhum dado encontrado.");
        return;
    }

    // Preencher dados
    for (auto row : resultado) {
        std::vector<std::string> linha;
        linha.push_back(row["nome"].c_str());
        linha.push_back(row["email"].c_str());
        linha.push_back(row["cpf"].c_str());
        linha.push_back(row["data_nascimento"].c_str());
        linha.push_back(row["rua"].c_str());
        linha.push_back(row["bairro"].c_str());
        dados.push_back(linha);
    }

    tabela->rows(dados.size());
    tabela->redraw();
}


void Visualizar::drawcell(Fl_Table* table, int row, int col, int X, int Y, int W, int H, Visualizar* instance) {
    if (row >= instance->dados.size() || col >= instance->dados[row].size()) return;
    fl_draw(instance->dados[row][col].c_str(), X + 2, Y + 14);
}

void Visualizar::tablecallback(Fl_Widget* w, void* data) {
    Fl_Table* table = static_cast<Fl_Table*>(w);
    Visualizar* viz = static_cast<Visualizar*>(data);
    int row = table->callback_row();
    int col = table->callback_col();

    if (row < 0 || col < 0) return; 
    drawcell(table, row, col, table->x(), table->y(), table->w(), table->h(), viz);
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