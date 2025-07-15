#include <pqxx/pqxx>
#include <iostream>

int bancoDados() {
    try {
        pqxx::connection conn("dbname=dashboard user=postgres password=5115 host=localhost");
        pqxx::work w(conn);
        pqxx::result r = w.exec("SELECT COUNT(*) FROM alunos");
        w.commit();

        std::cerr << "Dados da consulta:" << std::endl;
        for (auto row : r) {
            for (auto field : row) {
                std::cerr << field.c_str() << " ";
            }
            std::cerr << std::endl;
        }
    } catch (const pqxx::failure &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erro desconhecido: " << e.what() << std::endl;
    }

    std::cout << "Pressione Enter para sair..." << std::endl;
    std::cin.get();

    return 0;
}


// g++ -o dadosBanco dadosBanco.cpp -lpqxx -lpq