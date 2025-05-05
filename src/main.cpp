////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Directed Acyclic Graph Scheduler
// All rights reserved.
//
// Contact: mehoggan@gmail.com
//
// This software is licensed under the terms of the Your License.
// See the LICENSE file in the top-level directory.
/////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <iostream>
#include <osmium/handler.hpp>
#include <osmium/index/map/sparse_mem_array.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/visitor.hpp>
#include <pqxx/pqxx>

class MainHandler : public osmium::handler::Handler {
public:
    uint64_t nodes = 0;
    uint64_t ways = 0;
    uint64_t relations = 0;

    void node(osmium::Node& n) {
        if (ways > 0 || relations > 0) {
            std::cout << "not sorted" << "\n";
            exit(1);
        }
        nodes++;
    }

    void way(osmium::Way& way) {
        if (relations > 0) {
            std::cout << "not sorted" << "\n";
            exit(1);
        }
        ways++;
    }

    void relation(osmium::Relation&) { relations++; }
};

int main(int argc, char* argv[]) {
    try {
        pqxx::connection db_connect{
                "postgresql://postgres:serverobotics@localhost:5432/"
                "serve_postgis"};
        pqxx::work pxx_work{db_connect};
        pqxx::result pxx_results =
                pxx_work.exec("SELECT osm_id, tags FROM planet_osm_roads;");
        pxx_work.commit();
        for (const pqxx::row& pxx_result : pxx_results) {
            std::cout << "Node ID: " << pxx_result["osm_id"].as<std::int32_t>()
                      << ", Tags: " << pxx_result["tags"].as<std::string>()
                      << std::endl;
        }
        // osmium::io::Reader reader(pxx_result[0][0].as<std::string>());
        // MainHandler handler;
        // osmium::apply(reader, handler);
        // reader.close();
        // std::cout << "sorted" << std::endl;
    } catch (const std::exception& except) {
        std::cerr << except.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
