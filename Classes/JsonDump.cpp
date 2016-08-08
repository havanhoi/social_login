//
//  JsonDump.cpp
//  Demo
//
//  Created by Ha Anh Man on 3/8/16.
//
//

#include "JsonDump.h"
#include <json/document.h>
#include <json/rapidjson.h>
#include <json/stringbuffer.h>
#include <json/writer.h>

JsonDump* JsonDump::instance;
JsonDump* JsonDump::getInstance()
{
    if (instance == nullptr) {
        instance = new JsonDump();
    }
    return instance;
}

/*
 bool IsNull()   const { return flags_ == kNullFlag; }
 bool IsInt()    const { return (flags_ & kIntFlag) != 0; }
 bool IsDouble() const { return (flags_ & kDoubleFlag) != 0; }
 bool IsString() const { return (flags_ & kStringFlag) != 0; }
  bool IsArray()  const { return flags_ == kArrayFlag; }
 bool IsObject() const { return flags_ == kObjectFlag; }

 */
ValueMap JsonDump::dumpValueMap(rapidjson::Value &data) {
    ValueMap vl;
    
    rapidjson::Value::MemberIterator item;
    for (item = data.MemberBegin(); item != data.MemberEnd(); item++)
    {
        std::string key = item->name.GetString();
        if(key.length() == 0) {
            CCLOG("Khong co gia tri key");
        }
        if(item->value.IsNull()) {
//            vl[key] = NULL;
            continue;
        }
        if(item->value.IsInt()) {
            vl[key] = item->value.GetInt();
            continue;
        }
        if(item->value.IsBool()) {
            vl[key] = item->value.GetBool();
            continue;
        }
        
        if(item->value.IsDouble()) {
            vl[key] = item->value.GetDouble();
            continue;
        }
        
        if(item->value.IsString()) {
            if(StringIsNumber(item->value.GetString())) {
                int so = atoi(item->value.GetString());
                vl[key] = so;
            } else {
                vl[key] = item->value.GetString();
            }
            continue;
        }
        if(item->value.IsArray()) {
            ValueVector vvArr = dumpValueVector(item->value);
            vl[key] = vvArr;
            continue;
        }
        
        if(item->value.IsObject()) {
            rapidjson::Value &obj = item->value;
            
            //kiem tra xem object nay co key:value hay khong
            bool haskey = false;
            rapidjson::Value::MemberIterator sub;
            for (sub = obj.MemberBegin(); sub != obj.MemberEnd(); sub++) {
                std::string key = sub->name.GetString();
                haskey = key.length() > 0;
                break;
            }
            
            if(haskey) {
                vl[key] = processObjectVM(obj);
            } else {
                vl[key] = processObjectVV(obj);
            }
            
            continue;
        }
    }
    return vl;
}

bool JsonDump::StringIsNumber(const std::string& str)
{
    if(str.length() == 0) {
        return false;
    }
    std::string::const_iterator i = str.begin();
    for (; i != str.end(); ++i)
    {
        if (*i < '0' || *i > '9') {
            return false;
        }
    }
    return true;
}

ValueVector JsonDump::dumpValueVector(rapidjson::Value &data) {
    ValueVector vv;
    for (rapidjson::SizeType i = 0; i < data.Size(); i++) {
        if(data[i].IsObject()) {
//            CCLOG("dumpValueVector => IsObject");
        }
        if(data[i].IsArray()) {
//            CCLOG("dumpValueVector => IsArray");
        }
        if(data[i].IsInt()) {
//            CCLOG("dumpValueVector => IsInt");
            vv.push_back(Value(data[i].GetInt()));
            continue;
        }
        if(data[i].IsDouble()) {
            CCLOG("dumpValueVector => IsDouble");
            vv.push_back(Value(data[i].GetDouble()));
            continue;
        }
        if(data[i].IsString()) {
            if(StringIsNumber(data[i].GetString())) {
                int so = atoi(data[i].GetString());
                vv.push_back(Value(so));
            } else {
                vv.push_back(Value(data[i].GetString()));
            }
            continue;
        }
        ValueMap vl = dumpValueMap(data[i]);
        vv.push_back(Value(vl));
    }
    return vv;
}

ValueVector JsonDump::getArrayNumber(rapidjson::Value &data) {
    ValueVector arr;
    for (int i = 0; i < data.Size(); i++) {
        if(data[i].IsInt()) {
            arr.push_back(Value(data[i].GetInt()));
        }
    }
    return arr;
}



ValueVector JsonDump::processObjectVV(rapidjson::Value &data) {
    ValueVector arr;
    rapidjson::Value::MemberIterator sub;
    for (sub = data.MemberBegin(); sub != data.MemberEnd(); sub++) {
        if(sub->value.IsInt()) {
            arr.push_back(Value(sub->value.GetInt()));
        }
    }
    return arr;
}

