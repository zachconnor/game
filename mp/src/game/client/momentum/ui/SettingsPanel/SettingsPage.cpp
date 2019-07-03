#include "cbase.h"

#include "SettingsPage.h"

#include "tier0/memdbgon.h"

SettingsPage::SettingsPage(Panel *pParent, const char *pName) : BaseClass(pParent, pName)
{
    // Set proportionality of the panels inside the dialog
    SetSize(10, 10);
    SetProportional(true);

    //Lastly, the scroll panel so we can scroll through our settings page.
    m_pScrollPanel = new SettingsPageScrollPanel(pParent, this, "ScrollablePanel");
    m_pScrollPanel->AddActionSignalTarget(this);
    m_pScrollPanel->SetProportional(true);
}

void SettingsPage::NotifyParentOfUpdate()
{
    // Note: Clicking the "apply" button should handle setting the values.
    PostMessage(m_pScrollPanel->GetParent()->GetVPanel(), new KeyValues("ApplyButtonEnable"));
}

void SettingsPage::OnApplyChanges()
{
    // We're going to fire this to all our children, so the CVarToggleCheckButtons apply
    // their new settings to the convars.
    for (int i = 0; i < GetChildCount(); i++)
    {
        Panel *pChild = GetChild(i);
        if (pChild)
        {
            PostMessage(pChild, new KeyValues("ApplyChanges"));
        }
    }
}

void SettingsPage::OnPageShow()
{
    LoadSettings();
    m_pScrollPanel->ScrollToTop();
}

void SettingsPage::OnResetData()
{
    LoadSettings();
}
