#include "head.h"
using namespace std;
map<string, string> buildMap(ifstream &map_file){
	map<string, string> trans_map;
	string key, value;
	while (map_file >> key && getline(map_file, value))
		if (value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for"+key);
	return trans_map;
}
const string& transform(const string& s,const map<string,string>& m){
	auto map_it = m.find(s);
	if (map_it != m.cend())
		return (*map_it).second;
	else
		return s;
}
void word_transform(ifstream& map_file, ifstream& input,ofstream& output){
	auto trans_map = buildMap(map_file);
	string text;
	while (getline(input, text)){
		istringstream stream(text);
		string word;
		bool firstword = true;
		while (stream >> word){
			if (firstword)
				firstword = false;
			else
				output<< " ";
			output << transform(word, trans_map);
		}
		output << endl;
	}
}
int main(){
	ifstream map_file("C:/Users/zhangle/Desktop/11.txt");
	ifstream input("C:/Users/zhangle/Desktop/22.txt");
	ofstream output("C:/Users/zhangle/Desktop/33.txt");
	if (map_file && input)
		word_transform(map_file, input,output);
	else
		cerr << "no data!" << endl;
	system("pause");
	return 0;
}