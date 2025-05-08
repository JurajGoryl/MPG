#include "GL/glew.h"

#include "../include/display.h"
#include "../include/objects.h"
#include "../include/init.h"
#include "../include/input.h"
#include "../include/utils.h"
#include "../include/globals.h"

#include <cmath>
#include <GL/glut.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glext.h>   
#include <vector>
#include <algorithm>


using namespace std;


void DrawPlane(int size)
{
    glPushMatrix();
    glTranslatef(0, -15, 0);

    GLfloat floorAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat floorDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, floorAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, floorDiffuse);
    if (texturesEnabled) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, coble); 
 
    } else {
        glDisable(GL_TEXTURE_2D);
    }
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0); // Normála smeruje hore
    glTexCoord2f(0.0f, 0.0f); glVertex3i(-size, 0, size);
    glTexCoord2f(0.0f, 1.0f); glVertex3i(-size, 0, -size);
    glTexCoord2f(1.0f, 1.0f); glVertex3i(size , 0, -size);
    glTexCoord2f(1.0f, 0.0f); glVertex3i(size , 0, size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

GLfloat wallVertices[] = {
    0.0f, 0.0f, 0.0f,
    200.0f, 0.0f, 0.0f,
    200.0f, 50.0f, 0.0f,
    0.0f, 50.0f, 0.0f
};


void DrawWall(float nx, float ny, float nz)
{
    GLfloat wallAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat wallDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, wallAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wallDiffuse);


    if (texturesEnabled) {
   
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, cobleWall);

    } else {
        glDisable(GL_TEXTURE_2D);
    }

    glBegin(GL_QUADS);
    glNormal3f(nx, ny, nz);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(200.0f, 0.0f, 0.0f);
    glTexCoord2f(4.0f, 2.0f); glVertex3f(200.0f, 50.0f, 0.0f);
    glTexCoord2f(0.0f, 2.0f); glVertex3f(0.0f, 50.0f, 0.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void DrawAllWalls()
{
     
    glPushMatrix();
    glTranslatef(100.0f, 0.0f, -100.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, -15, 0);
    DrawWall(0, 0, -1); 
    glPopMatrix();

    
    glPushMatrix();
    glTranslatef(-100.0f, 0.0f, 100.0f);
    glTranslatef(0, -15, 0);
    DrawWall(0, 0, -1);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(100.0f, 0.0f, 100.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, -15, 0);
    DrawWall(0, 0, -1);
    glPopMatrix();

   
    glPushMatrix();
    glTranslatef(-100.0f, 0.0f, -100.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, -15, 0);
    DrawWall(0, 0, -1); 
    glPopMatrix();
}

void DrawWallCollisionBounds() {
   glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    glLineWidth(2.0f);
    
    for (int i = 0; i < 4; i++) {
        Wall wall = Walls[i];
        glBegin(GL_LINE_LOOP);
        
        if (i == 0 || i == 1) { 
            float z = wall.point[2];
            glVertex3f(wall.point[0] - wall.width/2, wall.point[1], z);
            glVertex3f(wall.point[0] + wall.width/2, wall.point[1], z);
            glVertex3f(wall.point[0] + wall.width/2, wall.point[1] + wall.height, z);
            glVertex3f(wall.point[0] - wall.width/2, wall.point[1] + wall.height, z);
        } else { // Left/right walls
            float x = wall.point[0];
            glVertex3f(x, wall.point[1], wall.point[2] - wall.width/2);
            glVertex3f(x, wall.point[1], wall.point[2] + wall.width/2);
            glVertex3f(x, wall.point[1] + wall.height, wall.point[2] + wall.width/2);
            glVertex3f(x, wall.point[1] + wall.height, wall.point[2] - wall.width/2);
        }
        
        glEnd();
    }
    
    glEnable(GL_LIGHTING);
}

void LoadLampModel(const char* objPath) {
    std::ifstream file(objPath);
    if (!file.is_open()) {
        std::cerr << "Objek sa nenaloadil: " << objPath << std::endl;
        return;
    }

    std::vector<GLfloat> temp_vertices;
    std::vector<GLfloat> temp_normals;
    std::vector<GLfloat> temp_uvs;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {  // Vertex position
            GLfloat x, y, z;
            iss >> x >> y >> z;
            temp_vertices.push_back(x);
            temp_vertices.push_back(y);
            temp_vertices.push_back(z);
        } 
        else if (type == "vt") {  // Texture coordinate
            GLfloat u, v;
            iss >> u >> v;
            temp_uvs.push_back(u);
            temp_uvs.push_back(v);
        }
        else if (type == "vn") {  // Vertex normal
            GLfloat nx, ny, nz;
            iss >> nx >> ny >> nz;
            temp_normals.push_back(nx);
            temp_normals.push_back(ny);
            temp_normals.push_back(nz);
        }
        else if (type == "f") {  // Face definition
            for (int i = 0; i < 3; i++) {  // Assuming triangles
                std::string face;
                iss >> face;
                
                std::replace(face.begin(), face.end(), '/', ' ');
                std::istringstream fiss(face);
                
                int vIdx, tIdx = -1, nIdx = -1;
                fiss >> vIdx;
                if (fiss >> tIdx) {
                    if (fiss >> nIdx) {
                        // All three indices present
                    } else {
                        // Only vertex and texture indices
                    }
                }
                
                // Adjust indices (OBJ uses 1-based indexing)
                vIdx--;
                if (tIdx > 0) tIdx--;
                if (nIdx > 0) nIdx--;
                
                // Push vertex
                if (vIdx >= 0 && vIdx*3+2 < temp_vertices.size()) {
                    streetLamp.vertices.push_back(temp_vertices[vIdx*3]);
                    streetLamp.vertices.push_back(temp_vertices[vIdx*3+1]);
                    streetLamp.vertices.push_back(temp_vertices[vIdx*3+2]);
                }
                
                // Push texture coordinate if available
                if (tIdx >= 0 && tIdx*2+1 < temp_uvs.size()) {
                    streetLamp.uvs.push_back(temp_uvs[tIdx*2]);
                    streetLamp.uvs.push_back(temp_uvs[tIdx*2+1]);
                }
                
                // Push normal if available
                if (nIdx >= 0 && nIdx*3+2 < temp_normals.size()) {
                    streetLamp.normals.push_back(temp_normals[nIdx*3]);
                    streetLamp.normals.push_back(temp_normals[nIdx*3+1]);
                    streetLamp.normals.push_back(temp_normals[nIdx*3+2]);
                }
            }
        }
    }
    
    file.close();
    
    // If no UVs were loaded, generate simple ones
    if (streetLamp.uvs.empty()) {
        std::cout << "Generating simple UV coordinates" << std::endl;
        for (size_t i = 0; i < streetLamp.vertices.size(); i += 3) {
            // Simple planar projection
            float u = streetLamp.vertices[i] / 10.0f;  // Adjust scale as needed
            float v = streetLamp.vertices[i+1] / 10.0f;
            streetLamp.uvs.push_back(u);
            streetLamp.uvs.push_back(v);
        }
    }
    
    std::cout << "Loaded lamp model with " << streetLamp.vertices.size()/3 
              << " vertices and " << streetLamp.uvs.size()/2 << " UV coordinates" << std::endl;
}

