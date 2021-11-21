#pragma once

#include <beyrl/graphics/vertex_layout.hpp>

#include <vector>
#include <unordered_map>

namespace beyrl {

    struct obj_vertex {
        beyrl::Vec3f position;
        beyrl::Vec2f uv;
        beyrl::Vec3f normal;
    };

    const static_layout obj_layout = layout(obj_vertex{}.position, obj_vertex{}.uv, obj_vertex{}.normal);

    class obj_parser {

        std::vector<Vec3f> positions;
        std::vector<Vec2f> uvs;
        std::vector<Vec3f> normals;

        std::unordered_map<std::string, unsigned> vertexCache;
        
        std::vector<obj_vertex> vertices;
        std::vector<unsigned> indices;

        void parseVertex(std::string vertex);
    public:

        std::pair<std::vector<obj_vertex>, std::vector<unsigned>> parse(std::string const &objPath);
    };

}