#include "lab_m1/Tema3/Tema3.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema3::Tema3()
{
}


Tema3::~Tema3()
{
}


void Tema3::Init()
{
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "textures");

    // Load textures
    
    {
        mapTextures["random"] = CreateRandomTexture(25, 25);
    }

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "moon.png").c_str(), GL_REPEAT);
        mapTextures["moon"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "wood.png").c_str(), GL_REPEAT);
        mapTextures["wood"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "grass.png").c_str(), GL_REPEAT);
        mapTextures["grass"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "cement.png").c_str(), GL_REPEAT);
        mapTextures["cement"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "waterrr.png").c_str(), GL_REPEAT);
        mapTextures["waterrr"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "steag.png").c_str(), GL_REPEAT);
        mapTextures["steag"] = texture;
    }
    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "noise.png").c_str(), GL_REPEAT);
        mapTextures["noise"] = texture;
    }

    // Load meshes

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("insula");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "insula.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("far");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "far.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("corpvapor");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "corpvapor.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cilindruvapor");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cilindruvapor.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("panzevapor");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "panzevapor.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("steagvapor");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "steagvapor.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("steagvapor2");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "steagvapor2.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("apaa");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "apaa.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }


    // Create a simple quad
    {
        vector<glm::vec3> vertices
        {
            glm::vec3(0.5f,   0.5f, 0.0f),    // top right
            glm::vec3(0.5f,  -0.5f, 0.0f),    // bottom right
            glm::vec3(-0.5f, -0.5f, 0.0f),    // bottom left
            glm::vec3(-0.5f,  0.5f, 0.0f),    // top left
        };

        vector<glm::vec3> normals
        {
            glm::vec3(0, 1, 1),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0),
            glm::vec3(0, 1, 0)
        };

        vector<glm::vec2> textureCoords
        {
            // TODO(student): Complete texture coordinates for the square
            glm::vec2(1.0f, 0.0f),
            glm::vec2(1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f),
            glm::vec2(0.0f, 0.0f)

        };

        vector<unsigned int> indices =
        {
            0, 1, 3,
            1, 2, 3
        };

        Mesh* mesh = new Mesh("square");
        mesh->InitFromData(vertices, normals, textureCoords, indices);
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema3", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}


