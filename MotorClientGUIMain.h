/***************************************************************
 * Name:      MotorClientGUIMain.h
 * Purpose:   Defines Application Frame
 * Author:    Eli Ruiz (eruiz063@fiu.edu)
 * Created:   2017-04-19
 * Copyright: Eli Ruiz (zaawaa.com)
 * License:
 **************************************************************/

#ifndef MOTORCLIENTGUIMAIN_H
#define MOTORCLIENTGUIMAIN_H

#include <wx/socket.h>

//(*Headers(MotorClientGUIFrame)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/gbsizer.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
//*)

class MotorClientGUIFrame: public wxFrame
{
    public:

        MotorClientGUIFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~MotorClientGUIFrame();

    private:

        //(*Handlers(MotorClientGUIFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void onSend(wxCommandEvent& event);
        void OnChoice1Select(wxCommandEvent& event);
        //*)

        //(*Identifiers(MotorClientGUIFrame)
        static const long ID_CHOICE1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL2;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(MotorClientGUIFrame)
        wxTextCtrl* cmdValue;
        wxStatusBar* StatusBar1;
        wxChoice* cmdChoice;
        wxTextCtrl* outputTextbox;
        wxButton* sendButton;
        //*)

        // event handlers for Socket menu
        void OnConnectToServer(wxCommandEvent& event);

        // socket event handler
        void OnSocketEvent(wxSocketEvent& event);

        DECLARE_EVENT_TABLE()
};

enum
{
    // menu items
    CLIENT_QUIT = 1000,
    CLIENT_OPEN,

    // id for socket
    SOCKET_ID
};



#endif // MOTORCLIENTGUIMAIN_H
