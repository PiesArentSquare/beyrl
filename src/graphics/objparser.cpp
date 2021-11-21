#include "objparser.hpp"

#include <fstream>

namespace beyrl {

    std::vector<std::string> split(std::string s, char delim = ' ') {
        size_t pos = 0;
        std::vector<std::string> tokens;
        while ((pos = s.find(delim)) != std::string::npos) {
            tokens.push_back(s.substr(0, pos));
            s.erase(0, pos + 1);
        }
        tokens.push_back(s);
        return tokens;
    }

    void obj_parser::parseVertex(std::string vertex) {
        if (vertexCache.find(vertex) != vertexCache.end())
            indices.push_back(vertexCache[vertex]);
        else {
            auto vertexComponents = split(vertex, '/');
            Vec3f position = positions[std::stoi(vertexComponents[0]) - 1]; // -1 because obj's count from 1 -\_(:/)_/-
            Vec2f uv;
            if (vertexComponents.size() > 1 && !vertexComponents[1].empty())
                uv = uvs[std::stoi(vertexComponents[1]) - 1];
            Vec3f normal;
            if (vertexComponents.size() > 2 && !vertexComponents[2].empty())
                normal = normals[std::stoi(vertexComponents[2]) - 1];

            obj_vertex v = {position, uv, normal};
            vertices.push_back(v);
            indices.push_back(vertexCache.size());
            vertexCache.insert({vertex, static_cast<unsigned>(vertexCache.size())});
        }
    }

    std::pair<std::vector<obj_vertex>, std::vector<unsigned>> obj_parser::parse(std::string const &objPath) {
        std::ifstream objFile(objPath);
        if (!objFile) {
            std::cerr << "obj error: file '" << objPath << "' could not be read\n";
            return {};
        }

        try {
            std::string line;
            while (std::getline(objFile, line)) {
                auto tokens = split(line);
                if (tokens[0] == "v")
                    positions.push_back({std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])});
                else if (tokens[0] == "vt")
                    uvs.push_back({std::stof(tokens[1]), std::stof(tokens[2])});
                else if (tokens[0] == "vn")
                    normals.push_back({std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])});
                else if (tokens[0] == "f") {
                    parseVertex(tokens[1]);
                    parseVertex(tokens[2]);
                    parseVertex(tokens[3]);
                }
            }
        } catch(std::out_of_range e) {
            std::cerr << "obj error: malformed file\n";
        }

        objFile.close();

        return std::make_pair(vertices, indices);

    }

}
