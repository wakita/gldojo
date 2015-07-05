#include <fstream>
#include <iostream>
#include <json11.hpp>

using namespace std;
using namespace json11;

int main() {
  // Creating a JSON structure
  Json json1 = Json::object {
    { "k1", "v1" },
    { "k2", false },
    { "k3", Json::array { 1, 2, 3 } },
    { "k4", Json::array { -4.5, -3.5, -2.5, 2.5, 3.5, 4.5} },
  };
  cout << json1.dump() << endl;

  ifstream f("/Users/wakita/Dropbox (smartnova)/work/opengl/dojo/config/x.json");
  string input((istreambuf_iterator<char>(f)), istreambuf_iterator<char>()), err;
  Json x(Json::parse(input, err));
  cout << x.dump() << endl;

  // Retrieval and conversion of a JSON element
  vector<float> vLightLa;
  for (auto v : x["Light"]["La"].array_items())
    vLightLa.push_back((float)(v.number_value()));

  return 0;
}
