#pragma once

#include "IChangelogPanel.h"
#include <vgui_controls/Frame.h>
#include "steam/steam_api_common.h"
#include "steam/isteamhttp.h"

// CChangelogPanel class
class CChangelogPanel : public vgui::Frame
{
    DECLARE_CLASS_SIMPLE(CChangelogPanel, Frame);

    CChangelogPanel(vgui::VPANEL parent); // Constructor
    ~CChangelogPanel();

    void SetChangelogText(const char* pChangelogText);

    void ApplySchemeSettings(vgui::IScheme* pScheme) OVERRIDE;

    void Activate() OVERRIDE;

  private:
    void GetRemoteChangelog();
    CCallResult<CChangelogPanel, HTTPRequestCompleted_t> m_callResult;
    void ChangelogCallback(HTTPRequestCompleted_t *pParam, bool bIOFailure);

    vgui::RichText *m_pChangeLog;
    char m_cOnlineVersion[12];
    wchar_t *m_pwOnlineChangelog;
};

class CChangelogInterface : public IChangelogPanel
{
  private:
    CChangelogPanel *pPanel;

  public:
    CChangelogInterface();
    virtual ~CChangelogInterface() {}
    void Create(vgui::VPANEL parent) OVERRIDE;

    void Destroy() OVERRIDE
    {
        if (pPanel)
        {
            pPanel->SetParent(nullptr);
            delete pPanel;
        }
        pPanel = nullptr;
    }
    void Activate(void) OVERRIDE
    {
        if (pPanel)
        {
            pPanel->Activate();
        }
    }
};