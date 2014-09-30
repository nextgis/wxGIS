/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  Main frame class.
 * Author:   Dmitry Baryshnikov (aka Bishop), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2009-2010,2012 Dmitry Baryshnikov
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 2 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "wxgis/cat_app/catalogframe.h"

#include "wxgis/app/gisaboutdlg.h"

#include "../../art/wxgiscatalog_x16.xpm"
#include "../../art/wxgiscatalog16.xpm"
#include "../../art/wxgiscatalog_x32.xpm"
#include "../../art/wxgiscatalog32.xpm"
#include "../../art/wxgiscatalog_x48.xpm"
#include "../../art/wxgiscatalog48.xpm"
#include "../../art/wxgiscatalog_x64.xpm"
#include "../../art/wxgiscatalog64.xpm"
#include "../../art/wxgiscatalog_x128.xpm"
#include "../../art/wxgiscatalog128.xpm"
#include <wx/datetime.h>

//-----------------------------------------------------------
// wxGISCatalogFrame
//-----------------------------------------------------------
IMPLEMENT_CLASS(wxGISCatalogFrame, wxGxApplication)

wxGISCatalogFrame::wxGISCatalogFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxGxApplication(parent, id, title, pos, size, style)
{
	//set app main icon
	wxIconBundle iconBundle;
	
	//brending
	wxGISAppConfig oConfig = GetConfig();
	bool bIsBranded = false;
    if (oConfig.IsOk())
	{
		bIsBranded = oConfig.ReadBool(enumGISHKCU, wxT("ngmbrend/status/is_branded"), false);
		if(bIsBranded)
		{
			wxString sBrendText = oConfig.Read(enumGISHKCU, wxT("ngmbrend/text/short"), wxEmptyString);
		
			if(!sBrendText.IsEmpty())
			{
				m_sAppDisplayNameShort = sBrendText;
			}
			
			sBrendText = oConfig.Read(enumGISHKCU, wxT("ngmbrend/text/normal"), wxEmptyString);
		
			if(!sBrendText.IsEmpty())
			{
				m_sAppDisplayName = sBrendText;
			}
			
			//icons
			wxString sPrefix = oConfig.Read(enumGISHKCU, wxT("ngmbrend/icon/prefix"), wxEmptyString);
			wxString sImgPath = oConfig.GetConfigDir(wxT("brand"));
			if(!sImgPath.IsEmpty())
			{
				wxString sIconPath = sImgPath + wxFileName::GetPathSeparator() + wxString::Format(wxT("%s16.png"), sPrefix.c_str());
				m_pAppIcon = wxIcon(sIconPath, wxBITMAP_TYPE_PNG);
				for(int i = 16; i < 256; i *= 2)
				{
					sIconPath = sImgPath + wxFileName::GetPathSeparator() + wxString::Format(wxT("%s%d.png"), sPrefix.c_str(), i);
					iconBundle.AddIcon(wxIcon(sIconPath, wxBITMAP_TYPE_PNG));	 
				}
			}
		}
	}
	
	if(!bIsBranded)
	{
		wxDateTime now = wxDateTime::Now();
		if((now.GetMonth() == wxDateTime::Dec && now.GetDay() > 15) || (now.GetMonth() == wxDateTime::Jan && now.GetDay() < 15))
		{
			m_pAppIcon = wxIcon(wxgiscatalog_x16_xpm);
	#ifdef __WXMSW__
			iconBundle.AddIcon(wxICON(MAINFRAME_X));
	//#else
	#endif
			iconBundle.AddIcon(m_pAppIcon);
			iconBundle.AddIcon(wxIcon(wxgiscatalog_x32_xpm));
			iconBundle.AddIcon(wxIcon(wxgiscatalog_x48_xpm));
			iconBundle.AddIcon(wxIcon(wxgiscatalog_x64_xpm));
			iconBundle.AddIcon(wxIcon(wxgiscatalog_x128_xpm));

		}
		else
		{
			m_pAppIcon = wxIcon(wxgiscatalog16_xpm);
	#ifdef __WXMSW__
			iconBundle.AddIcon(wxICON(MAINFRAME));
	//#else
	#endif
			iconBundle.AddIcon(m_pAppIcon);
			iconBundle.AddIcon(wxIcon(wxgiscatalog32_xpm));
			iconBundle.AddIcon(wxIcon(wxgiscatalog48_xpm));
			iconBundle.AddIcon(wxIcon(wxgiscatalog64_xpm));
			iconBundle.AddIcon(wxIcon(wxgiscatalog128_xpm));
		}
	}
    SetIcons(iconBundle);
}

wxGISCatalogFrame::~wxGISCatalogFrame(void)
{
}

void wxGISCatalogFrame::OnAppAbout(void)
{
    wxGISAboutDialog oDialog(this);
    oDialog.ShowModal();
}


