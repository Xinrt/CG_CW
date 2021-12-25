#include "ObjLoader.h"
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

#include "../Framework/Engine/Scene.h"

ObjLoader::ObjLoader(string filename)
{
    string line;
    fstream f;

    f.open(filename, ios::in);

    if (!f.is_open()) {
        cout << "Something Went Wrong When Opening Objfiles" << endl;
    }

    while (!f.eof()) {

        getline(f, line);
        vector<string>parameters;
        string tailMark = " ";
        string ans = "";
        line = line.append(tailMark);

        for (int i = 0; i < line.length(); i++) {

            char ch = line[i];
            if (ch != ' ') {
                ans += ch;
            }
            else {
                parameters.push_back(ans);
                ans = "";
            }
        }

        //		if (parameters.size() != 4) {
        //			cout << "the size is not correct" << endl;
        //		}else {

        if (parameters[0] == "v") {

            vector<GLfloat>Point;

            for (int i = 1; i < 4; i++) {

                GLfloat xyz = atof(parameters[i].c_str());

                Point.push_back(xyz);
            }

            vSets.push_back(Point);

        }
        else if (parameters[0] == "f") {

            vector<GLint>vIndexSets;
            vector<GLint>vtIndexSets;
            vector<GLint>vnIndexSets;

            for (int i = 1; i < 4; i++) {  // for the 3 index of vertexs for one face
                string x = parameters[i];
                string ans = "";
                string ansVT = "";
                string ansVN = "";
                int count = 0;

                for (int j = 0; j < x.length(); j++) {
                    char ch = x[j];
                    if (ch != '/') {
                        if (count == 0) {
                            ans += ch;
                        } else if (count == 1) {
                            ansVT += ch;
                        } else {
                            ansVN += ch;
                        }
                    }
                    else {
                        if (count == 0) {
                            count++;
                        }
                        else if (count == 1) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }
                }

                GLint index = atof(ans.c_str());
                index = index--;
                vIndexSets.push_back(index);

                GLint indexVT = atof(ansVT.c_str());
                indexVT = indexVT--;
                vtIndexSets.push_back(indexVT);

                GLint indexVN = atof(ansVN.c_str());
                indexVN = indexVN--;
                vnIndexSets.push_back(indexVN);
            }
            fSets.push_back(vIndexSets);
            VTIndexSets.push_back(vtIndexSets);
            VNIndexSets.push_back(vnIndexSets);

        }
        else if (parameters[0] == "vn") {
            vector<GLfloat>vnValueSets;
            for (int i = 1; i < 4; i++) {
                GLfloat vnxyz = atof(parameters[i].c_str());
                vnValueSets.push_back(vnxyz);
            }
            vnSets.push_back(vnValueSets);

        }
        else if (parameters[0] == "vt") {
            vector<GLfloat>vtValueSets;
            for (int i = 1; i < 3; i++) {
                GLfloat vnxyz = atof(parameters[i].c_str());
                vtValueSets.push_back(vnxyz);
            }
            vtSets.push_back(vtValueSets);
        }

        //		}
    }
    //    cout << "f" << fSets.size();
    //    cout << "\nvn" << vnSets.size();
    //    cout << "\nvt" << vtSets.size();
    f.close();
}


void ObjLoader::Draw(){

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < fSets.size(); i++) {

        GLfloat VN[3];

        //three vertex represrnt a surface
        GLfloat SV1[3];
        GLfloat SV2[3];
        GLfloat SV3[3];


        if ((fSets[i]).size() != 3) {
            //cout << "the fSetsets_Size is not correct" << endl;
        }

        else {

                GLint firstVertexIndex = (fSets[i])[0];
                GLint secondVertexIndex = (fSets[i])[1];
                GLint thirdVertexIndex = (fSets[i])[2];

                SV1[0] = (vSets[firstVertexIndex])[0];
                SV1[1] = (vSets[firstVertexIndex])[1];
                SV1[2] = (vSets[firstVertexIndex])[2];

                SV2[0] = (vSets[secondVertexIndex])[0];
                SV2[1] = (vSets[secondVertexIndex])[1];
                SV2[2] = (vSets[secondVertexIndex])[2];

                SV3[0] = (vSets[thirdVertexIndex])[0];
                SV3[1] = (vSets[thirdVertexIndex])[1];
                SV3[2] = (vSets[thirdVertexIndex])[2];

                //if there is no vn in the objfile
                //if (vnSets.size() == 0) {
                    GLfloat vec1[3], vec2[3], vec3[3];
                    //(x2-x1,y2-y1,z2-z1)
                    vec1[0] = SV1[0] - SV2[0];
                    vec1[1] = SV1[1] - SV2[1];
                    vec1[2] = SV1[2] - SV2[2];

                    //(x3-x2,y3-y2,z3-z2)
                    vec2[0] = SV1[0] - SV3[0];
                    vec2[1] = SV1[1] - SV3[1];
                    vec2[2] = SV1[2] - SV3[2];

                    //(x3-x1,y3-y1,z3-z1)
                    vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
                    vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
                    vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

                    GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

                    VN[0] = vec3[0] / D;
                    VN[1] = vec3[1] / D;
                    VN[2] = vec3[2] / D;

                    glNormal3f(VN[0], VN[1], VN[2]);

                glVertex3f(SV1[0], SV1[1], SV1[2]);
                glVertex3f(SV2[0], SV2[1], SV2[2]);
                glVertex3f(SV3[0], SV3[1], SV3[2]);

        }
    }

    glEnd();
}


