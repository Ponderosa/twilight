//
// Created by ponderosa on 6/4/19.
//

#ifndef TWILIGHT_DISPATCH_H
#define TWILIGHT_DISPATCH_H

#include <list>
#include <string>
#include <map>
#include "subject.h"

class Dispatch {
public:
    Dispatch();
    void CreateSubjects(std::vector<std::string> sub_list, std::vector<double>, int num_channels);
    Subject* GetSubject(std::string name);
private:
    std::map<std::string, Subject*> subject_map;
};


#endif //TWILIGHT_DISPATCH_H
