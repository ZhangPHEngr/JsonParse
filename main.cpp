#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

struct output {
	int width;
	int height;
	int frame_rate;
	int crf;
};
void from_json(const json &j, output &vi){
    j.at("width").get_to(vi.width);
    j.at("height").get_to(vi.height);
    j.at("frameRate").get_to(vi.frame_rate);
    j.at("crf").get_to(vi.crf);
}


struct pieces
{
    string file;
    int startTime;
    int endTime;
};
void from_json(const json &j, pieces &p){
    j.at("file").get_to(p.file);
    j.at("startTime").get_to(p.startTime);
    j.at("endTime").get_to(p.endTime);
}

struct tracks {
    string name;
    pieces p[10];
    int p_cnt;
};

void from_json(const json &j, tracks &t){
    j.at("name").get_to(t.name);
    for (size_t i = 0; i < j["pieces"].size(); i++)
    {
        t.p[i] = j["pieces"][i];
    }
    t.p_cnt = j["pieces"].size();
}


int main(){

    ifstream jfile("D:/Code/Json/demo.json", ifstream::in);

    if(!jfile.is_open()){
        cout<<"open file failed!"<<endl;
        exit(-1);
    }
    cout<<"open file success!"<<endl;

    json js;
    jfile >> js;
    jfile.close();
    

    cout<<js.at("output")<<endl;
    output vi = js.at("output");
    cout<<vi.crf<<endl;

    int tilength = js["tracks"].size();
    tracks ti[tilength];
    for (int i = 0; i < tilength; i++) {
        ti[i] = js["tracks"][i];
    }
    cout<<ti[0].p[0].file<<endl;

    

}