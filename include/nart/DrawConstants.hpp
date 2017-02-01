#pragma once

#include "Typedef.hpp"
#include <vector>

#ifdef NART_GLM_EXTENSIONS
#include <glm/glm.hpp>
#endif

namespace nart {
    
    class Texture2D;
    
    class DrawConstants {
    public:
        struct Item {
            struct Type {
                enum Enum {
                    Float = 2,
                    Vector2 = 3,
                    Vector3 = 4,
                    Vector4 = 5,
                    Matrix2 = 6,
                    Matrix3 = 7,
                    Matrix4 = 8,
                    Texture2D = 20,
                };
            };
            
            ShaderProgram::UniformBinding binding;
            Type::Enum type;
            union RawData {
                float floatData[16];
            };
            RawData rawData;
            Ref<Texture2D> texture2d;
        };
    private:
        std::vector<Item> items;
    protected:
        friend class Renderer;
        const std::vector<Item>& getItems() const { return items; }
    public:
        DrawConstants() {}
        DrawConstants& item(const Item& item) {
            items.push_back(item);
            return *this;
        }
#ifdef NART_GLM_EXTENSIONS
        DrawConstants& item(ShaderProgram::UniformBinding binding, float value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Float;
            item.rawData.floatData[0] = value;
            return *this;
        }
        DrawConstants& item(ShaderProgram::UniformBinding binding, glm::vec2 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Vector2;
            item.rawData.floatData[0] = value.x;
            item.rawData.floatData[1] = value.y;
            return *this;
        }
        DrawConstants& item(ShaderProgram::UniformBinding binding, glm::vec3 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Vector3;
            item.rawData.floatData[0] = value.x;
            item.rawData.floatData[1] = value.y;
            item.rawData.floatData[2] = value.z;
            return *this;
        }
        DrawConstants& item(ShaderProgram::UniformBinding binding, glm::vec4 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Vector4;
            item.rawData.floatData[0] = value.x;
            item.rawData.floatData[1] = value.y;
            item.rawData.floatData[2] = value.z;
            item.rawData.floatData[3] = value.a;
            return *this;
        }
        DrawConstants& item(ShaderProgram::UniformBinding binding, glm::mat2 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Matrix2;
            memcpy(item.rawData.floatData, &value[0][0], sizeof(float) * 4);
            return *this;
        }
        DrawConstants& item(ShaderProgram::UniformBinding binding, glm::mat3 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Matrix3;
            memcpy(item.rawData.floatData, &value[0][0], sizeof(float) * 9);
            return *this;
        }
        DrawConstants& item(ShaderProgram::UniformBinding binding, glm::mat4 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Matrix4;
            memcpy(item.rawData.floatData, &value[0][0], sizeof(float) * 16);
            return *this;
        }
#endif
        DrawConstants& item(ShaderProgram::UniformBinding binding, const Ref<Texture2D> texture) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Texture2D;
            item.texture2d = texture;
            return *this;
        }
    };

    
}
