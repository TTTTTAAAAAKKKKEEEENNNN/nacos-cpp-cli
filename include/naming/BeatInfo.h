#ifndef __BEAT_INFO_H_
#define __BEAT_INFO_H_
#include <map>
#include "NacosString.h"

/*
 * Copyright 1999-2018 Alibaba Group Holding Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @author nkorange
 */
class BeatInfo
{
public:
	int port;
	NacosString ip;
	double weight;
	NacosString serviceName;
	NacosString cluster;
	std::map<NacosString, NacosString> metadata;
	volatile bool scheduled;

    NacosString toString()
	{
        //return JSON.toJSONString(this);
		return "{\"fake\":\"Beatinfo\"}";//TODO:add json support & serialize as string
    }
};

#endif