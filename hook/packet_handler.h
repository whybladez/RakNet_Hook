#pragma once
#include "raknet/RakClient.h"
#include "raknet/PluginInterface.h"

#include "main.h"

class packet_handler : public PluginInterface {
	virtual PluginReceiveResult OnReceive(RakPeerInterface*, Packet*) override;
};

class raknet_plugin_attacher {
public:
	void attach(RakClientInterface* rakclient, PluginInterface *handler);
	~raknet_plugin_attacher();

private:
	PluginInterface *handler;
	RakClientInterface* rakclient;
};

extern raknet_plugin_attacher raknet_plugin_attacher_instance;


void handle_handling_packet(BitStream bs);