void SetupLampBuffers() {
    glGenVertexArrays(1, &streetLamp.VAO);
    glGenBuffers(3, streetLamp.VBO);  // 0: vertices, 1: normals, 2: UVs
    
    glBindVertexArray(streetLamp.VAO);
    
    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, streetLamp.VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, 
                streetLamp.vertices.size() * sizeof(GLfloat),
                streetLamp.vertices.data(), 
                GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
    
    // Normals (if available)
    if (!streetLamp.normals.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, streetLamp.VBO[1]);
        glBufferData(GL_ARRAY_BUFFER,
                    streetLamp.normals.size() * sizeof(GLfloat),
                    streetLamp.normals.data(),
                    GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);
    }
    
    // UVs (if available)
    if (!streetLamp.uvs.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, streetLamp.VBO[2]);
        glBufferData(GL_ARRAY_BUFFER,
                    streetLamp.uvs.size() * sizeof(GLfloat),
                    streetLamp.uvs.data(),
                    GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(2);
    }
    
    glBindVertexArray(0);
}
void DrawLamp(int lightNumber = -1) {
    // Metal material properties
    GLfloat matAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat matDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matShininess = 128.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    // Draw lamp post
    glBindVertexArray(streetLamp.VAO);
    glDrawArrays(GL_TRIANGLES, 0, streetLamp.vertices.size() / 3);
    
    // Bulb properties
    if(lightNumber >= 0) {
        GLfloat emitColor[] = {1.0f, 0.9f, 0.8f, 1.0f}; // Matches light color
        glMaterialfv(GL_FRONT, GL_EMISSION, emitColor);
        
        glPushMatrix();
        glTranslatef(2, -1, 0); // Adjust to bulb position in your model
        glutSolidSphere(3.0, 16, 16); // High-quality bulb
        glPopMatrix();
        
        GLfloat noEmit[] = {0,0,0,1};
        glMaterialfv(GL_FRONT, GL_EMISSION, noEmit);
    }
    
    glBindVertexArray(0);
}
void DrawLamps() {
    GLfloat lampAmbient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
    //GLfloat lampDiffuse[]  = {1.0f, 0.9f, 0.8f, 1.0f};
    //GLfloat lampSpecular[] = {1.0f, 0.9f, 0.8f, 1.0f};
    GLfloat lampDiffuse[]  = {lightBrightness, lightBrightness, lightBrightness, 1.0f};
    GLfloat lampSpecular[] = {lightBrightness, lightBrightness, lightBrightness, 1.0f}; 
    float bulbYOffset = 27.0f;

     // Lampa 1
     glPushMatrix();
     glTranslatef(80, 0, 80);
     glRotatef(135, 0, 1, 0);
     glTranslatef(0, bulbYOffset, 0);
     GLfloat lightPos1[] = {0, 0, 0, 1.0f};
     glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
     glLightfv(GL_LIGHT1, GL_AMBIENT, lampAmbient);
     glLightfv(GL_LIGHT1, GL_DIFFUSE, lampDiffuse);
     glLightfv(GL_LIGHT1, GL_SPECULAR, lampSpecular);
     glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.00f);
     glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.008f);
     glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0005f);
     glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0f);
     glEnable(GL_LIGHT1);
     DrawLamp(1);
     glPopMatrix();
  

    // Lampa 2
    glPushMatrix();
    glTranslatef(80, 0, -80);
    glRotatef(-135, 0, 1, 0);
    glTranslatef(0, bulbYOffset, 0);
    GLfloat lightPos2[] = {0, 0, 0, 1.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, lampAmbient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lampDiffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lampSpecular);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.00f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.008f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0005f);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 180.0f);
    glEnable(GL_LIGHT2);
    DrawLamp(2);
    glPopMatrix();

    // Lampa 4
    glPushMatrix();
    glTranslatef(-80, 0, -80);
    glRotatef(-45, 0, 1, 0);
    glTranslatef(0, bulbYOffset, 0);
    GLfloat lightPos4[] = {0, 0, 0, 1.0f};
    glLightfv(GL_LIGHT4, GL_POSITION, lightPos4);
    glLightfv(GL_LIGHT4, GL_AMBIENT, lampAmbient);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, lampDiffuse);
    glLightfv(GL_LIGHT4, GL_SPECULAR, lampSpecular);
    glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.00f);
    glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.008f);
    glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.0005f);
    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 180.0f);
    glEnable(GL_LIGHT4);
    DrawLamp(4);
    glPopMatrix();
}

