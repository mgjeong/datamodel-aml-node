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

#include "namlobject.h"
#include "namldata.h"
#include "namlutils.h"

using namespace v8;
using namespace AML;

namespace naml
{
    NAN_MODULE_INIT(NAMLObject::Init)
    {
        // Prepare constructor template
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NAMLObject").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "addData", AddData);
        Nan::SetPrototypeMethod(tpl, "getData", GetData);
        Nan::SetPrototypeMethod(tpl, "getDataNames", GetDataNames);
        Nan::SetPrototypeMethod(tpl, "getDeviceId", GetDeviceId);
        Nan::SetPrototypeMethod(tpl, "getTimeStamp", GetTimeStamp);
        Nan::SetPrototypeMethod(tpl, "getId", GetId);

        constructor().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NAMLObject").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NAMLObject::NewInstance(int argc, v8::Local<v8::Value> argv[])
    {
        v8::Local<v8::Function> cons = Nan::New(constructor());
        return Nan::NewInstance(cons, argc, argv).ToLocalChecked();
    }

    NAMLObject::NAMLObject(std::string deviceId, std::string timeStamp, std::string id): Nan::ObjectWrap()
    {
        try
        {
            if(id.length() < 1)
            {
                nativeHandle =  new AMLObject(deviceId, timeStamp);
            }
            else
            {
                nativeHandle =  new AMLObject(deviceId, timeStamp, id);
            }
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAMLObject::~NAMLObject()
    {

    }

    NAN_METHOD(NAMLObject::New)
    {
        if (info.IsConstructCall())
        {
            NAMLObject* obj = NULL;
            // Invoked as constructor: `new NAMLObject(...)`
            if(info.Length() >= 2)
            {
                //Get deviceId
                Local<String> deviceID = Local<String>::Cast(info[0]);
                String::Utf8Value deviceId(deviceID);

                //Get timeStamp
                Local<String> stamp = Local<String>::Cast(info[1]);
                String::Utf8Value timeStamp(stamp);

                if(info.Length() == 3)
                {
                    //Get Id
                    Local<String> ID = Local<String>::Cast(info[2]);
                    String::Utf8Value id(ID);
                    obj = new NAMLObject(*deviceId, *timeStamp, *id);
                }
                else
                {
                    obj = new NAMLObject(*deviceId, *timeStamp, "");
                }
            }
            else
            {
                obj = new NAMLObject();
            }
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
    }

    NAN_METHOD(NAMLObject::AddData)
    {
        NAMLObject* obj = ObjectWrap::Unwrap<NAMLObject>(info.Holder());

        //Get name param
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value name(str);

        //Get value param [AML data object]
        NAMLData *amlObj = Nan::ObjectWrap::Unwrap<NAMLData>(info[1].As<Object>());
        try
        {
            (obj->nativeHandle)->addData(*name, *(amlObj->nativeHandle));
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NAMLObject::GetData)
    {
        NAMLObject* obj = ObjectWrap::Unwrap<NAMLObject>(info.Holder());

        //Get name param
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value name(str);
        AMLData *amlData = NULL;
        try
        {
            amlData =  (AMLData *)dynamic_cast<const AMLData*>(&((obj->nativeHandle)->getData(*name)));
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }
        //Create addon AML object
        Local<Object> addonAMLData =  NAMLData::NewInstance();
        NAMLData* unwrappedAMLData = ObjectWrap::Unwrap<NAMLData>(addonAMLData);
        unwrappedAMLData->nativeHandle = amlData;
        info.GetReturnValue().Set(addonAMLData);
    }


    NAN_METHOD(NAMLObject::GetDataNames)
    {
        NAMLObject* obj = ObjectWrap::Unwrap<NAMLObject>(info.Holder());

        //get native vector and conver to js vector
        std::vector<std::string> dataNames;
        try
        {
            dataNames = (obj->nativeHandle)->getDataNames();
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }
        v8::Local<v8::Array> jsDataNames = Nan::New<v8::Array>(dataNames.size());
        for (size_t i = 0; i < dataNames.size(); i++)
        {
            Nan::Set(jsDataNames, i, Nan::New(dataNames[i]).ToLocalChecked());
        }
        info.GetReturnValue().Set(jsDataNames);
    }

    NAN_METHOD(NAMLObject::GetDeviceId)
    {
        NAMLObject* obj = ObjectWrap::Unwrap<NAMLObject>(info.Holder());
        try
        {
            info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->getDeviceId()).c_str())).ToLocalChecked());
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NAMLObject::GetTimeStamp)
    {
        NAMLObject* obj = ObjectWrap::Unwrap<NAMLObject>(info.Holder());
        try
        {
            info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->getTimeStamp()).c_str())).ToLocalChecked());
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NAMLObject::GetId)
    {
        NAMLObject* obj = ObjectWrap::Unwrap<NAMLObject>(info.Holder());
        try
        {
            info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->getId()).c_str())).ToLocalChecked());
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }
}

