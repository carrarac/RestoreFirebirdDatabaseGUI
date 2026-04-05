#pragma once
#include "MinhaJanela.h"
class App :
    public wxApp
{
    wxLocale locale;
public:
    virtual bool OnInit();
};

