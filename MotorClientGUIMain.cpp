/***************************************************************
 * Name:      MotorClientGUIMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Eli Ruiz (eruiz063@fiu.edu)
 * Created:   2017-04-19
 * Copyright: Eli Ruiz (zaawaa.com)
 * License:
 **************************************************************/

#include "MotorClientGUIMain.h"
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>
#include <wx/msgdlg.h>

//(*InternalHeaders(MotorClientGUIFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(MotorClientGUIFrame)
const long MotorClientGUIFrame::ID_CHOICE1 = wxNewId();
const long MotorClientGUIFrame::ID_TEXTCTRL1 = wxNewId();
const long MotorClientGUIFrame::ID_BUTTON1 = wxNewId();
const long MotorClientGUIFrame::ID_TEXTCTRL2 = wxNewId();
const long MotorClientGUIFrame::idMenuQuit = wxNewId();
const long MotorClientGUIFrame::idMenuAbout = wxNewId();
const long MotorClientGUIFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MotorClientGUIFrame,wxFrame)
    //(*EventTable(MotorClientGUIFrame)
    EVT_MENU(CLIENT_OPEN,       MotorClientGUIFrame::OnConnectToServer)
    EVT_SOCKET(SOCKET_ID,       MotorClientGUIFrame::OnSocketEvent)
    //*)
END_EVENT_TABLE()

/*
BEGIN_EVENT_TABLE(MotorClientGUIFrame, wxFrame)
    EVT_MENU(CLIENT_QUIT,       MotorClientGUIFrame::OnQuit)
    EVT_MENU(CLIENT_OPEN,       MotorClientGUIFrame::OnConnectToServer)
    EVT_SOCKET(SOCKET_ID,       MotorClientGUIFrame::OnSocketEvent)
END_EVENT_TABLE()
*/
MotorClientGUIFrame::MotorClientGUIFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(MotorClientGUIFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxGridBagSizer* GridBagSizer1;
    wxMenu* Menu2;
    wxStaticBoxSizer* StaticBoxSizer1;

    Create(parent, wxID_ANY, _("Motor Client"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    GridBagSizer1 = new wxGridBagSizer(0, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Choose Command"));
    cmdChoice = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    cmdChoice->SetSelection( cmdChoice->Append(_("Nothing")) );
    cmdChoice->Append(_("Start"));
    cmdChoice->Append(_("Stop"));
    cmdChoice->Append(_("Rotate Left"));
    cmdChoice->Append(_("Rotate Right"));
    cmdChoice->Append(_("Speed"));
    StaticBoxSizer1->Add(cmdChoice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    cmdValue = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticBoxSizer1->Add(cmdValue, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sendButton = new wxButton(this, ID_BUTTON1, _("Send"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    StaticBoxSizer1->Add(sendButton, 1, wxALL|wxALIGN_TOP, 5);
    GridBagSizer1->Add(StaticBoxSizer1, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    outputTextbox = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(249,234), wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    GridBagSizer1->Add(outputTextbox, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND, 5);
    SetSizer(GridBagSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    GridBagSizer1->Fit(this);
    GridBagSizer1->SetSizeHints(this);

    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&MotorClientGUIFrame::OnChoice1Select);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MotorClientGUIFrame::onSend);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MotorClientGUIFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&MotorClientGUIFrame::OnAbout);
    //*)
    outputTextbox->AppendText(_("Client Ready"));

}

MotorClientGUIFrame::~MotorClientGUIFrame()
{
    //(*Destroy(MotorClientGUIFrame)
    //*)
}

void MotorClientGUIFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void MotorClientGUIFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
                    Event Handlers
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/
void MotorClientGUIFrame::OnConnectToServer(wxCommandEvent& WXUNUSED(event))
{

    wxIPV4address addr;
    addr.Hostname(_("localhost"));
    addr.Service(3000);

    // Create the socket
    wxSocketClient* Socket = new wxSocketClient();

    // Set up the event handler and subscribe to most events
    Socket->SetEventHandler(*this, SOCKET_ID);
    Socket->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    Socket->Notify(true);

    // Wait for the connection event
    Socket->Connect(addr, false);
}

void MotorClientGUIFrame::OnSocketEvent(wxSocketEvent& event)
{
     static int cnt = 1;
    // The socket that had the event
    wxSocketBase* sock = event.GetSocket();

    // Common buffer shared by the events
    char buf[10];

    switch(event.GetSocketEvent())
    {
        case wxSOCKET_CONNECTION:
        {
            SetStatusText(_("Connected to Server localhost on Port 3000"));
            wxString tt = wxString::Format(wxT("\nConnection Num:%i\n"),cnt++);
            outputTextbox->AppendText(tt);
            outputTextbox->AppendText(_("Connected to server.\n"));

            switch (cmdChoice->GetSelection()) {
            case 0:
                buf [0] = '0';
                buf [1] = '\n';
                buf [2] = '\0';
                break;
            case 1:
                buf [0] = '1';
                buf [1] = '\n';
                buf [2] = '\0';
                break;
            case 2:
                buf [0] = '2';
                buf [1] = '\n';
                buf [2] = '\0';
                break;
            case 3:
                buf [0] = '3';
                for(int i = 0 ; i < cmdValue->GetLineLength(0) ; i++){
                    buf [i + 1] = cmdValue->GetLineText(0)[i];
                }
                buf [cmdValue->GetLineLength(0) + 1] = '\n';
                buf [cmdValue->GetLineLength(0) + 2] = '\0';
                break;
            case 4:
                buf [0] = '4';
                for(int i = 0 ; i < cmdValue->GetLineLength(0) ; i++){
                    buf [i + 1] = cmdValue->GetLineText(0)[i];
                }
                buf [cmdValue->GetLineLength(0) + 1] = '\n';
                buf [cmdValue->GetLineLength(0) + 2] = '\0';
                break;
            case 5:
                buf [0] = '5';
                for(int i = 0 ; i < cmdValue->GetLineLength(0) ; i++){
                    buf [i + 1] = cmdValue->GetLineText(0)[i];
                }
                buf [cmdValue->GetLineLength(0) + 1] = '\n';
                buf [cmdValue->GetLineLength(0) + 2] = '\0';
                break;
            default:
                //message = NULL;
                break;
            }

            // Send the characters to the server
            sock->Write(buf, sizeof(buf));

            outputTextbox->AppendText(wxString(_("Sending to server: ") + wxString(buf, wxConvUTF8, 10)));



            break;
        }
        case wxSOCKET_INPUT:
        {
            sock->Read(buf, sizeof(buf));

            outputTextbox->AppendText(wxString(_("Received from server: ")) + wxString(buf, wxConvUTF8, 10) + _("\n"));

            break;
        }

        // The server hangs up after sending the data
        case wxSOCKET_LOST:
        {
            sock->Destroy();

            outputTextbox->AppendText(_("Connection lost.\n"));

            SetStatusText(_("Disconnected from localhost:3000"));

            break;
        }
    }
}


void MotorClientGUIFrame::onSend(wxCommandEvent& event)
{
    wxIPV4address addr;
    addr.Hostname(wxT("localhost"));
    addr.Service(3000);

    // Create the socket
    wxSocketClient* Socket = new wxSocketClient();

    // Set up the event handler and subscribe to most events
    Socket->SetEventHandler(*this, SOCKET_ID);
    Socket->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    Socket->Notify(true);

    // Wait for the connection event
    Socket->Connect(addr, false);
}

void MotorClientGUIFrame::OnChoice1Select(wxCommandEvent& event)
{
}
