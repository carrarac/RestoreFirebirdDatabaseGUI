#include "MinhaJanela.h"

void MinhaJanela::RadioBoxMudarSelecao(wxCommandEvent& evt)
{
    if (radioFirebirdVers->GetSelection() == 0 || radioFirebirdVers->GetSelection() == 1)
    {
        campoNucleos->SetValue("1");
        campoNucleos->Enable(false);
        return;
    }
    else
    {
        campoNucleos->Enable(true);
        return;
    }
}

void MinhaJanela::on_btnDestinoFDB_clicked(wxCommandEvent& evt)
{
    wxFileDialog dialog(this,
        "Selecione o arquivo .fbk",
        "",
        ".fbk",
        "Firebird Backup (*.fbk) |*.fbk",
        wxFD_OPEN
    );
    if (dialog.ShowModal() == wxID_OK) {
        campoBK->SetValue(dialog.GetPath());
    }
    if (campoBK->GetValue().Lower().EndsWith(".fbk")) {
        wxString nomeDB = campoBK->GetValue();
        nomeDB = nomeDB.Left(nomeDB.Len() - 3) + "fdb";
        campoDestino->SetValue(nomeDB);
    }
}

void MinhaJanela::on_btnExecutar_clicked(wxCommandEvent& evt)
{
    if (
        campoBK->GetValue().IsEmpty() ||
        campoDestino->GetValue().IsEmpty() ||
        campoIp->GetValue().IsEmpty() ||
        campoSenha->GetValue().IsEmpty() ||
        campoUsuario->GetValue().IsEmpty() ||
        campoPorta->GetValue().IsEmpty()
        )
    {
        wxMessageBox(wxT("É necessário preencher os campos essenciais\n"
            "IP, Porta, Usuário, Senha e Caminhos"), "Alerta", wxOK | wxICON_WARNING);
        return;
    }
    else
    {
        wxString comando = "";
        wxString ip = campoIp->GetValue();
        wxString porta = campoPorta->GetValue();
        wxString bk = campoBK->GetValue();
        wxString dest = campoDestino->GetValue();
        wxString page = comboPageSize->GetValue();
        wxString user = campoUsuario->GetValue();
        wxString senha = campoSenha->GetValue();

        if (chkRemoto->GetValue())
        {
            switch (radioFirebirdVers->GetSelection())
            {
            case 0:
            {
                campoNucleos->SetValue("1");
                comando = wxString::Format(
                    "\"C:/Program Files/Firebird/Firebird_3_0/gbak.exe\""
                    " -c -se %s/%s:service_mgr"
                    " \"%s\" \"%s/%s:%s\" -p %s -user %s -password %s",
                    ip, porta,   
                    bk,     
                    ip, porta, dest, 
                    page, user, senha);
            }   break;
            case 1:
            {
                campoNucleos->SetValue("1");
                comando = wxString::Format(
                    "\"C:/Program Files/Firebird/Firebird_4_0/gbak.exe\""
                    " -c -se %s/%s:service_mgr"
                    " \"%s\" \"%s/%s:%s\" -p %s -user %s -password %s",
                    ip, porta,
                    bk,
                    ip, porta, dest,
                    page, user, senha);
            }   break;
            case 2:
            {
                SYSTEM_INFO sysInfo;
                GetSystemInfo(&sysInfo);
                long maximoDeNucleos = sysInfo.dwNumberOfProcessors;
                long vlNucleos;
                if (!campoNucleos->GetValue().ToLong(&vlNucleos) || vlNucleos <= 0)
                {
                    wxMessageBox(wxT("Por favor, insira um número válido de núcleos (maior que zero)."),
                        "Erro de Validação", wxOK | wxICON_ERROR);
                    campoNucleos->SetValue("1");
                    return;
                }
                if (vlNucleos >= maximoDeNucleos)
                {
                    wxMessageBox(wxT("Quantidade de processadores lógicos maior ou igual ao existente.\nReduzindo para um valor seguro."),
                        "Alerta", wxOK | wxICON_WARNING);
                    long nucleosSeguros = (maximoDeNucleos > 1) ? (maximoDeNucleos - 1) : 1;
                    campoNucleos->SetValue(wxString::Format("%ld", nucleosSeguros));
                    return;
                }
                comando = wxString::Format(
                    "\"C:/Program Files/Firebird/Firebird_5_0/gbak.exe\""
                    " -c -par %s -se %s/%s:service_mgr"
                    " \"%s\" \"%s/%s:%s\" -p %s -user %s -password %s",
                    campoNucleos->GetValue(),
                    ip, porta,
                    bk,
                    ip, porta, dest,
                    page, user, senha);
            }   break;
            default: return; break;
            }
        }
        else
        {
            switch (radioFirebirdVers->GetSelection())
            {
            case 0:
            {
                campoNucleos->SetValue("1");
                comando = wxString::Format(
                    "\"C:/Program Files/Firebird/Firebird_3_0/gbak.exe\" -c"
                    " \"%s\" \"%s/%s:%s\" -p %s -user %s -password %s",
                    bk, ip, porta, dest, page, user, senha);
            }   break;
            case 1:
            {
                campoNucleos->SetValue("1");
                comando = wxString::Format(
                    "\"C:/Program Files/Firebird/Firebird_4_0/gbak.exe\" -c"
                    " \"%s\" \"%s/%s:%s\" -p %s -user %s -password %s",
                    bk, ip, porta, dest, page, user, senha);
            }   break;
            case 2:
            {
                SYSTEM_INFO sysInfo;
                GetSystemInfo(&sysInfo);
                long maximoDeNucleos = sysInfo.dwNumberOfProcessors;
                long vlNucleos;
                if (!campoNucleos->GetValue().ToLong(&vlNucleos) || vlNucleos <= 0)
                {
                    wxMessageBox(wxT("Por favor, insira um número válido de núcleos (maior que zero)."),
                        "Erro de Validação", wxOK | wxICON_ERROR);
                    campoNucleos->SetValue("1");
                    return;
                }
                if (vlNucleos >= maximoDeNucleos)
                {
                    wxMessageBox(wxT("Quantidade de processadores lógicos maior ou igual ao existente.\nReduzindo para um valor seguro."),
                        "Alerta", wxOK | wxICON_WARNING);
                    long nucleosSeguros = (maximoDeNucleos > 1) ? (maximoDeNucleos - 1) : 1;
                    campoNucleos->SetValue(wxString::Format("%ld", nucleosSeguros));
                    return;
                }
                comando = wxString::Format(
                    "\"C:/Program Files/Firebird/Firebird_5_0/gbak.exe\" -c -par %s"
                    " \"%s\" \"%s/%s:%s\" -p %s -user %s -password %s",
                    campoNucleos->GetValue(),
                    bk, ip, porta, dest, page, user, senha);
            }   break;
            default: return; break;
            }
        }

        if (wxFileExists(campoDestino->GetValue()))
        {
            wxMessageBox(wxT("Já existe um banco .FDB"), "Alerta", wxOK | wxICON_INFORMATION);
            wxString stringBanco = campoDestino->GetValue();
            stringBanco = stringBanco.Left(stringBanco.Len() - 4) + "_";
            stringBanco.Append(".fdb");
            campoDestino->SetValue(stringBanco);
            return;
        }

        wxArrayString erro;
        wxArrayString saida;
        long codigoRetorno = wxExecute(comando, saida, erro, wxEXEC_SYNC);

        if (codigoRetorno == -1)
        {
            wxMessageBox(wxT("Falha crítica: Não foi possível executar o gbak.exe.\nVerifique se o Firebird está instalado no caminho correto."),
                wxT("Erro de Execução"), wxOK | wxICON_ERROR);
        }
        else if (codigoRetorno != 0 || !erro.IsEmpty())
        {
            wxString mensagemErro = "Ocorreu um erro ao processar o banco de dados:\n\n";
            for (size_t i = 0; i < erro.GetCount(); i++)
                mensagemErro += erro[i] + "\n";
            wxMessageBox(mensagemErro, "Erro no GBAK", wxOK | wxICON_ERROR);
        }
        else
        {
            wxMessageBox(wxT("Processo concluído com sucesso!"), "Sucesso", wxOK | wxICON_INFORMATION);
        }
    }
}

