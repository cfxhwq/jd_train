#include "json/json.h"
#include <string>
#include <iostream>
using namespace std;

void writeJson() {
	using namespace std;

	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;

	item["cpp"] = "jsoncpp";
	item["java"] = "jsoninjava";
	item["php"] = "support";
	arrayObj.append(item);

	root["name"] = "json";
	root["array"] = arrayObj;

	root.toStyledString();
	std::string out = root.toStyledString();
	std::cout << "toStyledString" <<endl << out << std::endl;

	cout<< "FastWriter" <<endl;
	Json::FastWriter fast;
	out = fast.write(root);
	cout<< out <<endl;
	
	cout<<  "StyledWriter" <<endl;
	Json::StyledWriter styled;
	out = styled.write(root);
	cout<< out <<endl;

}

void readJson() {
	using namespace std;
	std::string strValue = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";

	Json::Reader reader;
	Json::Value value;

	if (reader.parse(strValue, value))
	{   
		std::string out = value["name"].asString();
		std::cout << out << std::endl;
		const Json::Value arrayObj = value["array"];
		for (unsigned int i = 0; i < arrayObj.size(); i++)
		{   
			if (!arrayObj[i].isMember("cpp")) 
				continue;
			out = arrayObj[i]["cpp"].asString();
			std::cout << out;
			if (i != (arrayObj.size() - 1)) 
				std::cout << std::endl;
		}   
	}   
}

int main()
{
	readJson() ;
	writeJson();
	return 0;
}
