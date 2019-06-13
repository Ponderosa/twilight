//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_DISPATCH_H
#define TWILIGHT_DISPATCH_H

#include <list>
#include <string>
#include <map>
#include "subject.h"
#include "parameter.h"

class Dispatch {
public:
    Dispatch();
    void CreateParameters(std::vector<std::string> sub_list, std::vector<double>, int num_channels);
    Parameter* GetParameter(std::string name);
private:
    std::map<std::string, Parameter*> parameter_map;
};


#endif //TWILIGHT_DISPATCH_H
