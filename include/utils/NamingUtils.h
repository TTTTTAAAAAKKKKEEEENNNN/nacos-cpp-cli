#ifndef __NAMING_UTILS_H_
#define __NAMING_UTILS_H_
#include <vector>
#include "NacosString.h"
#include "Constants.h"
#include "utils/ParamUtils.h"

class NamingUtils
{
public:
    static String getGroupedName(const String &serviceName, const String &groupName)
    {
        return groupName + Constants::SERVICE_INFO_SPLITER + serviceName;
    }

    static String getServiceName(const String &serviceNameWithGroup)
    {
        if (!ParamUtils::contains(serviceNameWithGroup, Constants::SERVICE_INFO_SPLITER))
        {
            return serviceNameWithGroup;
        }
        std::vector<String> splittedNameNGroup;
        ParamUtils::Explode(splittedNameNGroup, serviceNameWithGroup, Constants::SERVICE_INFO_SPLITER);
        return splittedNameNGroup[1];
    }

    static String getGroupName(const String &serviceNameWithGroup)
    {
        if (!ParamUtils::contains(serviceNameWithGroup, Constants::SERVICE_INFO_SPLITER))
        {
            return Constants::DEFAULT_GROUP;
        }
        std::vector<String> splittedNameNGroup;
        ParamUtils::Explode(splittedNameNGroup, serviceNameWithGroup, Constants::SERVICE_INFO_SPLITER);
        return splittedNameNGroup[0];
    }
};

#endif
