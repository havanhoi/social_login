//
//  JsonDump.h
//  JsonDump
//
//  Created by Ha Anh Man on 3/8/16.
//
//

#ifndef __JsonDump__JsonDump__
#define __JsonDump__JsonDump__

#include "json/document.h"
#include "json/rapidjson.h"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;
class JsonDump {
public:
    static JsonDump* getInstance();
    bool StringIsNumber(const std::string& str);
    
    ValueVector dumpValueVectorFromString(string str);
    ValueMap dumpValueMapFromString(string str);
    
    ValueMap dumpValueMap(rapidjson::Value &data);
    ValueVector dumpValueVector(rapidjson::Value &data);
    ValueVector getArrayNumber(rapidjson::Value &data);
    ValueVector processObjectVV(rapidjson::Value &data);
    ValueMap processObjectVM(rapidjson::Value &data);
    
    std::string MapToString(ValueMap map);
    std::string VectorToString(ValueVector vector);
    rapidjson::Value AddMapToDocument(rapidjson::Document &document, ValueMap map);
    
    rapidjson::Value AddVectorToDocument(rapidjson::Document &document, ValueVector vector);
    
    
private:
    static JsonDump* instance;
};

#endif /* defined(__JsonDump__JsonDump__) */
