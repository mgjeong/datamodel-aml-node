/*******************************************************************************
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *******************************************************************************/

#include "AMLException.h"

#include "namldata.h"
#include "namlutils.h"

using namespace v8;
using namespace AML;

namespace naml
{
    NAN_MODULE_INIT(NAMLData::Init)
    {
        // Prepare constructor template
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NAMLData").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "getValueToStr", GetValueToStr);
        Nan::SetPrototypeMethod(tpl, "getValueToStrArr", GetValueToStrArr);
        Nan::SetPrototypeMethod(tpl, "getValueToAMLData", GetValueToAMLData);
        Nan::SetPrototypeMethod(tpl, "getKeys", GetKeys);
        Nan::SetPrototypeMethod(tpl, "getValueType", GetValueType);

        Nan::SetPrototypeMethod(tpl, "setValue", SetValue);
        Nan::SetPrototypeMethod(tpl, "setAMLDataValue", SetAMLDataValue);
        Nan::SetPrototypeMethod(tpl, "setVectorValue", SetVectorValue);

        constructor().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NAMLData").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NAMLData::NewInstance()
    {
        v8::Local<v8::Function> cons = Nan::New(constructor());
        return Nan::NewInstance(cons).ToLocalChecked();
    }

    NAMLData::NAMLData(): Nan::ObjectWrap()
    {
        nativeHandle =  new AMLData();
    }

    NAMLData::~NAMLData()
    {

    }

    NAN_METHOD(NAMLData::New)
    {
        if (info.IsConstructCall())
        {
            // Invoked as constructor: `new NAMLData(...)`
            NAMLData *obj = new NAMLData();
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
    }

    NAN_METHOD(NAMLData::GetValueToStr)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value key(str);
        NAMLData* obj = ObjectWrap::Unwrap<NAMLData>(info.Holder());
        try
        {
            info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->getValueToStr(*key)).c_str())).ToLocalChecked());
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NAMLData::GetValueToStrArr)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value key(str);
        NAMLData* obj = ObjectWrap::Unwrap<NAMLData>(info.Holder());

        //get native vector and conver to js vector
        std::vector<std::string> values;
        try
        {
            values = (obj->nativeHandle)->getValueToStrArr(*key);
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }
        v8::Local<v8::Array> jsValues = Nan::New<v8::Array>(values.size());
        for (size_t i = 0; i < values.size(); i++)
        {
            Nan::Set(jsValues, i, Nan::New(values[i]).ToLocalChecked());
        }
        info.GetReturnValue().Set(jsValues);
    }

    NAN_METHOD(NAMLData::GetValueToAMLData)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value key(str);
        NAMLData* obj = ObjectWrap::Unwrap<NAMLData>(info.Holder());
        AMLData *amlData = NULL;
        try
        {
            amlData = (AMLData *)dynamic_cast<const AMLData*>(&(((obj->nativeHandle)->getValueToAMLData(*key))));
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }
        //Create addon AML object
        Local<Object> addonAMLData = NAMLData::NewInstance();
        NAMLData* unwrappedAMLData = ObjectWrap::Unwrap<NAMLData>(addonAMLData);
        unwrappedAMLData->nativeHandle = amlData;
        info.GetReturnValue().Set(addonAMLData);
    }

    NAN_METHOD(NAMLData::GetKeys)
    {
        NAMLData* obj = ObjectWrap::Unwrap<NAMLData>(info.Holder());
        //get native vector and conver to js vector
        std::vector<std::string> keys;
        try
        {
            keys = (obj->nativeHandle)->getKeys();
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }
        v8::Local<v8::Array> jsKeys = Nan::New<v8::Array>(keys.size());
        for (size_t i = 0; i < keys.size(); i++)
        {
            Nan::Set(jsKeys, i, Nan::New(keys[i]).ToLocalChecked());
        }
        info.GetReturnValue().Set(jsKeys);
    }

    NAN_METHOD(NAMLData::GetValueType)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value key(str);
        NAMLData* obj = ObjectWrap::Unwrap<NAMLData>(info.Holder());
        try
        {
            info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>((obj->nativeHandle)->getValueType(*key))));
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NAMLData::SetValue)
    {
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value key(str);
        str = Local<String>::Cast(info[1]);
        String::Utf8Value value(str);
        NAMLData* obj = ObjectWrap::Unwrap<NAMLData>(info.Holder());
        try
        {
            (obj->nativeHandle)->setValue(*key, *value);
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NAMLData::SetAMLDataValue)
    {
        NAMLData* obj = ObjectWrap::Unwrap<NAMLData>(info.Holder());

        //Get key param
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value key(str);

        //Get value param [AML data object]
        NAMLData *amlObj = Nan::ObjectWrap::Unwrap<NAMLData>(info[1].As<Object>());
        try
        {
            (obj->nativeHandle)->setValue(*key, *(amlObj->nativeHandle));
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NAMLData::SetVectorValue)
    {
        NAMLData* obj = ObjectWrap::Unwrap<NAMLData>(info.Holder());

        //Get key param
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value key(str);

        //Get value param [vector of string]
        std::vector<std::string> nativeValues;
        Local<Array> jsValues = Local<Array>::Cast(info[1]);
        unsigned int length = jsValues->Length();
        for (unsigned int i = 0; i < length; i++)
        {
            Local<String> str = Local<String>::Cast(jsValues->Get(i));
            String::Utf8Value utfValue(str);
            nativeValues.push_back(*utfValue);
        }
        try
        {
            (obj->nativeHandle)->setValue(*key, nativeValues);
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }
}

