/***************************************************************
 * Name:      MotorClientGUIApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Eli Ruiz (eruiz063@fiu.edu)
 * Created:   2017-04-19
 * Copyright: Eli Ruiz (zaawaa.com)
 * License:
 **************************************************************/

#include "MotorClientGUIApp.h"

//(*AppHeaders
#include "MotorClientGUIMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(MotorClientGUIApp);

bool MotorClientGUIApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	MotorClientGUIFrame* Frame = new MotorClientGUIFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
