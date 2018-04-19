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

#include "namlutils.h"

AMLErrorCode ExceptionCodeToErrorCode(AML::ResultCode result)
{
    switch (result)
    {
        case AML::INVALID_PARAM :           return AML_INVALID_PARAM;
        case AML::INVALID_FILE_PATH :       return AML_INVALID_FILE_PATH;
        case AML::INVALID_AML_SCHEMA :      return AML_INVALID_AML_SCHEMA;
        case AML::INVALID_XML_STR :         return AML_INVALID_XML_STR;
        case AML::NOT_MATCH_TO_AML_MODEL :  return AML_NOT_MATCH_TO_AML_MODEL;
        case AML::INVALID_BYTE_STR :        return AML_INVALID_BYTE_STR;
        case AML::SERIALIZE_FAIL :          return AML_SERIALIZE_FAIL;
        case AML::NO_MEMORY :               return AML_NO_MEMORY;
        case AML::KEY_NOT_EXIST :           return AML_KEY_NOT_EXIST;
        case AML::KEY_ALREADY_EXIST :       return AML_KEY_ALREADY_EXIST;
        case AML::WRONG_GETTER_TYPE :       return AML_WRONG_GETTER_TYPE;
        case AML::API_NOT_ENABLED :         return AML_API_NOT_ENABLED;
        default : /* AML::NO_ERROR */       return AML_OK;
    }
}
