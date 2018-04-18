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

#include "nrepresentation.h"
#include "namlobject.h"
#include "namldata.h"
#include "namlutils.h"

#include <v8.h>

using namespace v8;
using namespace AML;

namespace naml
{
    NAN_MODULE_INIT(NRepresentation::Init)
    {
        // Prepare constructor template
        v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
        tpl->SetClassName(Nan::New("NRepresentation").ToLocalChecked());
        tpl->InstanceTemplate()->SetInternalFieldCount(1);

        // Function Prototypes
        Nan::SetPrototypeMethod(tpl, "dataToAml", DataToAml);
        Nan::SetPrototypeMethod(tpl, "amlToData", AmlToData);
        Nan::SetPrototypeMethod(tpl, "dataToByte", DataToByte);
        Nan::SetPrototypeMethod(tpl, "byteToData", ByteToData);
        Nan::SetPrototypeMethod(tpl, "getRepresentationId", GetRepresentationId);
        Nan::SetPrototypeMethod(tpl, "getConfigInfo", GetConfigInfo);

        constructor().Reset(GetFunction(tpl).ToLocalChecked());
        Nan::Set(target, Nan::New("NRepresentation").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
    }

    v8::Local<v8::Object> NRepresentation::NewInstance(int argc, v8::Local<v8::Value> argv[])
    {
        v8::Local<v8::Function> cons = Nan::New(constructor());
        return Nan::NewInstance(cons, argc, argv).ToLocalChecked();
    }

    NRepresentation::NRepresentation(std::string filePath): Nan::ObjectWrap()
    {
        try
        {
            nativeHandle =  new Representation(filePath);
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NRepresentation::~NRepresentation()
    {

    }

    NAN_METHOD(NRepresentation::New)
    {
        // Invoked as constructor: `new NRepresentation(...)`
        if (info.IsConstructCall())
        {
            //Get filePath
            Local<String> str = Local<String>::Cast(info[0]);
            String::Utf8Value filePath(str);

            NRepresentation* obj = new NRepresentation(*filePath);
            obj->Wrap(info.This());
            info.GetReturnValue().Set(info.This());
        }
    }

    NAN_METHOD(NRepresentation::DataToAml)
    {
        NRepresentation* obj = ObjectWrap::Unwrap<NRepresentation>(info.Holder());

        //Get AML object
        NAMLObject *amlObject = Nan::ObjectWrap::Unwrap<NAMLObject>(info[0].As<Object>());
        try
        {
            info.GetReturnValue().Set(Nan::New(((obj->nativeHandle)->DataToAml(*(amlObject->nativeHandle))).c_str()).ToLocalChecked());
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NRepresentation::AmlToData)
    {
        NRepresentation* obj = ObjectWrap::Unwrap<NRepresentation>(info.Holder());

        //Get amlString
        Local<String> str = Local<String>::Cast(info[0]);
        String::Utf8Value amlString(str);
        AMLObject* amlObject = NULL;
        try
        {
            amlObject = (obj->nativeHandle)->AmlToData(*amlString);
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }
        //Create addon AML object
        v8::Local<v8::Value> argv[] {Nan::Null()};
        Local<Object> addonAMLObj =  NAMLObject::NewInstance(0, argv);
        NAMLObject* unwrappedAMLObj = ObjectWrap::Unwrap<NAMLObject>(addonAMLObj);
        unwrappedAMLObj->nativeHandle = amlObject;
        info.GetReturnValue().Set(addonAMLObj);
    }

    NAN_METHOD(NRepresentation::DataToByte)
    {
        NRepresentation* obj = ObjectWrap::Unwrap<NRepresentation>(info.Holder());
        NAMLObject *amlObject = Nan::ObjectWrap::Unwrap<NAMLObject>(info[0].As<Object>());
        std::string byteString;
        try
        {
            byteString = ((obj->nativeHandle)->DataToByte(*(amlObject->nativeHandle)));
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }

        size_t size = byteString.size();
        char* cstr = new char[size + 1];
        memcpy(cstr, byteString.c_str(), size);
        cstr[size] = '\0';
        uint8_t *byte = reinterpret_cast<uint8_t*>(cstr);
        info.GetReturnValue().Set(Nan::CopyBuffer((char *)byte,  byteString.size()).ToLocalChecked());
    }

    NAN_METHOD(NRepresentation::ByteToData)
    {
        NRepresentation* obj = ObjectWrap::Unwrap<NRepresentation>(info.Holder());
        Local<Object> bufferObj = info[0]->ToObject();
        char* data= (char*)node::Buffer::Data(bufferObj);
        size_t dataLength = info[1]->Uint32Value();
        std::string byteString(data, dataLength);
        AMLObject* amlObject = NULL;
        try
        {
            amlObject = (obj->nativeHandle)->ByteToData(byteString);
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }

        //Create addon AML object
        v8::Local<v8::Value> argv[] {Nan::Null()};
        Local<Object> addonAMLObj =  NAMLObject::NewInstance(0, argv);
        NAMLObject* unwrappedAMLObj = ObjectWrap::Unwrap<NAMLObject>(addonAMLObj);
        unwrappedAMLObj->nativeHandle = amlObject;
        info.GetReturnValue().Set(addonAMLObj);
    }

   NAN_METHOD(NRepresentation::GetRepresentationId)
    {
        NRepresentation* obj = ObjectWrap::Unwrap<NRepresentation>(info.Holder());
        try
        {
            info.GetReturnValue().Set((Nan::New(((obj->nativeHandle)->getRepresentationId()).c_str())).ToLocalChecked());
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
        }
    }

    NAN_METHOD(NRepresentation::GetConfigInfo)
    {
        NRepresentation* repObj = ObjectWrap::Unwrap<NRepresentation>(info.Holder());
        AMLObject* amlObj = NULL;
        try
        {
            amlObj = (repObj->nativeHandle)->getConfigInfo();
        }
        catch (const AMLException& e)
        {
            v8::Local<v8::Value> error = Nan::New<Integer>(ExceptionCodeToErrorCode(e.code()));
            Nan::ThrowError(error);
            return;
        }
        //Create addon AML object
        v8::Local<v8::Value> argv[] {Nan::Null()};
        Local<Object> addonAMLObj =  NAMLObject::NewInstance(0, argv);
        NAMLObject* unwrappedAMLObj = ObjectWrap::Unwrap<NAMLObject>(addonAMLObj);
        unwrappedAMLObj->nativeHandle = amlObj;
        info.GetReturnValue().Set(addonAMLObj);
    }
}

