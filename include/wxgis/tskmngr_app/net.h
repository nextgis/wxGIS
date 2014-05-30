/******************************************************************************
 * Project:  wxGIS (Task Manager)
 * Purpose:  Network classes.
 * Author:   Dmitry Barishnikov (aka Bishop), polimax@mail.ru
 ******************************************************************************
*   Copyright (C) 2012,2014 Dmitry Barishnikov
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

#include "wxgis/net/network.h"
#include "wxgis/net/servernet.h"

/** @class wxGISLocalNetworkService

    A local network server.

    @library{net}
*/
class wxGISLocalNetworkService : 
    public wxGISNetworkService
{
    DECLARE_CLASS(wxGISLocalNetworkService)
public:
    wxGISLocalNetworkService(INetEventProcessor* pNetEvtProc);
    virtual ~wxGISLocalNetworkService(void);
    virtual int GetConnectionCount(void){return m_nConnectionCounter;};
    //INetworkService
    virtual bool Start(void);
    virtual wxString GetServerName(void) const;
    virtual bool CanConnect(const wxString &sName, const wxString &sPass);
};

/** @class wxGISLocalNetworkPlugin

    A Server side Network Plugin.

    @library{net}
*/
class wxGISLocalNetworkPlugin : public INetPlugin
{
	DECLARE_CLASS(wxGISLocalNetworkPlugin)

    enum{
        // id for sockets
        TCP_SERVER_ID = 105         
    };
public:
	wxGISLocalNetworkPlugin(void);
	virtual ~wxGISLocalNetworkPlugin(void);
    bool CreateListenSocket(void);
    //INetworkPlugin
    virtual bool Start(INetService* pNetService, const wxXmlNode* pConfig);
    virtual bool Stop(void);   
    //events
    virtual void OnTCPServerEvent(wxSocketEvent& event);
protected:
    int m_nPort;
    wxString m_sAddr;
    INetService* m_pNetService;
    wxSocketServer* m_listeningSocket;

    DECLARE_EVENT_TABLE()
};

/** @class wxGISLocalServerConnection

    The network server connection interface class.

    @library{net}
*/
class wxGISLocalServerConnection : public wxGISNetServerConnection
{
    DECLARE_CLASS(wxGISLocalServerConnection)
public:
    wxGISLocalServerConnection(void);
    //wxGISLocalServerConnection(wxSocketBase* sock);
	virtual ~wxGISLocalServerConnection(void);
    virtual void SetSocket(wxSocketBase* sock);
protected: 
    //events
    virtual void OnSocketEvent(wxSocketEvent& event);
    virtual void OnTimer( wxTimerEvent & event);
protected:  
    virtual bool ProcessInputNetMessage(void);
};
