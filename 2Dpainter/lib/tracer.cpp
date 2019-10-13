#include "main.h"

namespace Tracer{
    std::deque<Record*> steps;
    int last_index = -1;
    int current_index = -1;

    Record* record_frame(int _act){
        Util::save_buffer();
        auto rec = new Record(Record::TYPE_FRAME, _act, canvas);
        return rec;
    }

    int push(Record* rec){
        if(current_index != last_index){
            std::deque<Record*> tmp;
            for(int i=0;i<last_index;++i){
                if(i <= current_index){
                    tmp.push_back(steps[i]);
                }
                else{
                    delete steps[i];
                }
            }
            steps = tmp;
        }

        if(current_index >= MAX_TRACE){
            auto _discard = steps.front();
            delete _discard;
            steps.pop_front();
        }
        else{current_index += 1;}

        last_index = current_index;
        steps.push_back(rec);
        return current_index;
    }

    int restore_last(){
        if(is_head()){return 0;}
        current_index -= 1;
        restore_step(current_index);
        return current_index;
    }

    int restore_next(){
        if(is_rear()){return last_index;}
        current_index += 1;
        restore_step(current_index);
        return current_index;
    }

    void restore_step(int _idx){
        cout << "Restore step " << _idx << '\n';
        Record* rec = steps[_idx];
        rec -> restore();
    }

    Record* current_record(){
        if(current_index < 0){return NULL;}
        return steps[current_index];
    }

    void reload_current_record(){
        if(current_index < 0){return ;}
        steps[current_index] -> restore_frame();
    }

    bool is_rear(){return current_index == last_index;}
    bool is_head(){return current_index <= 0;}
    bool is_empty(){return current_index == -1;}

    void terminate(){
        for(auto p:steps){
            delete p;
        }
    }
}
