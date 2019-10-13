#include "main.h"

#ifndef INCLUDE_TRACER
#define INCLUDE_TRACER

namespace Tracer{
    extern int current_index;
    extern std::deque<Record*> steps;
    Record* record_frame(int);
    int restore_last();
    int restore_next();
    bool is_rear();
    bool is_head();
    bool is_empty();
    int push(Record*);
    void restore_step(int);
    Record* pop();
    Record* current_record();
    void reload_current_record();
    void terminate();
}
#endif // INCLUDE_TRACER