MinhaJanela::MinhaJanela(std::string title, int width, int height) :
    wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER)
{
    this->EnableMaximizeButton(false);
    this->SetSize(width, height);
    maximoDeNucleos = 0;
    pnl = new wxPanel(this);
    wxIcon icone = wxArtProvider::GetIcon(wxART_FOLDER);
    this->SetIcon(icone);

    wxArrayString page_size;
    page_size.Add("1024");
    page_size.Add("2048");
    page_size.Add("4096");
    page_size.Add("8192");
    page_size.Add("16384");
    page_size.Add("32768");

    wxArrayString opcoes;
    opcoes.Add("Firebird 3");
    opcoes.Add("Firebird 4");
    opcoes.Add("Firebird 5");

    btnExecutar = new wxButton(pnl, wxID_ANY, "Executar", wxPoint(20, 300), wxSize(-1, -1));

    new wxStaticText(pnl, wxID_ANY, "IP", wxPoint(20, 20), wxSize(-1, -1));
    campoIp = new wxTextCtrl(pnl, wxID_ANY, "127.0.0.1", wxPoint(20, 40), wxSize(200, -1));

    new wxStaticText(pnl, wxID_ANY, "Porta", wxPoint(240, 20), wxSize(-1, -1));
    campoPorta = new wxTextCtrl(pnl, wxID_ANY, "3050", wxPoint(240, 40), wxSize(60, -1));

    new wxStaticText(pnl, wxID_ANY, "Caminho do backup do banco (.fbk)", wxPoint(20, 70), wxSize(-1, -1));
    campoBK = new wxTextCtrl(pnl, wxID_ANY, "", wxPoint(20, 90), wxSize(300, -1));

    btnDestinoFDB = new wxButton(pnl, wxID_ANY, "Selecionar", wxPoint(20, 130), wxSize(-1, -1));

    new wxStaticText(pnl, wxID_ANY, wxT("Caminho para criação do banco  (.fdb)"), wxPoint(330, 70), wxSize(-1, -1));
    campoDestino = new wxTextCtrl(pnl, wxID_ANY, "", wxPoint(330, 90), wxSize(300, -1));

    new wxStaticText(pnl, wxID_ANY, wxT("Usuário"), wxPoint(20, 190), wxSize(-1, -1));
    campoUsuario = new wxTextCtrl(pnl, wxID_ANY, "SYSDBA", wxPoint(20, 210), wxSize(200, -1));

    new wxStaticText(pnl, wxID_ANY, "Senha", wxPoint(20, 250), wxSize(-1, -1));
    campoSenha = new wxTextCtrl(pnl, wxID_ANY, "masterkey", wxPoint(20, 270), wxSize(200, -1), wxTE_PASSWORD);

    new wxStaticText(pnl, wxID_ANY, wxT("Núcleos"), wxPoint(420, 20), wxSize(-1, -1));
    campoNucleos = new wxTextCtrl(pnl, wxID_ANY, "1", wxPoint(420, 40), wxSize(60, -1));

    chkRemoto = new wxCheckBox(pnl, wxID_ANY, wxT("Restore remoto (banco será restaurado no servidor)"), wxPoint(330, 240));

    new wxStaticText(pnl, wxID_ANY, "Page Size", wxPoint(330, 270), wxSize(-1, -1));
    comboPageSize = new wxComboBox(pnl, wxID_ANY, "4096", wxPoint(330, 290), wxSize(100, -1), page_size);

    radioFirebirdVers = new wxRadioBox(pnl, wxID_ANY, wxT("Versão do Firebird"),
        wxPoint(330, 130), wxSize(-1, -1), opcoes, 1, wxRA_SPECIFY_COLS);
    radioFirebirdVers->SetSelection(2);

    btnDestinoFDB->Bind(wxEVT_BUTTON, &MinhaJanela::on_btnDestinoFDB_clicked, this);
    btnExecutar->Bind(wxEVT_BUTTON, &MinhaJanela::on_btnExecutar_clicked, this);
    radioFirebirdVers->Bind(wxEVT_RADIOBOX, &MinhaJanela::RadioBoxMudarSelecao, this);
}