void ObjLoader::Draw(GLint texID) {

    // add texture to roof 
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < fSets.size(); i++) {

        GLfloat VN[3];

        GLfloat VT1[3];
        GLfloat VT2[3];
        GLfloat VT3[3];

        //three vertex represrnt a surface
        GLfloat SV1[3];
        GLfloat SV2[3];
        GLfloat SV3[3];


        //        if ((fSets[i]).size() != 3) { // 对于一个face
        //            cout << "the fSetsets_Size is not correct" << endl;
        //        }else {

        GLint firstVertexIndex = (fSets[i])[0];
        GLint secondVertexIndex = (fSets[i])[1];
        GLint thirdVertexIndex = (fSets[i])[2];

        SV1[0] = (vSets[firstVertexIndex])[0];
        SV1[1] = (vSets[firstVertexIndex])[1];
        SV1[2] = (vSets[firstVertexIndex])[2];

        SV2[0] = (vSets[secondVertexIndex])[0];
        SV2[1] = (vSets[secondVertexIndex])[1];
        SV2[2] = (vSets[secondVertexIndex])[2];

        SV3[0] = (vSets[thirdVertexIndex])[0];
        SV3[1] = (vSets[thirdVertexIndex])[1];
        SV3[2] = (vSets[thirdVertexIndex])[2];

        GLint firstVTIndex = (VTIndexSets[i])[0];
        GLint secondVTIndex = (VTIndexSets[i])[1];
        GLint thirdVTIndex = (VTIndexSets[i])[2];

        VT1[0] = (vtSets[firstVTIndex])[0];
        VT1[1] = (vtSets[firstVTIndex])[1];


        VT2[0] = (vtSets[secondVTIndex])[0];
        VT2[1] = (vtSets[secondVTIndex])[1];


        VT3[0] = (vtSets[thirdVTIndex])[0];
        VT3[1] = (vtSets[thirdVTIndex])[1];


        //if there is no vn in the objfile
        GLfloat vec1[3], vec2[3], vec3[3];
        //(x2-x1,y2-y1,z2-z1)
        vec1[0] = SV1[0] - SV2[0];
        vec1[1] = SV1[1] - SV2[1];
        vec1[2] = SV1[2] - SV2[2];

        //(x3-x2,y3-y2,z3-z2)
        vec2[0] = SV1[0] - SV3[0];
        vec2[1] = SV1[1] - SV3[1];
        vec2[2] = SV1[2] - SV3[2];

        //(x3-x1,y3-y1,z3-z1)
        vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
        vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
        vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

        GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

        VN[0] = vec3[0] / D;
        VN[1] = vec3[1] / D;
        VN[2] = vec3[2] / D;

        glNormal3f(VN[0], VN[1], VN[2]);

        glTexCoord2f(VT1[0], VT1[1]);
        glVertex3f(SV1[0], SV1[1], SV1[2]);

        glTexCoord2f(VT2[0], VT2[1]);
        glVertex3f(SV2[0], SV2[1], SV2[2]);

        glTexCoord2f(VT3[0], VT3[1]);
        glVertex3f(SV3[0], SV3[1], SV3[2]);

        //        }

    }

    glEnd();


    // Stop blending textures and colours
    glDisable(GL_COLOR_MATERIAL);

    // Bind to the blank buffer to stop ourselves accidentaly
    // using the wrong texture in the next draw call
    glBindTexture(GL_TEXTURE_2D, NULL);
    // Stop performing texturing
    glDisable(GL_TEXTURE_2D);
}