GLfloat boxTexCoords[] = {
    // Front face
    0,1, 1,1, 1,0,
    0,1, 1,0, 0,0,

    // Back face
    1,0, 0,0, 0,1,
    1,0, 0,1, 1,1,

    // Left face
    1,1, 0,1, 0,0,
    1,1, 0,0, 1,0,

    // Right face
    0,0, 1,0, 1,1,
    0,0, 1,1, 0,1,

    // Top face
    0,0, 1,0, 1,1,
    0,0, 1,1, 0,1,

    // Bottom face
    1,1, 0,1, 0,0,
    1,1, 0,0, 1,0
};

GLfloat boxVertices[] = {
    // Front face (2 triangles)
    -10, 10, 10,   10, 10, 10,   10, -10, 10,   // Triangle 1
    -10, 10, 10,   10, -10, 10,   -10, -10, 10,  // Triangle 2
    
    // Back face
    -10, -10, -10,  10, -10, -10,  10, 10, -10,  // Triangle 1
    -10, -10, -10,  10, 10, -10,  -10, 10, -10,  // Triangle 2
    
    // Left face
    -10, 10, -10,   -10, 10, 10,   -10, -10, 10, // Triangle 1
    -10, 10, -10,   -10, -10, 10,   -10, -10, -10, // Triangle 2
    
    // Right face
    10, -10, -10,  10, -10, 10,  10, 10, 10,     // Triangle 1
    10, -10, -10,  10, 10, 10,  10, 10, -10,     // Triangle 2
    
    // Top face
    -10, 10, 10,   10, 10, 10,   10, 10, -10,    // Triangle 1
    -10, 10, 10,   10, 10, -10,   -10, 10, -10,  // Triangle 2
    
    // Bottom face
    -10, -10, 10,  10, -10, 10,  10, -10, -10,   // Triangle 1
    -10, -10, 10,  10, -10, -10,  -10, -10, -10  // Triangle 2
};

