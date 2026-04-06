#pragma once
#include<wx/wx.h>
#include<wx/artprov.h>
class MinhaJanela :
    public wxFrame
{
public:
    MinhaJanela(std::string title, int width, int height);
    void on_btnDestinoFDB_clicked(wxCommandEvent& evt);
    void on_btnExecutar_clicked(wxCommandEvent& evt);
    void RadioBoxMudarSelecao(wxCommandEvent& evt);

private:
    wxButton* btnExecutar, * btnDestinoFDB;
    wxCheckBox* chkRemoto;
    wxRadioBox* radioFirebirdVers;
    wxTextCtrl* campoIp, * campoPorta, * campoBK, * campoUsuario, * campoSenha, * campoNucleos, * campoDestino;
    long maximoDeNucleos;
    wxPanel* pnl;
};

