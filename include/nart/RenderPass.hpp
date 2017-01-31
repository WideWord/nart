#pragma once

#include <vector>
#include <nart/Typedef.hpp>
#include <nart/ShaderProgram.hpp>
#include <memory>

#ifdef NART_GLM_EXTENSIONS
#include <glm/glm.hpp>
#endif

namespace nart {
    
    class VertexArray;
    class Renderer;
    class Texture2D;
    
    struct DrawCallOptions {
        DrawCallOptions() {}
    };
    
    class DrawConstantsBlock {
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
        DrawConstantsBlock() {}
        DrawConstantsBlock& item(const Item& item) {
            items.push_back(item);
            return *this;
        }
#ifdef NART_GLM_EXTENSIONS
        DrawConstantsBlock& item(ShaderProgram::UniformBinding binding, float value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Float;
            item.rawData.floatData[0] = value;
            return *this;
        }
        DrawConstantsBlock& item(ShaderProgram::UniformBinding binding, glm::vec2 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Vector2;
            item.rawData.floatData[0] = value.x;
            item.rawData.floatData[1] = value.y;
            return *this;
        }
        DrawConstantsBlock& item(ShaderProgram::UniformBinding binding, glm::vec3 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Vector3;
            item.rawData.floatData[0] = value.x;
            item.rawData.floatData[1] = value.y;
            item.rawData.floatData[2] = value.z;
            return *this;
        }
        DrawConstantsBlock& item(ShaderProgram::UniformBinding binding, glm::vec4 value) {
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
        DrawConstantsBlock& item(ShaderProgram::UniformBinding binding, glm::mat2 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Matrix2;
            memcpy(item.rawData.floatData, &value[0][0], sizeof(float) * 4);
            return *this;
        }
        DrawConstantsBlock& item(ShaderProgram::UniformBinding binding, glm::mat3 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Matrix3;
            memcpy(item.rawData.floatData, &value[0][0], sizeof(float) * 9);
            return *this;
        }
        DrawConstantsBlock& item(ShaderProgram::UniformBinding binding, glm::mat4 value) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Matrix4;
            memcpy(item.rawData.floatData, &value[0][0], sizeof(float) * 16);
            return *this;
        }
#endif
        DrawConstantsBlock& item(ShaderProgram::UniformBinding binding, const Ref<Texture2D> texture) {
            items.emplace_back();
            Item& item = items.back();
            item.binding = binding;
            item.type = Item::Type::Texture2D;
            item.texture2d = texture;
            return *this;
        }
    };
    
    class RenderPass {
    protected:
        struct DrawCall {
            Ref<VertexArray> vertexBuffer;
            Ref<ShaderProgram> shaderProgram;
            DrawConstantsBlock constants;
            DrawCallOptions options;
        };
    private:
        std::vector<DrawCall> drawCalls;
        bool needsClearColor;
        bool needsClearDepth;
        float clearColor[4];
    protected:
        friend class Renderer;
        const std::vector<DrawCall>& getDrawCalls() const { return drawCalls; }
    public:
        RenderPass() {
            needsClearColor = true;
            needsClearDepth = true;
            clearColor[0] = 0;
            clearColor[1] = 0;
            clearColor[2] = 0;
            clearColor[3] = 1;
        }
        
        void clear();
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawConstantsBlock& constants, const DrawCallOptions& options);
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram) {
            draw(vertexBuffer, shaderProgram, nart::DrawConstantsBlock(), nart::DrawCallOptions());
        }
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawConstantsBlock& constants) {
            draw(vertexBuffer, shaderProgram, constants, nart::DrawCallOptions());
        }
        
        void draw(const Ref<VertexArray>& vertexBuffer, const Ref<ShaderProgram>& shaderProgram, const DrawCallOptions& options) {
            draw(vertexBuffer, shaderProgram, nart::DrawConstantsBlock(), options);
        }
        
        void setNeedsClearColor(bool needs) {
            needsClearColor = needs;
        }
        
        bool isNeedsClearColor() const {
            return needsClearColor;
        }
        
        void setNeedsClearDepth(bool needs) {
            needsClearDepth = needs;
        }
        
        bool isNeedsClearDepth() const {
            return needsClearDepth;
        }
        
        void setClearColor(float red, float green, float blue, float alpha) {
            clearColor[0] = red;
            clearColor[1] = green;
            clearColor[2] = blue;
            clearColor[3] = alpha;
        }
        
        const float* getClearColor() const {
            return clearColor;
        }
    };
    
}
