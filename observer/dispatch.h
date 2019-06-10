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
    void CreateSubjects(std::list<std::string> sub_list, int num_channels);
    Subject* GetSubject(std::string name);
    void SetSubject(std::string name, double value);

    //void add_midi_device();
    //void add_UI();
    //void add_YAML();
private:
    std::map<std::string, Subject*> subject_map;
};




#endif //TWILIGHT_DISPATCH_H
