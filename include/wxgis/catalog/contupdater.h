/******************************************************************************
 * Project:  wxGIS (GIS Catalog)
 * Purpose:  Remote Connection classes.
 * Author:   Dmitry Baryshnikov (aka Bishop), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2014 Dmitry Baryshnikov
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
#pragma once

#include "wxgis/catalog/gxobject.h"
#include "wxgis/core/process.h"

#include <wx/hashmap.h>

WX_DECLARE_HASH_MAP(int, wxString, wxIntegerHash, wxIntegerEqual, wxGxObjectMap);

/** @class wxGxObjectContainerUpdater
 * 
 * A special class to periodically request the changes from remote container and update children
 * 
 * @library{catalog}
 */
 
class WXDLLIMPEXP_GIS_CLT wxGxObjectContainerUpdater :
	public wxGxObjectContainer,
    public wxGISThreadHelper,
	public IGxObjectNotifier
{
	DECLARE_ABSTRACT_CLASS(wxGxObjectContainerUpdater)
public:
	wxGxObjectContainerUpdater(wxGxObject *oParent, const wxString &soName = wxEmptyString, const CPLString &soPath = "");
	virtual ~wxGxObjectContainerUpdater();
	//IGxObjectNotifier
	virtual void OnGetUpdates(int nDelay = 50);
protected:
    virtual wxThread::ExitCode Entry();
	virtual wxGxObject *GetChildByRemoteId(int nRemoteId) const;
    virtual wxGxObjectMap GetRemoteObjects() = 0;
	virtual void DeleteObject(int nRemoteId);
	virtual void RenameObject(int nRemoteId, const wxString &sNewName);
	virtual void AddObject(int nRemoteId, const wxString &sName) = 0;
    virtual bool CreateAndRunThread(void);
protected:	
	wxGxObjectMap m_smObjects;
	int m_nLongWait, m_nShortWait, m_nStep;
	int m_nProcessUpdatesRequests;
	bool m_bChildrenLoaded;
};
	
/** @class wxGxRemoteId
  * 
  * A remote object identificator
  * 
  * @library{catalog}
  */
  
class WXDLLIMPEXP_GIS_CLT wxGxRemoteId
{
public:
    wxGxRemoteId();
	wxGxRemoteId(int nRemoteId);
    virtual ~wxGxRemoteId(void);
	virtual int GetRemoteId() const;
	virtual void SetRemoteId(int nRemoteId);
protected:
    int m_nRemoteId;
};


