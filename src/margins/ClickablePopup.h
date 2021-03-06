#pragma once

#include <cstdint>
#include <cassert>
#include <exception>
#include <stdexcept>

#include "util.h"
#include "nametagGlobals.h"

#include <audioSound.h>
#include <pandabase.h>
#include <pandaNode.h>
#include <nodePath.h>
#include <typeinfo>
#include <mouseWatcher.h>
#include <mouseWatcherBase.h>
#include <mouseWatcherRegion.h>
#include <notifyCategoryProxy.h>
#include <eventReceiver.h>
#include <eventParameter.h>

NotifyCategoryDecl(ClickablePopup, EXPCL_LIBOTP, EXPTP_LIBOTP);

class ClickablePopup;

typedef void(*callback_t)(const Event* ev);
typedef pmap<std::string, callback_t> event_table_t;

class EXPCL_LIBOTP ClickablePopup : public virtual EventReceiver, public NodePath {
    
    PUBLISHED:
        ClickablePopup();
        ClickablePopup(NodePath* camera);
        virtual ~ClickablePopup();
        
    public:
        enum State {
            stateStopped = 0,
            statePaused = 1,
            stateRunning = 2
        };
        
        virtual void destroy();
        virtual void set_click_region_event(const std::string& event, int do_id=0);
        virtual void update_contents();
        
        void set_state(State state);
        uint32_t get_state();
        
        int get_click_state();
        virtual void click_state_changed()=0;

        static void handle_event(const Event* ev, void* data);
        
    protected:
        std::string get_event(const std::string& pattern);
        void update_click_state();
        void update_click_region(float left, float right, float bottom, float top);
        void disable_click_region();

        PT(MouseWatcher) m_mouse_watcher;
        PT(AudioSound) m_click_sound, m_rollover_sound;
        NodePath* m_cam;
        
        bool m_disabled;
        bool m_clicked;
        bool m_hovered;
        
        int m_click_state;
        std::string m_click_event;
        std::string m_name;
        MouseWatcherRegion *m_region;
    
    private:      
        static unsigned int ClickablePopup_serial;
        
        int m_from_id;
        
        std::string mouse_enter_name;
        std::string mouse_leave_name;
        std::string button_down_name;
        std::string button_up_name;
        
        EventParameter m_event_parameter;
        
        void enter_region();
        void exit_region();
        
        void mouse_enter(const Event* ev);
        void mouse_leave(const Event* ev);
        void button_down(const Event* ev);
        void button_up(const Event* ev);
        
        void accept(const std::string& ev);
        void ignore_all();
        
    TYPE_HANDLE(ClickablePopup, TypedObject);
};