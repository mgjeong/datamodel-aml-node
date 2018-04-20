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

#ifndef NAML_UTILS_H
#define NAML_UTILS_H

#include "AMLException.h"

typedef enum
{
    AML_OK = 0,
    AML_INVALID_PARAM,
    AML_INVALID_FILE_PATH,
    AML_INVALID_AML_SCHEMA,
    AML_INVALID_XML_STR,
    AML_NOT_MATCH_TO_AML_MODEL,
    AML_INVALID_BYTE_STR,
    AML_SERIALIZE_FAIL,
    AML_NO_MEMORY,
    AML_KEY_NOT_EXIST,
    AML_KEY_ALREADY_EXIST,
    AML_WRONG_GETTER_TYPE,
    AML_API_NOT_ENABLED,
} AMLErrorCode;

AMLErrorCode ExceptionCodeToErrorCode(AML::ResultCode result);

#endif  //NAML_UTILS_H