ValueMap JsonDump::processObjectVM(rapidjson::Value &data) {
    ValueMap map;
    rapidjson::Value::MemberIterator sub;
    for (sub = data.MemberBegin(); sub != data.MemberEnd(); sub++) {
        std::string key = sub->name.GetString();
        if(sub->value.IsObject()) {
            map[key] = dumpValueMap(sub->value);
            continue;
        }
        if(sub->value.IsArray()) {
            map[key] = dumpValueVector(sub->value);
            continue;
        }
        if(sub->value.IsInt()) {
            map[key] = sub->value.GetInt();
            continue;
        }
        
        if(sub->value.IsDouble()) {
            map[key] = sub->value.GetDouble();
            continue;
        }
        
        if(sub->value.IsString()) {
            if(StringIsNumber(sub->value.GetString())) {
                int so = atoi(sub->value.GetString());
                map[key] = so;
            } else {
                map[key] = sub->value.GetString();
            }
            continue;
        }
    }
    return map;
}




std::string JsonDump::MapToString(ValueMap map) {
    rapidjson::Document document; // Null
    typedef rapidjson::GenericValue<rapidjson::UTF8<> > JValue;
        
    rapidjson::Value sub = AddMapToDocument(document, map);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    sub.Accept(writer);
    
    std::string document_str = buffer.GetString();
    return document_str;
}

std::string JsonDump::VectorToString(ValueVector vector) {
    rapidjson::Document document;
    
    rapidjson::Value sub = AddVectorToDocument(document, vector);

    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    sub.Accept(writer);
    
    std::string document_str = buffer.GetString();
    return document_str;
}

rapidjson::Value JsonDump::AddMapToDocument(rapidjson::Document &document, ValueMap map) {
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    typedef rapidjson::GenericValue<rapidjson::UTF8<> > JValue;
    JValue jKey, jValue;
    
    rapidjson::Value obj(rapidjson::kObjectType);
    
    
    for (auto item : map) {
        string key = StringUtils::format("%s",item.first.c_str());
        jKey.SetString(key.c_str(), key.length(), allocator);        
        cocos2d::Value::Type vType = map[key].getType();
        if(vType == Value::Type::STRING) {
            jValue.SetString(map[key].asString().c_str(), allocator);
            obj.AddMember(jKey, jValue, allocator);
        }else if(vType == Value::Type::INTEGER) {
            jValue.SetInt(map[key].asInt());
            obj.AddMember(jKey, jValue, allocator);
        }else if(vType == Value::Type::FLOAT || vType == Value::Type::DOUBLE) {
            jValue.SetDouble(map[key].asDouble());
            obj.AddMember(jKey, jValue, allocator);
        }else if(vType == Value::Type::BOOLEAN) {
            jValue.SetBool(map[key].asBool());
            obj.AddMember(jKey, jValue, allocator);
        }else if(vType == Value::Type::MAP) {
            rapidjson::Value sub = AddMapToDocument(document, map[key].asValueMap());
            obj.AddMember(jKey, sub, allocator);
        }else if(vType == Value::Type::VECTOR) {
            rapidjson::Value sub = AddVectorToDocument(document, map[key].asValueVector());
            obj.AddMember(jKey, sub, allocator);
        }
    }
    return obj;
}

rapidjson::Value JsonDump::AddVectorToDocument(rapidjson::Document &document, ValueVector vector) {
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value arrayItem(rapidjson::kArrayType);
    
    typedef rapidjson::GenericValue<rapidjson::UTF8<> > JValue;
    JValue jValue;
    for (auto g : vector) {
        cocos2d::Value::Type vType = g.getType();
        if(vType == Value::Type::INTEGER) {
            jValue.SetInt(g.asInt());
            arrayItem.PushBack(jValue, allocator);
        } else if(vType == Value::Type::DOUBLE || vType == Value::Type::FLOAT) {
            jValue.SetDouble(g.asDouble());
            arrayItem.PushBack(jValue, allocator);
        } else if(vType == Value::Type::STRING) {
            jValue.SetString(g.asString().c_str(), allocator);
            arrayItem.PushBack(jValue, allocator);
        } else if(vType == Value::Type::MAP) {
            ValueMap map = g.asValueMap();
            rapidjson::Value obj = AddMapToDocument(document, map);
            arrayItem.PushBack(obj, allocator);
        }
    }
    return arrayItem;
}

ValueVector JsonDump::dumpValueVectorFromString(string str) {
    ValueVector data;
    if(str.length() == 0) {
        return data;
    }
    rapidjson::Document document;
    rapidjson::Document phonic_highlight;
    document.Parse<0>(str.c_str());
    
    rapidjson::Value &vl = document;
    data = dumpValueVector(vl);
    return data;
}

ValueMap JsonDump::dumpValueMapFromString(string str) {
    ValueMap data;
    if(str.length() == 0) {
        return data;
    }
    rapidjson::Document document;
    rapidjson::Document phonic_highlight;
    document.Parse<0>(str.c_str());
    
    rapidjson::Value &vl = document;
    data = dumpValueMap(vl);
    return data;
}