void Tema3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema3::Update(float deltaTimeSeconds)
{

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-7, 5, -15));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2));
        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, mapTextures["moon"]);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["insula"], shaders["LabShader"], modelMatrix, mapTextures["grass"]);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["far"], shaders["LabShader"], modelMatrix, mapTextures["cement"]);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["apaa"], shaders["LabShader"], modelMatrix, mapTextures["waterrr"]);
    }


   

    //VAPOR1
    angle += -1 * deltaTimeSeconds;

    // Calculul noii pozitii pe cerc
    float radius = 1.5f; // Raza cercului
    glm::vec3 center(0, 0, -3); // Centrul cercului
    float x = center.x + radius * cos(angle);
    float z = center.z + radius * sin(angle);
    glm::vec3 newPosition(x, 0, z); // Noua pozitie pe cerc

    // Calculul directiei de miscare
    glm::vec3 direction = glm::normalize(newPosition - center);

    // Orientarea vaporului
    glm::vec3 forward = glm::normalize(-direction);

    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::cross(up, forward);
    up = glm::cross(forward, right);

    glm::mat4 rotationMatrix = glm::mat4(glm::vec4(right, 0), glm::vec4(up, 0), glm::vec4(forward, 0), glm::vec4(0, 0, 0, 1));

    // Aplicarea transformarilor
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1), newPosition) * rotationMatrix;
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));

    RenderSimpleMesh(meshes["corpvapor"], shaders["LabShader"], modelMatrix, mapTextures["wood"]);
    RenderSimpleMesh(meshes["cilindruvapor"], shaders["LabShader"], modelMatrix, mapTextures["wood"]);
    RenderSimpleMesh(meshes["panzevapor"], shaders["LabShader"], modelMatrix, mapTextures["noise"]);
    RenderSimpleMesh(meshes["steagvapor"], shaders["LabShader"], modelMatrix, mapTextures["steag"]);


    //VAPOR2
    angle2 += deltaTimeSeconds;

    // Calculul noii pozitii pe cerc
    float radius2 = 2.5f; // Seteaza raza cercului
    glm::vec3 center2(0, 0, -3); // Centrul cercului
    float x2 = center2.x + radius2 * cos(angle2);
    float z2 = center2.z + radius2 * sin(angle2);
    glm::vec3 newPosition2(x2, 0, z2); // Noua pozitie pe cerc

    // Calculul directiei de miscare
    glm::vec3 direction2 = glm::normalize(newPosition2 - center2);

    // Orientarea vaporului
    glm::vec3 forward2 = glm::normalize(-direction2);
    glm::vec3 up2 = glm::vec3(0, 1, 0);
    glm::vec3 right2 = glm::cross(up2, forward2);
    up2 = glm::cross(forward2, right2);

    glm::mat4 rotationMatrix2 = glm::mat4(glm::vec4(right2, 0), glm::vec4(up2, 0), glm::vec4(forward2, 0), glm::vec4(0, 0, 0, 1));

    // Aplicarea transformarilor
    glm::mat4 modelMatrix2 = glm::translate(glm::mat4(1), newPosition2) * rotationMatrix2;
    modelMatrix2 = glm::scale(modelMatrix2, glm::vec3(0.2f));

    RenderSimpleMesh(meshes["corpvapor"], shaders["LabShader"], modelMatrix2, mapTextures["wood"]);
    RenderSimpleMesh(meshes["cilindruvapor"], shaders["LabShader"], modelMatrix2, mapTextures["wood"]);
    RenderSimpleMesh(meshes["panzevapor"], shaders["LabShader"], modelMatrix2, mapTextures["noise"]);
    RenderSimpleMesh(meshes["steagvapor2"], shaders["LabShader"], modelMatrix2, mapTextures["steag"]);

    //VAPOR3
    angle3 += -1 * deltaTimeSeconds;

    // Calculul noii pozitii pe cerc
    float radius3 = 3.5f; // Seteaza raza cercului
    glm::vec3 center3(0, 0, -3); // Centrul cercului
    float x3 = center3.x + radius3 * cos(angle3);
    float z3 = center3.z + radius3 * sin(angle3);
    glm::vec3 newPosition3(x3, 0, z3); // Noua pozitie pe cerc

    // Calculul directiei de miscare
    glm::vec3 direction3 = glm::normalize(newPosition3 - center3);

    // Orientarea vaporului
    glm::vec3 forward3 = glm::normalize(-direction3);
    glm::vec3 up3 = glm::vec3(0, 1, 0);
    glm::vec3 right3 = glm::cross(up3, forward3);
    up3 = glm::cross(forward3, right3);

    glm::mat4 rotationMatrix3 = glm::mat4(glm::vec4(right3, 0), glm::vec4(up3, 0), glm::vec4(forward3, 0), glm::vec4(0, 0, 0, 1));

    // Aplicarea transformarilor
    glm::mat4 modelMatrix3 = glm::translate(glm::mat4(1), newPosition3) * rotationMatrix3;
    modelMatrix3 = glm::scale(modelMatrix3, glm::vec3(0.2f));

    RenderSimpleMesh(meshes["corpvapor"], shaders["LabShader"], modelMatrix3, mapTextures["wood"]);
    RenderSimpleMesh(meshes["cilindruvapor"], shaders["LabShader"], modelMatrix3, mapTextures["wood"]);
    RenderSimpleMesh(meshes["panzevapor"], shaders["LabShader"], modelMatrix3, mapTextures["noise"]);
    RenderSimpleMesh(meshes["steagvapor"], shaders["LabShader"], modelMatrix3, mapTextures["steag"]);

    //VAPOR4
    angle4 += deltaTimeSeconds;

    // Calculul noii pozitii pe cerc
    float radius4 = 4.5f; // Seteaza raza cercului
    glm::vec3 center4(0, 0, -3); // Centrul cercului
    float x4 = center4.x + radius4 * cos(angle4);
    float z4 = center4.z + radius4 * sin(angle4);
    glm::vec3 newPosition4(x4, 0, z4); // Noua pozitie pe cerc

    // Calculul directiei de miscare
    glm::vec3 direction4 = glm::normalize(newPosition4 - center4);

    // Orientarea vaporului
    glm::vec3 forward4 = glm::normalize(-direction4);
    glm::vec3 up4 = glm::vec3(0, 1, 0);
    glm::vec3 right4 = glm::cross(up4, forward4);
    up4 = glm::cross(forward4, right4);

    glm::mat4 rotationMatrix4 = glm::mat4(glm::vec4(right4, 0), glm::vec4(up4, 0), glm::vec4(forward4, 0), glm::vec4(0, 0, 0, 1));

    // Aplicarea transformarilor
    glm::mat4 modelMatrix4 = glm::translate(glm::mat4(1), newPosition4) * rotationMatrix4;
    modelMatrix4 = glm::scale(modelMatrix4, glm::vec3(0.2f));

    RenderSimpleMesh(meshes["corpvapor"], shaders["LabShader"], modelMatrix4, mapTextures["wood"]);
    RenderSimpleMesh(meshes["cilindruvapor"], shaders["LabShader"], modelMatrix4, mapTextures["wood"]);
    RenderSimpleMesh(meshes["panzevapor"], shaders["LabShader"], modelMatrix4, mapTextures["noise"]);
    RenderSimpleMesh(meshes["steagvapor2"], shaders["LabShader"], modelMatrix4, mapTextures["steag"]);
}


void Tema3::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // TODO(student): Set any other shader uniforms that you need
    int loc_time = glGetUniformLocation(shader->program, "time");
    int loc_mix_value = glGetUniformLocation(shader->program, "mix_value");
    glUniform1i(loc_mix_value, 0);

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);


    }

    if (texture2)
    {
        // TODO(student): Do these:
        // - activate texture location 1
        // - bind the texture2 ID
        // - send the uniform value
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);


    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
    GLuint textureID = 0;
    unsigned int channels = 3;
    unsigned int size = width * height * channels;
    unsigned char* data = new unsigned char[size];

    // TODO(student): Generate random texture data
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 256;
    }

    // TODO(student): Generate and bind the new texture ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }
    // TODO(student): Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();

    // Use glTexImage2D to set the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // TODO(student): Generate texture mip-maps
    glGenerateMipmap(GL_TEXTURE_2D);

    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema3::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    }
}


void Tema3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema3::OnWindowResize(int width, int height)
{
}