GLfloat boxNormals[] = {
    // Front face (6 normals - 2 per triangle)
    0,0,1, 0,0,1, 0,0,1, 0,0,1, 0,0,1, 0,0,1,
    // Back face
    0,0,-1, 0,0,-1, 0,0,-1, 0,0,-1, 0,0,-1, 0,0,-1,
    // Left face
    -1,0,0, -1,0,0, -1,0,0, -1,0,0, -1,0,0, -1,0,0,
    // Right face
    1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0, 1,0,0,
    // Top face
    0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0, 0,1,0,
    // Bottom face
    0,-1,0, 0,-1,0, 0,-1,0, 0,-1,0, 0,-1,0, 0,-1,0
};

void Box() {

    if (texturesEnabled) {
       
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, woodTextureID);
    } else {
        glDisable(GL_TEXTURE_2D);
    }
    

    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 36; i++) {  // 6 faces * 2 triangles * 3 vertices = 36
        glNormal3fv(&boxNormals[i*3]);
        glTexCoord2fv(&boxTexCoords[i*2]);
        glVertex3fv(&boxVertices[i*3]);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


void DrawBox() {
    glPushMatrix();
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(75, -15, -75); 
    Box(); // Your existing box rendering
    glPopMatrix();
}


void GenerateWoodTexture()
{
    unsigned char data[WOOD_TEX_SIZE][WOOD_TEX_SIZE][3];

    for (int y = 0; y < WOOD_TEX_SIZE; ++y) {
        for (int x = 0; x < WOOD_TEX_SIZE; ++x) {
            float fx = x / (float)WOOD_TEX_SIZE;
            float fy = y / (float)WOOD_TEX_SIZE;
            
            // Hlavné prstence
            float ring_pattern = 0.5f + 0.5f * sinf(20.0f * fx + 5.0f * sinf(3.0f * fy));
            
            // Vlákna (viac frekvencií)
            float grain = 0.3f*sinf(100*fy + 60*fx) 
                        + 0.15f*sinf(250*fy + 150*fx);
            
            // Škvrny
            float knots = 0.0f;
            if (sinf(15*fx)*sinf(15*fy) > 0.9f) {
                knots = 0.3f * (sinf(40*fx)*sinf(40*fy));
            }
            
            float wood = ring_pattern + grain + knots;
            
            // Nelineárna farebná transformácia
            float r = 90 + 60 * sqrtf(fabsf(wood));
            float g = 40 + 35 * wood;
            float b = 15 + 10 * wood * wood;
            
            // Kontrast
            wood = powf((wood + 1.0f)/2.0f, 1.5f);
            
            data[y][x][0] = (GLubyte)fmax(0, fmin(255, r));
            data[y][x][1] = (GLubyte)fmax(0, fmin(255, g));
            data[y][x][2] = (GLubyte)fmax(0, fmin(255, b));
        }
    }

    glGenTextures(1, &woodTextureID);
    if (texturesEnabled) {

        glBindTexture(GL_TEXTURE_2D, woodTextureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WOOD_TEX_SIZE, WOOD_TEX_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    } else {
        glDisable(GL_TEXTURE_2D);
    }
    

}
void WindowObject() {
    // Disable backface culling (optional for full visibility)
    glDisable(GL_CULL_FACE);

    glDisable(GL_BLEND);        // No blending for opaque
    glDepthMask(GL_TRUE);       // Write to depth buffer

    GLfloat frameColor[] = {0.4f, 0.2f, 0.1f, 1.0f}; // Fully opaque wood
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, frameColor);

    struct Bar {
        GLfloat x0, y0, z0;
        GLfloat x1, y1, z1;
    };

    Bar bars[] = {
        {0.0f, 0.0f, -0.2f, 0.2f, 2.0f, 0.0f},    // Left
        {1.8f, 0.0f, -0.2f, 2.0f, 2.0f, 0.0f},    // Right
        {0.2f, 1.8f, -0.2f, 1.8f, 2.0f, 0.0f},    // Top
        {0.2f, 0.0f, -0.2f, 1.8f, 0.2f, 0.0f}     // Bottom
    };

    for (int b = 0; b < 4; ++b) {
        Bar bar = bars[b];
        GLfloat x0 = bar.x0, y0 = bar.y0, z0 = bar.z0;
        GLfloat x1 = bar.x1, y1 = bar.y1, z1 = bar.z1;

        glBegin(GL_TRIANGLES);
        // Front face
        glNormal3f(0, 0, 1);
        glVertex3f(x0, y0, z1); glVertex3f(x1, y0, z1); glVertex3f(x1, y1, z1);
        glVertex3f(x0, y0, z1); glVertex3f(x1, y1, z1); glVertex3f(x0, y1, z1);

        // Back face
        glNormal3f(0, 0, -1);
        glVertex3f(x1, y0, z0); glVertex3f(x0, y0, z0); glVertex3f(x0, y1, z0);
        glVertex3f(x1, y0, z0); glVertex3f(x0, y1, z0); glVertex3f(x1, y1, z0);

        // Left face
        glNormal3f(-1, 0, 0);
        glVertex3f(x0, y0, z0); glVertex3f(x0, y0, z1); glVertex3f(x0, y1, z1);
        glVertex3f(x0, y0, z0); glVertex3f(x0, y1, z1); glVertex3f(x0, y1, z0);

        // Right face
        glNormal3f(1, 0, 0);
        glVertex3f(x1, y0, z1); glVertex3f(x1, y0, z0); glVertex3f(x1, y1, z0);
        glVertex3f(x1, y0, z1); glVertex3f(x1, y1, z0); glVertex3f(x1, y1, z1);

        // Top face
        glNormal3f(0, 1, 0);
        glVertex3f(x0, y1, z1); glVertex3f(x1, y1, z1); glVertex3f(x1, y1, z0);
        glVertex3f(x0, y1, z1); glVertex3f(x1, y1, z0); glVertex3f(x0, y1, z0);

        // Bottom face
        glNormal3f(0, -1, 0);
        glVertex3f(x0, y0, z0); glVertex3f(x1, y0, z0); glVertex3f(x1, y0, z1);
        glVertex3f(x0, y0, z0); glVertex3f(x1, y0, z1); glVertex3f(x0, y0, z1);
        glEnd();
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE); // Prevent writing to depth buffer (so glass doesn't obscure frame)

    GLfloat glassColor[] = {0.5f, 0.8f, 1.0f, 0.3f}; // Semi-transparent glass
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, glassColor);

    glBegin(GL_TRIANGLES);
    // Front face (Z = -0.05)
    glNormal3f(0, 0, 1);
    glVertex3f(0.25f, 0.25f, -0.05f);
    glVertex3f(1.75f, 0.25f, -0.05f);
    glVertex3f(1.75f, 1.75f, -0.05f);
    glVertex3f(0.25f, 0.25f, -0.05f);
    glVertex3f(1.75f, 1.75f, -0.05f);
    glVertex3f(0.25f, 1.75f, -0.05f);

    // Back face (Z = -0.15)
    glNormal3f(0, 0, -1);
    glVertex3f(1.75f, 0.25f, -0.15f);
    glVertex3f(0.25f, 0.25f, -0.15f);
    glVertex3f(0.25f, 1.75f, -0.15f);
    glVertex3f(1.75f, 0.25f, -0.15f);
    glVertex3f(0.25f, 1.75f, -0.15f);
    glVertex3f(1.75f, 1.75f, -0.15f);
    glEnd();

    glDepthMask(GL_TRUE);  // Restore depth buffer writes
    glDisable(GL_BLEND);   // Turn off blending after glass
}

