#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"


void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
    
	std::vector<int> indices;
    std::vector<Vec3f> vertices;
    std::ifstream file;
    
    file.open(fileName);
    if (!file.is_open()){
        std::cerr << "Error while opening the file " << std::endl;
        return;
    }

    char c = file.get();

    while(c != EOF){
        if (c == 'v'){ // vertices
            Vec3f vertex;
            float p1, p2 ,p3;
            file >> p1 >> p2 >> p3;

            vertex[0] = p1 * 100.00f;
            vertex[1] = p2 * 100.00f;
            vertex[2] = p3 * 100.00f;

            vertices.push_back(vertex);
        }

        else if (c == 'f'){ // faces

            int indexArray[3];
            int p1, p2, p3;

            file >> p1 >> p2 >> p3;

            indexArray[0] = p1;
            indexArray[1] = p2;
            indexArray[2] = p3;

            indices.push_back(indexArray[0]);
            indices.push_back(indexArray[1]);
            indices.push_back(indexArray[2]);
        }

        c = file.get();
    }

    for (int i = 0; i < indices.size(); i = i){
        Vec3f vec1,vec2,vec3;

        vec1 = vertices[--indices[i]];
        i++;

        vec2 = vertices[--indices[i]];
        i++;

        vec3 = vertices[--indices[i]];
        i++;

        Add(std::make_shared<CPrimTriangle>(vec1, vec2, vec3, pShader));
    }

    file.close();

	std::cout << "Finished Parsing" << std::endl;
}

