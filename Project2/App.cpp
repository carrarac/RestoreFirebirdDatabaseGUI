#include "App.h"

bool App::OnInit() {
	locale.Init(wxLANGUAGE_DEFAULT);
	wxConvCurrent = &wxConvUTF8;
	MinhaJanela* Janela = new MinhaJanela("Restore Firebird Database", 700, 400);
	Janela->Show(true);
	return true;
}
wxIMPLEMENT_APP(App);