void AnimateObject() {

    glPushMatrix();

    // Move to window center, rotate, move back
    glTranslatef(1.0f, 1.0f, -0.1f);      // Move origin to window center
    glRotatef(animateAngle, 0, 1, 0);      // Rotate around Y axis
    glTranslatef(-1.0f, -1.0f, 0.1f);     // Move origin back

    // Now draw the window at (0,0,0) as usual
    WindowObject();

    glPopMatrix();
   
}

void DrawWindowObject() {
    glPushMatrix();
    glScalef(2,2,2);
    glTranslatef(17.7, 0, -18.5);
    AnimateObject();
    glPopMatrix();
}

void OnIdle() {
    if (animationRunning) {
    animateAngle += 0.5f; // degrees per frame, adjust speed as needed
    if(animateAngle >= 360.0f) animateAngle -= 360.0f;
    glutPostRedisplay();
    }

    if (thrownObject.active) {
        if (!thrownObject.falling) {
            // Simulácia letu
            thrownObject.x += thrownObject.vx;
            thrownObject.y += thrownObject.vy;
            thrownObject.z += thrownObject.vz;
    
            // Kolízia so stenami
            if (!CanMoveTo(thrownObject.x, thrownObject.y, thrownObject.z)) {
                thrownObject.falling = true;
                thrownObject.vx = 0;
                thrownObject.vz = 0;
            }
        } else {
            // Padanie dole
            thrownObject.y -= 0.3f; // gravitácia
            if (thrownObject.y <= -15.0f) {  // zem
                thrownObject.y = -15.0f;
                thrownObject.active = false;
            }
        }
    }
}


